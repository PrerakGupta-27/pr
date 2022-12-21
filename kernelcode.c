#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

void pickup_forks(int philosopher_id) {
// Pick up the left fork
printf("Philosopher %d: Picking up left fork\n", philosopher_id);

// Pick up the right fork
printf("Philosopher %d: Picking up right fork\n", philosopher_id);
}

void return_forks(int philosopher_id) {
// Put down the left fork
printf("Philosopher %d: Putting down left fork\n", philosopher_id);

// Put down the right fork
printf("Philosopher %d: Putting down right fork\n", philosopher_id);
}

void eat(int philosopher_id) {
printf("Philosopher %d: Eating\n", philosopher_id);
sleep(1);
}

void think(int philosopher_id) {
printf("Philosopher %d: Thinking\n", philosopher_id);
sleep(1);
}

void* philosopher_thread(void* philosopher_id_ptr) {
int philosopher_id = ((int) philosopher_id_ptr);

while (1) {
think(philosopher_id);
pickup_forks(philosopher_id);
eat(philosopher_id);
return_forks(philosopher_id);
}

return NULL;
}

int main() {
pthread_t philosophers[NUM_PHILOSOPHERS];
int philosopher_ids[NUM_PHILOSOPHERS];

for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
philosopher_ids[i] = i;
pthread_create(&philosophers[i], NULL, philosopher_thread, &philosopher_ids[i]);
}

for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
pthread_join(philosophers[i], NULL);
}

return 0;
}
