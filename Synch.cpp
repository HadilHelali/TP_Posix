#include<stdio.h>
#include<stdlib.h> 
#include<pthread.h>
#include<semaphore.h>

sem_t evt;

void* tache1(void* arg) {
	int i = 0;
	while (i < 10) {
		printf("La tache %s s'execute\n", (char*) arg);
		i++;
	}
	return 0;
}

int main() {

	pthread_t th1, th2;
	sem_init(&evt, 0, 0);
	char* var1 = (char*) malloc(1);
	char* var2 = (char*) malloc(1);
	*var1 = '1';
	*var2 = '2';
	pthread_create(&th1, NULL, tache1, var1);
	pthread_create(&th2, NULL, tache1, var2);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	return 0;

}