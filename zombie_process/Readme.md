1、僵尸进程<br>
&emsp;&emsp;概念：主进程创建子进程，但主进程不调用wait/waitpid回收子进程资源，当子进程先于主进程退出且没有被wait/waitpid回收进程资源时，在主进程退出之前，子进程将保持僵尸进程状态；主进程退出时，系统扫描所有进程信息，将属于该主进程的所有子进程交接给Init进程管理，Init进程会自动wait其子进程，僵尸进程被处理。<br>

2、示例<br>
&emsp;\# make clean；make<br>
&emsp;\# ./zombp<br>
&emsp;zombp进程运行后，可以通过htop工具F4过滤查看zombp运行情况：

- 开始运行：<br>
&emsp;|_ ./zombp<br>
&emsp;&emsp;|_./zombp
- 运行1秒子进程退出：<br>
&emsp;|_ ./zombp<br>
&emsp;&emsp;|_ zombp     //变成僵尸进程<br>
&emsp;同时通过top命令可以看到zombie值变成1；
- 运行21秒主进程退出：<br>
&emsp;主进程退出，僵尸子进程资源由Init进程接管回收，top命令zombie值变成0。
 
 3、清理<br>
- 查找僵尸进程：<br>
&emsp;ps -A -ostate,ppid,pid,cmd | grep -e '^[Zz]'<br>
&emsp;ps -A&emsp;列出系统所有进程信息；<br>
&emsp;ps -o&emsp;自定义输出展示字段state（进程状态）,ppid（父进程id）,pid（当前进程id）,cmd（运行命令）；<br>
&emsp;grep -e 启用正则表达式；'^[Zz]'：Z表示僵尸进程，匹配行首。<br>
- 清理僵尸进程：<br>
&emsp;通过kill父进程来处理僵尸进程，原理如1中描述。<br>
