#include <mqueue.h>   
#include <stdio.h>

int main(void)
{
    struct mq_attr attr;

    // mq attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 4;
    attr.mq_curmsgs = 0;

    // open a message queue
    mqd_t mq = mq_open("/mq_receive", O_CREAT | O_RDONLY, 0644, &attr);
    mqd_t mq2 = mq_open("/mq_receive", O_WRONLY);
    if(mq==-1)
        perror("mq_open error\n");
    if(mq2==-1)
        perror("mq_open2 error\n");
    char buffer[attr.mq_msgsize];

    //int err = mq_send(mq2, buffer, attr.mq_msgsize, 0);
    //if(err==-1)
      //  perror("!");
    int err = mq_receive(mq, buffer, attr.mq_msgsize, NULL);
    if(err==-1)
        perror("!");
    err = mq_receive(mq, buffer, attr.mq_msgsize, NULL);
    if(err==-1)
        perror("!");
}
