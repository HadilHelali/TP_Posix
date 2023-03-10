#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* fonc(void* arg) {
	int i;
	int*  data = (int*)(arg);
    int   x    = *data;
	for (i = 0; i < 7; i++) {
		printf("Tache %d : %d\n", x, i);
		usleep(1000000);
	}
}

int main(void) {

	pthread_t tache1, tache2;
	pthread_attr_t attr;
	struct sched_param param;
	pthread_attr_init(&attr);
	param.sched_priority = 12;
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	//pthread_attr_setinheritpolicy(&attr, SCHED_FIFO);
	param.sched_priority = 10;
	pthread_attr_setschedparam(&attr, &param);
	pthread_create(&tache1, &attr, fonc, (void*)1);
	param.sched_priority = 7;
	pthread_attr_setschedparam(&attr, &param);
	pthread_create(&tache2, &attr, fonc, (void*)2);
	pthread_attr_destroy(&attr);
	pthread_join(tache1, NULL);
	pthread_join(tache2, NULL);
	return 0;

}