#include <stdio.h>
#include <limits.h>
#include "dg_stack.h"

#define NO_PATH -1
#define INF -2147483648
#define OVERINF -2147483647
#define MAX_VRTX 5000
#define MAX_EDGS n*(n+1)/2

void Dijkstra(int start, LIST **graph, int *lens, int *from) {
    //creating stack
    LIST *stack = Create(0, 0);
    Insert(stack, Create(start, 0));

    while (stack -> next != NULL) {
        //taking element from stack
        LIST *curV = stack -> next;
        //index of current vertex
        int vrtx = curV -> key;
        //length of path from start to current vertex
        int len = *(lens+vrtx);
        stack -> next = curV -> next;
        free(curV);

        //taking the first element from the desired row of the adjacency list
        LIST *curN = (*(graph+vrtx)) -> next;
        while(curN != NULL) {
            //index of current neighbor
            int neigh = curN -> key;
            //length of path from start to neigh through current vertex
            int lenT = len + (curN -> value);

            //checking for overflow
            if (lenT < 0)
                lenT = INF;
            if (len == OVERINF)
                lenT = OVERINF;

            //also checking for overflow
            if (*(lens+neigh) < NO_PATH & lenT < NO_PATH) {
                *(lens+neigh) = OVERINF;
                *(from+neigh) = vrtx;
                Insert(stack, Create(curN -> key, 0));
            }

            //if this neighbor has not been visited before
            if (*(lens+neigh) == NO_PATH) {
                *(lens+neigh) = lenT;
                *(from+neigh) = vrtx;
                Insert(stack, Create(curN -> key, 0));
            }

            //if the path through the current vertex is shorter
            else if ((lenT >= 0) & (lenT < *(lens+neigh))) {
                *(lens+neigh) = lenT;
                *(from+neigh) = vrtx;
                Insert(stack, Create(curN -> key, 0));;
            }

            curN = curN -> next;
        }
    }

    free(stack);
}

int main()
{
    int n, start, end, m;
    int vrt1, vrt2, l;
    LIST **graph;
    int *lens;
    int *from;

    //getting input
    scanf("%d", &n);
    if (n < 0 || n > MAX_VRTX) {
        printf("bad number of vertices");
        return 0;
    }

    scanf("%d %d", &start, &end);
    if (start < 1 || start > n || end < 1 || end > n) {
        printf("bad vertex");
        return 0;
    }

    scanf("%d", &m);
    if (m < 0 || m > MAX_EDGS) {
        printf("bad number of edges");
        return 0;
    }

    //adjacency list
    graph = (LIST**)malloc((n+1)*sizeof(LIST*));
    //array of shortest lengths
    lens = (int*)malloc((n+1)*sizeof(int));
    //the nearest neighbor of the current vertex to the beginning
    from = (int*)malloc((n+1)*sizeof(int));

    for (int i = 1; i <= n; i++) {
        *(graph+i) = Create(0, 0);
        *(lens+i) = NO_PATH;
    }
    *(lens+start) = 0;
    *(from+start) = start;

    //getting edges of graph
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d %d", &vrt1, &vrt2, &l) != 3) {
            printf("bad number of lines");
            return 0;
        }

        if (vrt1 < 1 || vrt1 > n || vrt2 < 1 || vrt2 > n) {
            printf("bad vertex");
            return 0;
        }

        if (l < 0) {
            printf("bad length");
            return 0;
        }

        Add(*(graph+vrt1), Create(vrt2, l));
        Add(*(graph+vrt2), Create(vrt1, l));
    }


    Dijkstra(start, graph, lens, from);

    //printing shortest paths
    for (int i = 1; i <= n; i++) {
        int len = *(lens+i);
        if (len == NO_PATH)
            printf("oo ");
        else if (len < 0)
            printf("INT_MAX+ ");
        else
            printf("%d ", len);
    }
    printf("\n");

    //printing shortest path to the end vertex
    if (*(lens+end) == NO_PATH) {
        printf("no path");
        return 0;
    }

    if (*(lens+end) == OVERINF) {
        printf("overflow");
        return 0;
    }

    while (*(from+end) != end) {
        printf("%d ", end);
        end = *(from+end);
    }
    printf("%d", end);

    //clearing memory
    free(lens);
    free(from);
    for (int i = 1; i <= n; i++)
        Clear(*(graph+i));
    free(graph);

    return 0;
}
