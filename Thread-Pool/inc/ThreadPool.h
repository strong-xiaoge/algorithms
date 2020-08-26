#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <thread>
#include <functional>

class ThreadPool
{
public:
    ThreadPool() :ThreadPool(5){}
    ThreadPool(size_t);
    ~ThreadPool();
    template<class F,class... Argv>
    auto push(F&&function,Argv&&... argv)
        -> std::future<typename std::result_of<F(Argv...)>::type>;
private:
    //工作线程集合
    std::vector< std::thread > works;
    //工作任务队列
    std::queue< std::function<void()> > tasks;
    //队列锁
    std::mutex queue_mutex;
    //条件变量
    std::condition_variable condition;
    //停止信号
    bool stop;
    //允许最大线程数
    const size_t max_threads = 200;
};


