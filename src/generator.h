#ifndef _H_GENERATOR_
#define _H_GENERATOR_

#include "common.h"
bool check_solution(int w, int h, int punk_num, vector< vector<int> > &painted_map, vector< vector<int> > &map, vector< vector<int> > &answer);
void send_msg_to_solver(int w, int h, vector< vector<int> > &answer);
void adjust_difficulty(int &w, int &h, int time);
void generate_hidato(int w, int h, vector< vector<int> > &map, vector< vector<int> > &answer);
void generate_not_unique_hidato(int w, int h, vector< vector<int> > &map,vector< vector<int> > &answer);
int check_answer(int w, int h, vector< vector<int> > &answer);
int make_punk(int w,int h, vector< vector<int> > &map);
void *start_generate_hidato (void *sem_id);
void paint_map(int y, int x, int w, int h, int punk_num, int cnt_block, bool &cycle_avail, vector< vector<int> > &map, vector< vector<int> > &painted_map, vector< vector<int> > &answer);
bool check_punk(int p_w,int p_h,int w,int h,vector< vector<int> >&map);
void make_unique_solution(int x, int y, int w, int h, int target_solution, int cnt, bool &find_answer, vector< vector <int> > &painted_map, vector< vector <int> > &map);
void padding(vector< vector <int> > &map, vector< vector <int> > &answer);
#endif
