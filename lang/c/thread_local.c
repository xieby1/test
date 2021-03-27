// to test thread local
// the normal pointer expected to be equal among main, t1, t2
// the local pointer expected to be different among main, t1, t2

#include<stdio.h> /* printf */
#include<pthread.h> /* pthread_create, pthread_join */

int normal;
__thread int local;

void *print(void *str)
{
    printf("%s: snormal@%p, local@%p\n", (char*)str, &normal, &local);

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    print("main");
    pthread_create(&t1, NULL, print, "t1  ");
    pthread_create(&t2, NULL, print, "t2  ");

    // to prevent main exit before t1 and t2, pthread_join is neccessory
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
