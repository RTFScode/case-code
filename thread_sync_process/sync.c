#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

//num在这里就是一个共享资源
static unsigned int num;

//定义互斥锁和自旋锁  可以采用显示的调用初始化函数进行初始化
static pthread_mutex_t mutex; //= PTHREAD_MUTEX_INITIALIZER;
static pthread_spinlock_t spin;

void* mutex_func1()
{
    pthread_t self;
    self = pthread_self();
    int i = 0;
    for(i=0;i<10;i++)
    {
        pthread_mutex_lock(&mutex);
        num++;
        printf("i am the child thread2:%u,num=%u\n",self,num);
        pthread_mutex_unlock(&mutex);
    }
}

void* mutex_func2()
{
    int i = 0;
    pthread_t self;
    self = pthread_self();
    for(i=0;i<10;i++)
    {
        pthread_mutex_lock(&mutex);
        num++;
        printf("i am child thread2:%u,num=%u\n",self,num);
        pthread_mutex_unlock(&mutex);
    }
}


void* spin_func1()
{
    int i=0;
    pthread_t self;
    self = pthread_self();
    for(i=0;i<10;i++)
    {
        pthread_spin_lock(&spin);
        num++;
        printf("i am the child thread2:%u,num=%u\n",self,num);
        pthread_spin_unlock(&spin);
    }
}

void* spin_func2()
{
    int i=0;
    pthread_t self;
    self = pthread_self();
    for(i=0;i<10;i++)
    {
        pthread_spin_lock(&spin);
        num++;
        printf("i am child thread2:%u,num=%u\n",self,num);
        pthread_spin_unlock(&spin);
    }
}

unsigned int get_systime()
{
    struct timeval time_val;
    gettimeofday(&time_val,NULL);
    return time_val.tv_sec*1000000+time_val.tv_usec;
}


int main()
{
    //自旋锁需要显示调用初始化函数，否则获取不到锁资源
    pthread_spin_init(&spin,PTHREAD_PROCESS_SHARED);
    //初始化互斥所
    /*  第二个参数是互斥锁的属性
     *  pthread_mutexattr_t mutex_attr;
     *  pthread_mutexattr_init(&mutex_attr);
     *  pthread_mutexattr_setpshared(&mutex_attr,PTHREAD_PROCESS_SHARED);
     *  pthread_mutex_init(&mutex,&mutex_attr);
	 *	pthread_mutexattr_destroy(&mutex_attr);	//必须销毁互斥锁属性对象
     * 上面的函数就是设置属性的方式
     * */
    pthread_mutex_init(&mutex,NULL);

    unsigned int time_now = get_systime();
    pthread_t tid1;
    pthread_t tid2;
    pthread_t self;
    int res1;
    int res2;
    res1 = pthread_create(&tid1,NULL,mutex_func1,NULL);
    if(res1 != 0)
    {
        perror("pthread_create1\n");
    }
    res2 = pthread_create(&tid2,NULL,mutex_func2,NULL);
    if(res2 != 0)
    {
        perror("pthread_create2\n");
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    unsigned int time_mutex_over = get_systime();
    printf("mutex_use_time:%u\n",time_mutex_over-time_now);
    
    pthread_t tid3,tid4;
    int res3,res4;
    
    res3 = pthread_create(&tid3,NULL,spin_func1,NULL);
    if(res3 != 0)
    {
        perror("pthread_create3\n");
    }
    res4 = pthread_create(&tid4,NULL,spin_func2,NULL);
    if(res4 != 0)
    {
        perror("pthread_create4\n");
    }
    //使用pthread_join回收线程资源，或者使用pthread_detach进行分离
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
    unsigned int time_end = get_systime();
    printf("spin_use_time:%u\n",time_end-time_mutex_over);
    //销毁自旋锁
    pthread_spin_destroy(&spin);
    //销毁互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}
