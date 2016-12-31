// Generate maze with Prim
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50;   // maximum size of the maze MAXN * MAXN
const int reverse_dir[] = {2, 3, 0, 1};

struct P {
    int u, v, d, w;
    P(int u, int v, int d, int w): u(u), v(v), d(d), w(w) {}
    bool operator<(const P &p) const { return w < p.w; }
};

struct Edge {
    int v, d, w, next;
    bool operator<(const Edge &e) const { return w < e.w; }
} eg[MAXN*MAXN*4];

int row, col;
int egc, head[MAXN*MAXN];
bool used[MAXN*MAXN];
bool M[MAXN][MAXN][4];

// add a edge <u, v> with weight w
void add(int u, int v, int d, int w)
{
    eg[egc] = (Edge){v,d,w,head[u]};
    head[u] = egc++;
}

// transfrom 1-d coodinate to 2-d coodinate
void u2p(int u, int &r, int &c)
{
    r = u / col, c = u % col;
}

// generation of the maze
void generate()
{
    int r, c, nr, nc;
    priority_queue<P> que;
    memset(head, -1, sizeof(head));

    // initialize all the edges
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            if(j < col-1) add(i*col+j, i*col+(j+1), 1, rand());
            if(i < row-1) add(i*col+j, (i+1)*col+j, 2, rand());
        }
    }

    // prim
    que.push(P(0, 0, 0, 0));
    while(!que.empty()) {
        P p = que.top(); que.pop();
        if(used[p.v]) continue;
        used[p.v] = true;
        if(p.u != p.v) {
            u2p(p.u, r, c);
            u2p(p.v, nr, nc);
            M[r][c][p.d] = 1;
            M[nr][nc][reverse_dir[p.d]] = 1;
        }
        for(int pe = head[p.v]; pe != -1; pe = eg[pe].next)
            que.push(P(p.v, eg[pe].v, eg[pe].d, eg[pe].w));
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

    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            for(int k = 0; k < 4; ++k)
                printf("%d\n", M[i][j][k]);
    return 0;
}
