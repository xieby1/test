// fork
#include <sys/types.h>
#include <unistd.h>

// mq
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

// waitpid
#include <sys/wait.h>

// printf
#include <stdio.h>

const char *mqName = "/mt-helloMQ";

int main(void)
{
    pid_t pid = fork();

    mqd_t mqd;
    int msg_len = 22; // include '\0'
    if(pid > 0)
    { // parent
        mqd = mq_open(mqName, O_RDWR);
        const char *msg = "Msg send from parent\n";
        mq_send(mqd, msg, msg_len, 0);

        int wstatus;
        waitpid(pid, &wstatus, 0);
    }
    else if(pid == 0)
    { // child
        mqd = mq_open(mqName, O_RDWR);

        char msg[msg_len];
        int receivedSize;
        do
        {
            receivedSize = mq_receive(mqd, msg, msg_len, NULL);
        }
        while (receivedSize <= 0);
        printf("%s\n", msg);
    }

    mq_close(mqd);
    mq_unlink(mqName);
    return 0;
}
