#ifndef _H_SOLVER_
#define _H_SOLVER_

#include "common.h"

void *start_solver_hidato (void *sem_id);
void solve_hidato_puzzle(vector< vector<int> > &ans);
bool check_duplication(vector< vector<int> > &ans);
void send_msg_to_generator(vector< vector<int> > &ans);

#endif

