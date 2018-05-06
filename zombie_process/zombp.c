/*
 * date: 2018-5
 * author: lk
 * decription: This is an example of creating a zombie process.The parent process and child process is running,when the child process terminates,but the parent process doesn't call wait(),
 * until before the end of parent process,the child process is a zombie process,the parent process exits,zombie resource releases.
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
    pid_t pid;
    
    printf("before fork()\n");

    pid = fork();
    if(pid < 0){
        printf("fork() failed.\n");
        return -1;
    }else if(pid == 0){
        printf("I'm the child process,my process id is %d.I'm going to quit after 1 seconds\n",getpid());
        sleep(1);
        printf("child process quits.\n");
    }else{
        printf("I'm the parent process,my process id is %d.no wait() for child process,After child process quits,the system zombie adds one\n",getpid());
        sleep(20);
        printf("After 20 seconds,parent process quits,the system zombie minuses one.\n");
    }
    return 0;
}
