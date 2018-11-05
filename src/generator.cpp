#include "generator.h"

void *start_generate_hidato (void *sem_id)
{
    sem_t *sem = (sem_t *)sem_id;
    sem_t generator = sem[0];
    sem_t solver = sem[1];

    while (1) {
        
    }
}
