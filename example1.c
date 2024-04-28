#include <stdlib.h>
#include <stdio.h>

typedef struct Node 
{
    int data;
    struct Node *next;
} NODE;

typedef struct g 
{
    int v;
    NODE **alst;
    int *vis;
} GPH;

typedef struct s 
{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) 
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) 
{
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v) 
{
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v);
    g->vis = malloc(sizeof(int) * v);
    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s(int scap) 
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s) 
{
    s->t++;
    s->arr[s->t] = pshd;
}

int pop(STK *s) 
{
    if (s->t == -1) return -1; // Stack is empty
    return s->arr[s->t--];
}

void DFS(GPH *g, STK *s, int v_nr) 
{
    g->vis[v_nr] = 1;
    push(v_nr, s);
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr) 
{
    int src, dest;
    printf("Adauga %d muchii\n", edg_nr);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g) 
{
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}

int canbe(GPH *g, int nrv, STK *s1, STK *s2) 
{
    for (int i = 0; i < nrv; i++) {
        wipe(g);
        wipe(s1);
        wipe(s2);
        DFS(g, s1, i);
        wipe(g);
        DFS(g, s2, i);
        while (s1->t >= 0 && s2->t >= 0) {
            if (pop(s1) != pop(s2))
                return 0;
        }
    }
    return 1;
}

int main() 
{
    int nrv, edg_nr;
    printf("Cate noduri are reteaua ");
    scanf("%d", &nrv);
    printf("Cate muchii are reteaua ");
    scanf("%d", &edg_nr);
    GPH *g = create_g(nrv);

    insert_edges(g, edg_nr);

    STK *s1 = create_s(nrv);
    STK *s2 = create_s(nrv);

    if (canbe(g, nrv, s1, s2))
        printf("da, exista drum direct\n");
    else
        printf("nu, nu exista drum direct\n");

    return 0;
}
