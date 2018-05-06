1、僵尸进程
  概念：主进程创建子进程，但主进程不调用wait/waitpid回收子进程资源，当子进程先于主进程退出且没有被wait/waitpid回收进程资源时，
在主进程退出之前，子进程将保持僵尸进程状态；主进程退出时，系统扫描所有进程信息，将属于该主进程的所有子进程交接给Init进程管理，
Init进程会自动wait其子进程，僵尸进程被处理。

2、示例
  # make clean；make
  # ./zombp
  zombp进程运行后，可以通过htop工具F4过滤查看zombp运行情况：
  开始运行：
   |_ ./zombp
     |_./zombp
   运行1秒子进程退出：
   |_ ./zombp
     |_ zombp     //变成僵尸进程
   同时通过top命令可以看到zombie值变成1；
   运行21秒主进程退出：
   主进程退出，僵尸子进程资源有Init进程接管回收资源，top命令里面zombie变成0。