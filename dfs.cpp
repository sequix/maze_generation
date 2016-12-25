// Generate maze with DFS.
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50;   // maximum size of the maze MAXN * MAXN
const int reverse_dir[] = {2, 3, 0, 1};

struct P {
    int r, c;
    P(int r=0, int c=0): r(r), c(c) {}
};

stack<P> stk;
int row, col;
bool vis[MAXN][MAXN];
bool haswall[MAXN][MAXN][4];

// return a random positive integer ranged in [left, right]
int random(int left, int right)
{
    return ((double)rand() / RAND_MAX) * (right - left + 1) + left; 
}

// move point (r,c) along d direction (0 up, 1right, 2 down, 3 left)
void move(int r, int c, int &nr, int &nc, int d)
{
    switch(d) {
        case 0: nr = r - 1; nc = c; break;
        case 1: nr = r; nc = c + 1; break;
        case 2: nr = r + 1; nc = c; break;
        case 3: nr = r; nc = c - 1; break;
    }
}

// generation of the maze
void generate()
{
    memset(haswall, 1, sizeof(haswall));
    P src(random(0, row-1), random(0, col-1));
    printf("%d %d\n", src);

    stk.push(src);
    while(!stk.empty()) {
        int nr, nc, d, rd;
        bool backtrack = true;
        int r = stk.top().r, c = stk.top().c;
        vis[r][c] = 1;

        for(int i = 0; i < 4; ++i) {
            move(r, c, nr, nc, i);
            if(0<=nr&&nr<row && 0<=nc&&nc<col && !vis[nr][nc]) {
                backtrack = false;
                break;
            }
        }

        if(backtrack) {
            stk.pop();
            continue;
        }

        while(1) {
            d = random(0, 3);
            move(r, c, nr, nc, d);
            if(0<=nr&&nr<row && 0<=nc&&nc<col && !vis[nr][nc]) break;
        }
        haswall[r][c][d] = 0;
        haswall[nr][nc][reverse_dir[d]] = 0;
        stk.push(P(nr, nc));
    }
}

int main(int argc, char *argv[])
{
    if(argc != 3) {
        fprintf(stderr, "usage: %s ROW COL\n", argv[0]);
        exit(1);
    }

    srand(time(0));
    row = atoi(argv[1]);
    col = atoi(argv[2]);

    generate();

    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            printf("%d %d", i, j);
            for(int k = 0; k < 4; ++k)
                printf(" %d", haswall[i][j][k]);
            putchar(10);
        }
    }
    return 0;
}
