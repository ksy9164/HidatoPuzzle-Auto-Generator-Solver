#include "solver.h"

void *start_solver_hidato (void *sem_id)
{
    sem_t *sem = (sem_t *)sem_id;
    sem_t generator = sem[0];
    sem_t solver = sem[1];

    vector< vector<int> > ans;
    
    bool check;

    while (1)
    {
        sem_wait(&solver);
        
        check = check_duplication(ans);
        if (check == true) {
            cout << "\n This hidato pulzzle has not unique solution \n";
            send_msg_to_generator(ans);
            sem_post(&generator);
            /* exit function */
            return (void *)check;
        }

        solve_hidato_puzzle(&generator, &solver, ans);
        
        sem_post(&generator);
    }
}

void solve_hidato_puzzle(sem_t *generator, sem_t *solver, vector< vector<int> > &ans)
{
    /* TODO */
    /* open quize.txt and solve the hidato
     * if this function solves generator's quize
     * than you have to use send_msg_to_gernerator function to write answer.txt file */
}

bool check_duplication(vector< vector<int> > &ans)
{
    /* TODO */

    /* check duplicate
     * if this hidato is unique
     *     => return 0;
     * if this hidato is not unique
     *     => write -1 to ans array  and return 1 */
}

void send_msg_to_generator(vector< vector<int> > &ans)
{
    ofstream out;
    out.open("answer.txt");

    for (int i = 0; i < (int)ans.size(); ++i) {
        for (int j = 0; j < (int)ans[0].size(); ++j) {
            out << ans[i][j] << " ";
        }
        out << endl;
    }

    return ;
}
