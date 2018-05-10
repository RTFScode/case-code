```
make 		//编译
./sync 		//执行
make clean	//清理
```

## 验证多线程下资源的竞争情况
- 同时各创建两个互斥锁和自选锁的线程
  - 多执行几次`./sync`可以看到两个线程的执行是相互交错的，在互斥锁的线程开始之前记录当前时间(微秒级别)，在互斥锁的两个线程join之后，获取当前时间，做差，得到mutex消耗的时间。
  - 同时开始执行spin自旋锁的线程，以同样的方式获取时间。
```
//资源竞争打印
....
i am child thread2:1737496320,num=8
i am the child thread2:1745889024,num=9
i am the child thread2:1745889024,num=10
i am the child thread2:1745889024,num=11
i am the child thread2:1745889024,num=12
i am the child thread2:1745889024,num=13
i am the child thread2:1745889024,num=14
i am the child thread2:1745889024,num=15
i am the child thread2:1745889024,num=16
i am the child thread2:1745889024,num=17
i am the child thread2:1745889024,num=18
i am child thread2:1737496320,num=19
i am child thread2:1737496320,num=20
...
//耗时
mutex_use_time:539
spin_use_time:287
```
## 结论
- 多线程下的资源是互相竞争的，对于共享资源必须有同步机制。
- 自旋锁貌似比互斥锁在时间性能上有一定的优势，但是自旋锁由于需要循环等待，如果自旋锁同时被很多个线程竞争则在系统性能上有影响。
