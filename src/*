#include "generator.h"

void *start_generate_hidato (void *sem_id)
{
    sem_t *sem = (sem_t *)sem_id;
    sem_t *generator = &sem[0];
    sem_t *solver = &sem[1];

    int w = 5;
    int h = 5;
    
    clock_t begin,end;
    int time_check;
    int iter = 0;
    int check = 1;
    vector< vector<int> > map;
    vector< vector<int> > answer;

    srand((unsigned int)time(NULL));
    while (1) {
        sem_wait(generator);
        end = clock();
        sleep(1);
        if (iter > 0)
            check = check_answer(w,h,answer);
        if (check == 0) {
            cout << "\n It is wrong answer ";
            fflush(stdout);
            return NULL;
        } else if (check == -1) {
            cout << "\n duplicated sollution !! \n";
            fflush(stdout);
            return NULL;
        }
        if (iter != 0) {
            time_check = end - begin;
            adjust_difficulty(w,h,time_check);
        }

        map.resize(h,vector<int>(w,-1));
        answer.resize(h,vector<int>(w,-1));
        
        switch (GENERATOR_HANDLE) {
            case 0:
                generate_not_unique_hidato(w,h,map,answer);
                break;
            case 1:
                generate_hidato(w,h,map,answer);
                break;
        }
        send_msg_to_solver(w,h,map);
        sem_post(solver);
        begin = clock();
        iter++;
    }
}
void send_msg_to_solver(int w, int h, vector< vector<int> > &answer)
{
    ofstream out;
    out.open(F_QUIZE);

    out << h << " " << w << endl;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            out << answer[i][j] << " ";        
        }
        out << endl;
    }
}
int check_answer(int w, int h, vector< vector<int> > &answer)
{
    ifstream in;
    in.open(F_ANSWER);

    int t;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; j++) {
            in >> t;
            if (t != answer[i][j]) {
                return 0;
            }
        } 
    }
    return 1;
}
void generate_hidato(int w, int h, vector< vector<int> > &map, vector< vector<int> > &answer)
{
    bool find_answer = false;
    int i,x,y;

    vector < vector<int> > painted_map(h,vector<int> (w ,0));

    /* this is max solution road */
    int max_solution = (h + 1) / 2 * (w - 1) + 1;

    int target_solution = 0;
    /* set difficulty */
    while (target_solution < max_solution / 5 * 4) {
        target_solution = rand() % max_solution;
    }

    vector < vector<int> > checked_map(h,vector<int> (w ,0));
    i = 0;

    while (i < w * h) {
        /* init array */
        map.clear();
        painted_map.clear();
        map.resize(h,vector<int>(w,0));
        painted_map.resize(h,vector<int>(w,0));
        
        x = rand() % w;
        y = rand() % h;
        if (checked_map[y][x] == 1) {
            continue;
        }
        else {
            make_unique_solution(x, y, w, h, target_solution, 1, find_answer, painted_map, map);
            checked_map[y][x] = 1;
            i++;
            if (find_answer == false)
                continue;
            else {
                break;
            }
        }
    }
    
    cout << "\n\n--------------------------\n";
    cout << "--------------------------\n";
    cout << "This is Unique Solution !! \n";
    for (i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cout << map[i][j] << "     ";
            answer[i][j] = map[i][j];
        }
        cout << endl;
    }
    return;
}
void make_unique_solution(int x, int y, int w, int h, int target_solution, int cnt, bool &find_answer,vector< vector <int> > &painted_map, vector< vector <int> > &map)
{
    int i,tx,ty;
    int x_pos[8] = {-1,-1,-1,0,0,1,1,1};
    int y_pos[8] = {1,0,-1,1,-1,1,0,-1};
    /* if find the answer?? */
    if (find_answer)
        return;
    if (cnt == target_solution) {
       for (int i = 0; i < h; ++i) {
           for (int j = 0; j < w; j++) {
               map[i][j] = painted_map[i][j];
           }
       }
       find_answer = true;
       return;
    }
    /* check area */
    for (i = 0; i < 8; i++) {
        tx = x_pos[i] + x;
        ty = y_pos[i] + y;

        if (ty < 0 || tx < 0 || tx >= w || ty >= h || painted_map[ty][tx] == cnt - 1)
            continue;
        else if (painted_map[ty][tx] != 0)
            return;
    }

    /* draw! it is unique map */
    painted_map[y][x] = cnt;
    
    /* find next target! */
    for (i = 0; i < 8; i++) {
        tx = x_pos[i] + x;
        ty = y_pos[i] + y;

        if (ty < 0 || tx < 0 || tx >= w || ty >= h)
            continue;
        else if (painted_map[ty][tx] == 0)
            make_unique_solution(tx, ty, w, h, target_solution, cnt + 1, find_answer, painted_map, map);
    }
    painted_map[y][x] = 0;
}
void generate_not_unique_hidato(int w, int h, vector< vector<int> > &map, vector< vector<int> > &answer)
{
    int i,j,punk_num;
    vector < vector<int> > painted_map(h,vector<int> (w ,0));
    while (1) {
        /* map init */
        map.clear();
        painted_map.clear();
        map.resize(h,vector<int>(w,-1));
        painted_map.resize(h,vector<int> (w ,0));

        punk_num = make_punk(w, h, map);
        if (check_solution(w, h, punk_num, painted_map, map ,answer))
            break;
    } 

    cout << "--------------------------\n";
    cout << "--------------------------\n";
    cout << "\n\nThis is Not Unique Solution !! \n";
    for (i = 0; i < h; ++i) {
        for (j = 0; j < w; ++j) {
            cout << map[i][j] << "     "; 
        }
        cout << endl;
    }
    return;
}
void adjust_difficulty(int &w, int &h, int time)
{
    /* TODO */
    /* 
     *     adjust difficulty ( w and h )
     *     by referring to the time */
}
int make_punk(int w,int h, vector< vector<int> > &map)
{
    int punk_num, p_w, p_h, i;
    bool punk_avail;
    /* checking map for make punk.. */
    vector < vector<int> > checked_map(h,vector<int> (w ,0));
    map.resize(h,vector<int> (w ,-1));
    punk_num = 0; 
    i = 0;
    while (i < w * h) {
        p_w = rand() % w;
        p_h = rand() % h;
        if (checked_map[p_h][p_w] == 1) {
            continue;
        }
        else {
            punk_avail = check_punk(p_w, p_h, w, h, map);
            checked_map[p_h][p_w] = 1;
            i++;
            if (punk_avail == false)
                continue;
            else {
                map[p_h][p_w] = 0;
                punk_num++;
            }
        }
    }
    return punk_num;
}
bool check_punk(int p_w, int p_h, int w, int h, vector< vector<int> >&map)
{
    int x_pos[8] = {-1,-1,-1,0,0,1,1,1};
    int y_pos[8] = {1,0,-1,1,-1,1,0,-1};

    int tx,ty,i,j,near_road;
    
    bool punk_avail;
    
    /* make punk */
    map[p_h][p_w] = 0;
    punk_avail = true;

    /* check nearby */
    for (i = 0; i < 8; i++) {
        tx = x_pos[i] + p_w;
        ty = y_pos[i] + p_h;
        if (ty < 0 || tx < 0 || tx >= w || ty >= h || map[ty][tx] == 0) {
            continue;
        }
        else {
            /* check each pos */
            near_road = 0;
            for (j = 0; j < 8; ++j) {
                int n_tx = tx + x_pos[j];
                int n_ty = ty + y_pos[j];
                if (n_ty < 0 || n_tx < 0 || n_ty >= w || n_tx >= h)
                    continue;
                else if (map[n_ty][n_tx] == -1)
                    near_road++;
            }
            if (near_road < 2)
                punk_avail = false;
        }
    }
    map[p_h][p_w] = -1;
    return punk_avail;
}
bool check_solution(int w, int h, int punk_num, vector< vector<int> > &painted_map, vector< vector<int> > &map, vector< vector<int> > &answer)
{
    bool cycle_avail;
    int i,j; 
    for (i = 0; i < h; ++i) {
        for (j = 0; j < w; ++j) {
            cycle_avail = false;
            if (map[i][j] == -1) {
                paint_map(i, j, w, h, punk_num, 1,cycle_avail, map, painted_map, answer);
                if (cycle_avail == true) {
                    map[i][j] = 1;
                    return true;
                }

            }
        }
    }
    return false;
}
void paint_map(int y, int x, int w, int h, int punk_num, int cnt_block, bool &cycle_avail, vector< vector<int> > &map, vector< vector<int> > &painted_map, vector< vector<int> > &answer)
{
    int i,j,tx,ty;
    int x_pos[8] = {-1,-1,-1,0,0,1,1,1};
    int y_pos[8] = {1,0,-1,1,-1,1,0,-1};
    
    painted_map[y][x] = cnt_block;
    
    if ((w * h) - punk_num == cnt_block) {
        cycle_avail = true;
        map[y][x] = painted_map[y][x];

        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j++) {
                answer[i][j] = painted_map[i][j];
            }
        }
        painted_map[y][x] = 0;
        return;
    }
    
    for (i = 0; i < 8; i++) {
        tx = x_pos[i] + x;
        ty = y_pos[i] + y;
        if (ty < 0 || tx < 0 || tx >= w || ty >= h ) {
            continue;
        } else if (map[ty][tx] == -1 && painted_map[ty][tx] == 0) {
            map[y][x] = 0;
            paint_map(ty, tx, w, h, punk_num, cnt_block + 1, cycle_avail, map, painted_map, answer);
            /* if (!cycle_avail) */
            map[y][x] = -1;
        }
    }
    /* back tracking */
    if (!cycle_avail)
        painted_map[y][x] = 0;
}
