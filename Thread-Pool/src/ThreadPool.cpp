#include "ThreadPool.h"
#include <stdexcept>

ThreadPool::ThreadPool(size_t threads)
    :stop(false){
    if(threads<0)threads=0;
    if(threads>this->max_threads)threads=this->max_threads;
    for(size_t i=0;i<threads;++i){
        //直接放置任务函数
        works.emplace_back(
            [this]{
                while(1){
                    std::function<void()>task;
                    {
                        //线程锁
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        //线程阻塞
                        this->condition.wait(lock,[this]{return this->stop||!this->tasks.empty();});
                        //退出线程
                        if(this->stop && this->tasks.empty())return;
                        //执行任务
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            }
        );
    }
}

template<class F, class... Argv>
auto ThreadPool::push(F &&function, Argv &&...argv)
    ->std::future<typename std::result_of<F (Argv...)>::type>{
    //创建函数返回类型
    using return_type = typename std::result_of<F (Argv...)>::type;
    //创建函数引用对象
    auto task =std::make_shared<
        std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(function)
                    ,std::forward<Argv>(argv)...)
    );
    //获取任务返回值
    std::future<return_type> ret = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(stop){
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        if(this->works.empty()){
            throw std::runtime_error("enqueue on empty ThreadPool");
        }
        tasks.emplace([task]{ (*task)(); });
    }
    this->condition.notify_one();
    return ret;
}
ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex);
        this->stop = true;
    }
    this->condition.notify_all();
    for(auto& work:works){
        work.join();
    }
}

#include <iostream>
int main(int argc,char* argy[]){

    ThreadPool pools(-1);
    std::vector< std::future<int> > results;
    
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pools.push(
                [i](){
                    std::cout<<"hellow word:"<<i<<std::endl;
                    return i*i;
                }
            )
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}