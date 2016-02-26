/***********************
 * file name: railway.c
 *
 * ********************/
#include <assert.h>
#include <stdlib.h>

#include <comm.h>
#include <config.h>
#include <graph.h>
#include <stack.h>

PRIVATE void usage(int argc, char **argv);
PRIVATE void print_route_distance(const graph_t *graph, int *route, int n);
PRIVATE int question6(const graph_t *graph);
PRIVATE int question7(const graph_t *graph);
PRIVATE int question9(graph_t *graph);
PRIVATE int question10(graph_t *graph);

int main(int argc, char **argv) 
{
    if (2 != argc) {
        usage(argc, argv);
        return -1;
    } 

    graph_t *graph = new_graph(argv[1]);
    if (NULL == graph) {
        return -2;
    }

    /**
     * Question 1
     */
    int route1[] = {0, 1, 2};
    int n = sizeof(route1) / sizeof(route1[0]);
    print_route_distance(graph, route1, n);

    /**
     * Question 2
     */
    int route2[] = {0, 3};
    n = sizeof(route2) / sizeof(route2[0]);
    print_route_distance(graph, route2, n);

    /**
     * Question 3
     */
    int route3[] = {0, 3, 2};
    n = sizeof(route3) / sizeof(route3[0]);
    print_route_distance(graph, route3, n);

    /**
     * Question 4
     */
    int route4[] = {0, 4, 1, 2, 3};
    n = sizeof(route4) / sizeof(route4[0]);
    print_route_distance(graph, route4, n);

    /**
     * Question 5
     */
    int route5[] = {0, 4, 3};
    n = sizeof(route5) / sizeof(route5[0]);
    print_route_distance(graph, route5, n);

    /**
     * Question 6
     */
    int answer6 = question6(graph);
    if (answer6 <= 0) {
        printf("NO SUCH ROUTE\n");
    } else {
        printf("%d\n", answer6);
    }

    /**
     * Question 7
     */
    int answer7 = question7(graph);
    if (answer7 <= 0) {
        printf("NO SUCH ROUTE\n");
    } else {
        printf("%d\n", answer7);
    }

    /**
     * Question 8
     */
     int nVertex = get_vertex_num(graph);
#ifdef DEBUG
    Log("nVertex:%d\n", nVertex);
#endif

    if (dijkstra(graph, 0) < 0) {
        LogE("Failed call dijsktra");
    }

    int *distances = read_graph_buff(graph);
    if (NULL == distances) {
        LogE("Wo~Wo~ It seems not good, crash me!");
    }
    printf("%d\n", distances[2]);

    /**
     * Question 9
     */
    int dist = question9(graph); 
    if (dist >= INFINITE) {
        printf("NO SUCH ROUTE\n");
    } else {
        printf("%d\n", dist);
    }
    
    /**
     * Question 10
     */
#if 0
    int answer10 = question10(graph);
    if (anser10 <= 0) {
        printf("NO SUCH ROUTE\n");
    } else {
        printf("%d\n", answer10);
    }
#endif
    printf("question 10\n");
    
    free_graph(graph);
    graph = NULL;

}

PRIVATE void usage(int argc, char **argv) {
    Log("Usage: %s path\n", argv[0]);
}

PRIVATE int question6(const graph_t *graph) {
    VALIDATE_NOT_NULL(graph);

    int counter = 0;
    int i, j;
    
    int nVertex = get_vertex_num(graph);

    // 2 stops
    for (i = 0; i < nVertex; ++i) {
        if (2 == i) continue;
        if (calc_distance(graph, 2, i) < INFINITE &&
                calc_distance(graph, i, 2) < INFINITE) {
            ++counter;
        }
    } 

    int n1 = 0;
    int *next = (int *)calloc(nVertex, sizeof(int));
    assert(NULL != next);

    int n2 = 0;
    int *prev = (int *)calloc(nVertex, sizeof(int));
    assert(NULL != prev);

    int dist;
    // next reachables
    for (i = 0; i < nVertex; ++i) {
        if (2 == i) continue;
        if (calc_distance(graph, 2, i) < INFINITE) {
            next[n1++] = i;
        }
    }

    for (i = 0; i < nVertex; ++i) {
        if (2 == i) continue;
        if (calc_distance(graph, i, 2) < INFINITE) {
            prev[n2++] = i;
        }
    }

    for (i = 0; i < n1; ++i) {
        for (j = 0; j < n2; ++j) {
            if (next[i] == prev[j]) continue;
            if (calc_distance(graph, next[i], prev[j]) < INFINITE) {
                counter++;
            }
        }
    }

    free (next);
    next = NULL;

    free (prev);
    prev = NULL;

    return counter;
}

PRIVATE int question7(const graph_t *graph) {
    VALIDATE_NOT_NULL(graph);

    int nVertex = get_vertex_num(graph);

    int n1 = 0;
    int *next = (int *)calloc(nVertex, sizeof(int));
    assert(NULL != next);

    int n2 = 0;
    int *prev = (int *)calloc(nVertex, sizeof(int));
    assert(NULL != prev);

    int i,j;
    for (i = 0; i < nVertex; ++i) {
        if (0 == i) continue;
        if (calc_distance(graph, 0, i) < INFINITE) {
            next[n1++] = i;
        }
    }
    
    int m1 = 0;
    int *next2 = (int *)calloc(nVertex, sizeof(int));
    assert(NULL != next2);
    for (i = 0; i < nVertex; ++i) {
        for (j = 0; j < n1; ++j) {
            if (i == next[j]) continue;
            if (calc_distance(graph, next[j], i) < INFINITE) {
                next2[m1++] = i;
            }
        }
    }

    for (i = 0; i < nVertex; ++i) {
        if (2 == i) continue;
        if (calc_distance(graph, i, 2) < INFINITE) {
            prev[n2++] = i;
        }
    }

    int counter = 0;
    for (i = 0; i < m1; ++i) {
        for (j = 0; j < n2; ++j) {
            if (next2[i] == prev[j]) continue;
            if (calc_distance(graph, next2[i], prev[j]) < INFINITE) {
                ++counter;
            }
        }
    }

    free (next);
    next = NULL;

    free (next2);
    next2 = NULL;

    free (prev);
    prev = NULL;

    return counter;
}

PRIVATE int question9(graph_t *graph) {
    VALIDATE_NOT_NULL(graph);

    int nVertex = get_vertex_num(graph);
#ifdef DEBUG
    Log("nVertex:%d\n", nVertex);
#endif

    // the reachables of 'B'
    int *reachables = (int *)calloc(nVertex, sizeof(int));
    if (NULL == reachables) {
        return -1;
    }

    int counter = 0;
    int i;
    for (i = 0; i < nVertex; ++i) {
        if (1 == i) {
            continue; 
        }

        int dist = calc_distance(graph, 1, i);
        if (dist < INFINITE) {
            reachables[counter] = dist;
            if (dijkstra(graph, i) < 0) {
                LogE("Faild dijkstra");
                return -1;
            }

            int *distance = read_graph_buff(graph);
            reachables[counter] += distance[1];
            counter++;
        }
    }

    int min = INFINITE;
    for (i = 0; i < counter; ++i) {
        if (reachables[i] < min) {
            min = reachables[i];
        }
    }

    free(reachables);
    reachables = NULL;

    return min;
}

PRIVATE void print_route_distance(const graph_t *graph, int *route, int n) {
    int distance = calc_route_distance(graph, route, n);
    if (distance < INFINITE) {
        printf("%d\n", distance);
    } else {
        printf("NO SUCH ROUTE\n");
    }
}

PRIVATE int question10(graph_t *graph) {

    assert(NULL != graph);

    #define DEPTH 10
    #define MAX_DISTANCE 30

    int nVertex = get_vertex_num(graph);
    assert(nVertex >= 2);

    int n1 = 0;
    int *buff1 = (int *)calloc(nVertex, sizeof(int));
    assert(NULL != buff1);

    int n2 = 0;
    int *buff2 = (int *)calloc(nVertex, sizeof(int));
    assert(NULL != buff2);

    int counter = 0;
    int i, j;

    int dist1, dist2, dist3;
    for (i = 0; i < nVertex; ++i) {
        if (2 == i) continue;
        dist1 = calc_distance(graph, 2, i);
        dist2 = calc_distance(graph, i, 2);
        if (dist1 + dist2 < MAX_DISTANCE) {
            counter++;
        } 
    }

    for (i = 0; i < nVertex; ++i) {
        if (2 == i) continue;
        dist1 = calc_distance(graph, 2, i);
        if (dist1 < INFINITE) {
            buff1[n1++] = i;    
        }
    }


    free (buff1);
    buff1 = NULL;

    free (buff2);
    buff2 = NULL;

    return -1;
}
