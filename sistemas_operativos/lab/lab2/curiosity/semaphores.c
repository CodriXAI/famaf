#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int main() {
    sem_t s;
    sem_init(&s, 0, 1); // inicializa en 1 (tipo mutex)

    printf("Semáforo inicializado.\n");

    sem_destroy(&s);
    return 0;
}
