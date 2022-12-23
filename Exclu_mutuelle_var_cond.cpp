#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h>
#include<pthread.h>

typedef struct {
	float taille;
	float poids;
}type_donneePartagee;

pthread_mutex_t verrou;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

type_donneePartagee donneePartagee;

void* tache1(void* arg) {
	type_donneePartagee ma_donneePartagee;
	int i = 0;
	while (i < 10) {
		pthread_mutex_lock(&verrou);
		pthread_cond_wait(&cond,&verrou);
		ma_donneePartagee = donneePartagee;
		pthread_mutex_unlock(&verrou);
		printf("La tache %s vient de lire la donnée partagée \n", (char*)arg);
		usleep(1000000);
		i++;
	}
}

void* tache2(void* arg) {
	type_donneePartagee ma_donnePartagee;
	int i = 0;
	while (i < 10) {
		pthread_mutex_lock(&verrou);
		donneePartagee.taille = 100 + rand() % 101;
		donneePartagee.poids = 10 + rand() % 101;
		if (donneePartagee.taille >= 120 && donneePartagee.poids >= 60) {
			pthread_cond_signal(&cond);
		}
		pthread_mutex_unlock(&verrou);
		printf("La tache %s vient de modifier la donnée partagée \n", (char*)arg);
		usleep(1000000);
		i++;
	}
}

int main(void) {
	pthread_t th1, th2;
	pthread_mutex_init(&verrou, NULL);
	donneePartagee.taille = 100 + rand() % 101;
	donneePartagee.poids = 10 + rand() % 101;
	char* var1 = (char*) malloc(1);
	char* var2 = (char*) malloc(1);
	pthread_create(&th1, NULL, tache1, var1);
	pthread_create(&th2, NULL, tache2, var1);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	return 0;


}