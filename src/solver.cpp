#include "solver.h"
void *start_solver_hidato (void *sem_id)
{
    sem_t *sem = (sem_t *)sem_id;
    sem_t *generator = &sem[0];
    sem_t *solver = &sem[1];

    vector< vector<int> > ans;
    
    bool check = false;

    while (1) {
        sem_wait(solver);
        sleep(1);
        check = check_duplication(ans);
        if (check == true) {
            cout << "\n This hidato pulzzle has not unique solution \n";
            send_msg_to_generator(ans);
            sem_post(generator);
            /* exit function */
            return NULL;
        }

        solve_hidato_puzzle(ans);
        send_msg_to_generator(ans);
        sem_post(generator);
    }
}

void solve_hidato_puzzle(vector< vector<int> > &ans)
{
    ifstream in;
    in.open(F_QUIZE);
    int h, w;
    int cnt_block = 0;
    bool solving_puzzle = false;
    in >> h >> w;
    vector< vector<int> > quize;

    ans.resize(h);
    quize.resize(h);

    for (int i = 0; i < h; ++i) {
        ans[i].resize(w,0);
        quize[i].resize(w,0);
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; j++) {
            in >> quize[i][j];
            if (quize[i][j] != 0)
                cnt_block++;
        }
    }
    in.close();
    
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; j++) {
            if (quize[i][j] == -1 || quize[i][j] == 1)
                check_hidato(i, j, h, w, cnt_block, 1, solving_puzzle, quize, ans);
            if (solving_puzzle)
                goto done;
        }
    }

done :
    print_ans(ans);
    return;
}

void check_hidato(int y, int x, int h, int w, int cnt_block, int cnt, bool &solving_puzzle, vector< vector<int> > &quize, vector< vector<int> > &ans)
{
    /* if solved? */
    if (solving_puzzle)
        return;
    
    /* check is it valuable? */
    if (quize[y][x] != -1 && quize[y][x] != cnt)
        return;
    
    bool map_valid = false;
    if (quize[y][x] == cnt)
        map_valid = true;

    quize[y][x] = cnt;

    if (cnt == cnt_block) {
        solving_puzzle = true;
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; j++)
                ans[i][j] = quize[i][j];
        return;
    }

    int tx,ty;
    int x_pos[8] = {-1,-1,-1,0,0,1,1,1};
    int y_pos[8] = {1,0,-1,1,-1,1,0,-1};

    for (int i = 0; i < 8; i++) {
        tx = x_pos[i] + x;
        ty = y_pos[i] + y;
        if (ty < 0 || tx < 0 || tx >= w || ty >= h )
            continue;
        else
            check_hidato(ty, tx, h, w, cnt_block, cnt + 1, solving_puzzle, quize, ans);
    }
    if (map_valid)
        quize[y][x] = cnt;
    else
        quize[y][x] = -1;
}
bool check_duplication(vector< vector<int> > &ans)
{
    bool check = false;
    /* TODO */

    /* check duplicate
     * if this hidato is unique
     *     => return 0;
     * if this hidato is not unique
     *     => write -1 to ans array  and return 1 */

    return check;
}

void send_msg_to_generator(vector< vector<int> > &ans)
{
    ofstream out;
    out.open(F_ANSWER);
    for (int i = 0; i < (int)ans.size(); ++i) {
        for (int j = 0; j < (int)ans[0].size(); ++j) {
            out << ans[i][j] << " ";
        }
        out << endl;
    }

    out.close();
    return ;
}

void print_ans(vector< vector <int> > &ans)
{
    cout << "--------------------------\n";
    cout << "---- This is solver!! ----\n";
    cout << "--------------------------\n";
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[0].size(); j++) {
            cout << ans[i][j] << "     ";
        }
        cout << endl;
    }
    return;
}
