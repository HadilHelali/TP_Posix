#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* fonc(void* arg) {
	int*  data = (int*)(arg);
    int   x    = *data;
	int i;
	for (i = 0; i < 7; i++) {
		printf("Tache %d : %d\n", x, i);
			usleep(1000000);
	}
}

int main(void) {
	pthread_t tache1, tache2;


	pthread_create(&tache1, NULL, fonc, (int*)1);
	pthread_create(&tache2, NULL, fonc, (int*)2);

	pthread_join(tache1, NULL);
	pthread_join(tache2, NULL);

	return 0;
}