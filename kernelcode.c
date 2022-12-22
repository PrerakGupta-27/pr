#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void *philosopher(void *id);

int main(){
    pthread_t philosophers[5];

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)(intptr_t)i);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

void *philosopher(void *id)
{
int philosopher_id = (int)(intptr_t)id;
int left_fork = philosopher_id;
int right_fork = (philosopher_id + 1) % 5;

while (1)
{
    printf("Philosopher %d is thinking\n", philosopher_id);
    sleep(1);

    printf("Philosopher %d is picking up left fork %d\n", philosopher_id, left_fork);

    printf("Philosopher %d is picking up right fork %d\n", philosopher_id, right_fork);

    printf("Philosopher %d is eating\n", philosopher_id);
    sleep(1);

    printf("Philosopher %d is putting down left fork %d\n", philosopher_id, left_fork);
    printf("Philosopher %d is putting down right fork %d\n", philosopher_id, right_fork);
}

return NULL;
}
