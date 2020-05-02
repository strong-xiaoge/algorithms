#define MODE    1
/**
 * 1.快速排序
 * 2.冒泡排序
 * 3.插入排序
 * 4.选择排序
 * 5.希尔排序
 * 6.归并排序
 * 7.堆排序
 * 8.计数排序
 * 9.桶排序
 * 10.基数排序
*/

#define NULL    (void*)0
/**
 * 快速排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void quickSort(int*const start,const int size){
    if(size<=0||start==NULL)return;
    int l=0,r=size-1;
    int key=start[l];
    while(l<r){
        while(l<r&&start[r]>=key)--r;
        start[l]=start[r];
        while(l<r&&start[l]<=key)++l;
        start[r]=start[l];
    }
    start[l]=key;
    quickSort(start,l);
    quickSort(start+l+1,size-l-1);
}

/**
 * 冒泡排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void bubbleSort(int*const start,const int size){
    if(start==NULL)return;
    for(int i=size-1;i>0;--i){    
        for(int j=0;j<i;++j){
            if(start[j]>start[j+1]){
                int temp=start[j];
                start[j]=start[j+1];
                start[j+1]=temp;
            }
        }
    }
}

/**
 * 插入排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void insertSort(int*const start,const int size){
    if(start==NULL)return;
    for(int i=1;i<size;++i){
        if(start[i]<start[i-1]){
            int temp=start[i];
            int j=i-1;
            while(j>=0&&start[j]>temp){
                start[j+1]=start[j];
                --j;
            }
            start[j+1]=temp;
        }
    }
}

/**
 * 选择排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void selectionSort(int*const start,const int size){
    if(start==NULL)return;
    for(int i=0;i<size-1;++i){   
        int min=i;
        for(int j=i;j<size;++j){
            if(start[j]<start[min]){
                min=j;
            }
        }
        if(min!=i){
            int temp=start[i];
            start[i]=start[min];
            start[min]=temp;
        }
    }
}

/**
 * 希尔排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void shellSort(int*const start,const int size){
    if(start==NULL)return;
    for(int step=size/2;step>0;step/=2){
        for(int group=0;group<step;++group){
            for(int i=group+step;i<size;i+=step){
                if(start[i]<start[i-step]){
                    int temp=start[i];
                    int j=i-step;
                    while(j>=0&&start[j]>temp){
                        start[j+step]=start[j];
                        j-=step;
                    }
                    start[j+step]=temp;
                }
            }
        }
    }
}

/**
 * 归并排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void mergeSort(int*const start,const int size){
    if(start==NULL)return;
    
}

/**
 * 堆排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void heapSort(int*const start,const int size){
    if(start==NULL)return;
    
}

/**
 * 计数排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
#include <stdlib.h>
#include <string.h>
void countingSort(int*const start,const int size){
    if(start==NULL||size<=0)return;
    int min,max;
    min=max=start[0];
    for(int i=0;i<size;++i){
        if(start[i]<min)min=start[i];
        else if(start[i]>max)max=start[i];
    }
    unsigned int range=max-min;
    int*const count = malloc((range+1)*sizeof(range));
    memset(count,0,(range+1)*sizeof(range));
    for(int i=0;i<size;++i)count[start[i]-min]++;
    int index=0;
    for(unsigned int i=0;i<=range;++i)
        while(count[i]--)start[index++]=i+min;
    free(count);
}
/**
 * 桶排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void bucketSort(int*const start,const int size){
    struct pag{
        int val;
        struct pag*next;
    };
    if(start==NULL||size<=0)return;
    int min,max;
    min=max=start[0];
    for(int i=0;i<size;++i){
        if(start[i]<min)min=start[i];
        else if(start[i]>max)max=start[i];
    }
    const int bucketnum = 10;
    struct pag* buckets = malloc(bucketnum*sizeof(struct pag));
    int bucketsize = (max-min)/bucketnum+1;
    for(int i=0;i<size;++i){
        int index=start[i]/bucketsize;
        struct pag*node=buckets[index].next;
        struct pag*lastnode=&buckets[index];
        while(node&&node->val<start[i]){
            lastnode=node;
            node=node->next;
        }
        lastnode->next = malloc(sizeof(struct pag));
        lastnode=lastnode->next;
        lastnode->val=start[i];
        lastnode->next=node;
    }
    int index=0;
    for(int i=0;i<bucketnum;++i){
        struct pag*node=buckets[i].next;
        while(node){
            start[index++]=node->val;
            node=node->next;
        }
    }
    /**释放内存**/
}

/**
 * 基数排序
 * start : 数组的起始指针
 * size  : 待排序的数组大小
*/
void redixSort(int*const start,const int size){
    if(start==NULL)return;
    
}

#include <stdio.h>
int main(){
    int data[]={1,5,7,2,3,9,-1,6,4,8,3,4,5,2,8,1,9,23,56,2,3,-3};
    int size = sizeof(data)/sizeof(data[0]);
    for(int i=0;i<size;++i)
        printf("%d ",data[i]);
    printf("\n");
    printf("size:%d\n",size);
    switch(MODE){
        case 1:quickSort(data,size);printf("quickSort...\n");break;
        case 2:bubbleSort(data,size);printf("bubbleSort...\n");break;
        case 3:insertSort(data,size);printf("insertSort...\n");break;
        case 4:selectionSort(data,size);printf("selectionSort...\n");break;
        case 5:shellSort(data,size);printf("shellSort...\n");break;
        case 6:mergeSort(data,size);printf("mergeSort...\n");break;
        case 7:heapSort(data,size);printf("heapSort...\n");break;
        case 8:countingSort(data,size);printf("countingSort...\n");break;
        case 9:bucketSort(data,size);printf("bucketSort...\n");break;
        case 10:redixSort(data,size);printf("redixSort...\n");break;
    }

    for(int i=0;i<size;++i)
        printf("%d ",data[i]);
    printf("\n");
    getchar();
    return 0;
}
