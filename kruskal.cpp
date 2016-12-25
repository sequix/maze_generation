// Generate maze with Kruskal
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50;   // maximum size of the maze MAXN * MAXN
const int reverse_dir[] = {2, 3, 0, 1};

struct Edge {
    int u, v, w, d;
    Edge(int u=0, int v=0, int w=0, int d=0): u(u), v(v), w(w), d(d) {}
    bool operator<(const Edge &e) const { return w < e.w; }
};

int row, col;
Edge edges[MAXN*MAXN*2];
int par[MAXN*MAXN];
bool haswall[MAXN][MAXN][4];

int getpar(int x)
{
    if(x != par[x])
        par[x] = getpar(par[x]);
    return par[x];
}

// transfrom 1-d coodinate to 2-d coodinate
void u2p(int u, int &r, int &c)
{
    r = u / col, c = u % col;
}

// generation of the maze
void generate()
{
    int edge_cnt = 0;

    // initialize all the edges, the disjoint-set and haswall[]
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            if(j < col-1)
                edges[edge_cnt++] = Edge(i*col+j, i*col+(j+1), rand(), 1);
            if(i < row-1)
                edges[edge_cnt++] = Edge(i*col+j, (i+1)*col+j, rand(), 2);
        }
    }
    sort(edges, edges+edge_cnt);  // shuffle
    for(int i = 0; i < row*col; ++i)
        par[i] = i;
    memset(haswall, 1, sizeof(haswall));

    // generation
    for(int i = 0; i < edge_cnt; ++i) {
        Edge &e = edges[i];
        if(getpar(e.u) != getpar(e.v)) {
            par[getpar(e.u)] = par[getpar(e.v)];
            int r, c, nr, nc;
            u2p(e.u, r, c);
            u2p(e.v, nr, nc);
            haswall[r][c][e.d] = 0;
            haswall[nr][nc][reverse_dir[e.d]] = 0;
        }
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
