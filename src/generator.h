#ifndef _H_GENERATOR_
#define _H_GENERATOR_

#include "common.h"

void send_msg_to_solver(int w, int h, vector< vector<int> > &map);
void adjust_difficulty(int &w, int &h, int time);
void generate_hidato(int w, int h, vector< vector<int> > &map);
void generate_not_unique_hidato(int w, int h, vector< vector<int> > &map);
int check_answer(int w, int h, vector< vector<int> > &map);
void *start_generate_hidato (void *sem_id);

#endif
