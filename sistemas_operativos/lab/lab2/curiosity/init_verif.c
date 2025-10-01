#include <stdio.h>

typedef struct {
    int value;
    int used;
} sem_s;

#define N 5
sem_s sem_array[N];   // global

int main() {
    for (int i = 0; i < N; i++) {
        printf("sem_array[%d].used = %d\n", i, sem_array[i].used);
    }
    return 0;
}
