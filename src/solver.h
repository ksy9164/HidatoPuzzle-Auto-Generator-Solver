#ifndef _H_SOLVER_
#define _H_SOLVER_

#include "common.h"

void *start_solver_hidato (void *sem_id);
void solve_hidato_puzzle(vector< vector<int> > &ans);
bool check_duplication(vector< vector<int> > &ans);
void send_msg_to_generator(vector< vector<int> > &ans);
void check_hidato(int y, int x, int w, int h, int cnt_block, int cnt, bool &solving_puzzle, vector< vector<int> > &quize, vector< vector<int> > &ans);
void print_ans(vector< vector <int> > &ans );
#endif

