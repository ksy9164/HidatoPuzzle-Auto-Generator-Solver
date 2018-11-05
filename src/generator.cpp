#include "generator.h"

void *start_generate_hidato (void *sem_id)
{
    sem_t *sem = (sem_t *)sem_id;
    sem_t *generator = &sem[0];
    sem_t *solver = &sem[1];

    int w = 5;
    int h = 5;
    
    clock_t begin,end;
    int time;
    int iter = 0;
    int check = 1;
    vector< vector<int> > map;

    while (1) {
        sem_wait(generator);
        end = clock();
        check = check_answer(w,h,map);

        if (check == 0) {
            cout << "\n It is wrong answer ";
            return NULL;
        } else if (check == -1) {
            cout << "\n duplicated sollution !! \n";
            return NULL;
        }

        if (iter != 0) {
            time = end - begin;
            adjust_difficulty(w,h,time);
        }

        map.resize(h,vector<int>(w,0));

        switch (GENERATOR_HANDLE) {
            case 0:
                generate_not_unique_hidato(w,h,map);
                break;
            case 1:
                generate_hidato(w,h,map);
                break;
        }
        send_msg_to_solver(w,h,map);
        sem_post(solver);
        begin = clock();
        iter++;
    }
}
void send_msg_to_solver(int w, int h, vector< vector<int> > &map)
{
    ofstream out;
    out.open(F_QUIZE);

    out << h << " " << w << endl;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            out << map[i][j] << " ";        
        }
        out << endl;
    }
}
int check_answer(int w, int h, vector< vector<int> > &map)
{
    int answer = 1;
    /* TODO */
    /* open answer.txt and compare between map array */

    return answer;
}
void generate_hidato(int w, int h, vector< vector<int> > &map)
{
    /* TODO */
    /* generate (w X h) hidato puzzle
     * ans write to quize.txt
     * this puzzle's solution must be unique */
}
void generate_not_unique_hidato(int w, int h, vector< vector<int> > &map)
{
    /* TODO */
    /* generate (w X h) hidato puzzle
     * ans write to quize.txt
     * this puzzle's solution must be NOT!! unique */
}
void adjust_difficulty(int &w, int &h, int time)
{
    /* TODO */
/* 
 *     adjust difficulty ( w and h )
 *     by referring to the time */
}
