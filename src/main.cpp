#include "solver.h"
#include "generator.h"
using namespace std;

int main(void)
{
    pthread_t p_thread[2];
    int status;
    sem_t sem_id[2];

    sem_init(&sem_id[0], 0, 1);
    sem_init(&sem_id[1], 0, 0);
    
    pthread_create(&p_thread[0], NULL, start_generate_hidato,(void *)&sem_id);
    pthread_create(&p_thread[1], NULL, start_solver_hidato,(void *)&sem_id);
    
    pthread_join(p_thread[0],(void **)&status);
    pthread_join(p_thread[1],(void **)&status);

    return 0;
}
