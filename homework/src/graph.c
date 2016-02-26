/**********************
 * file name:   graph.c
 *
 *********************/

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <config.h>
#include <graph.h>
#include <parser.h>
#include <stack.h>

struct graph_s {
    int nVertex;
    int nEdge;
    int *data;
    int *buff1;  // store the result of dijkstra algorithm
    int *buff2;  // represent the open-close table used by algorithm
};

/**
 * create graph_t varible from the data file specified by path
 * return NULL if failed
 */
PUBLIC graph_t* new_graph(const char *path)
{
    input_data input;
    if (parse_file(path, &input) < 0) {
        LogE("Failed parse input file");
        return NULL;
    }

    graph_t *graph = (graph_t *)calloc(1, sizeof(graph_t));
    if (NULL == graph) {
        LogE("Failed callc graph");
        return NULL;
    }

    if (init_graph(graph, &input) < 0) {
        LogE("Failed init graph");
        free(graph);
        return NULL;
    }

#ifdef DEBUG
    print_graph(graph);
#endif

    if (NULL != input.edges) {
        free (input.edges);
        input.edges = NULL;
    }

    return graph;
}

/**
 * free the resource
 */
PUBLIC void free_graph(graph_t *graph)
{
    if (NULL != graph) {
        if (NULL != graph->data) {
            free(graph->data);
            graph->data = NULL;
        }

        if (NULL != graph->buff1) {
            free(graph->buff1);
            graph->buff1 = NULL;
        }

        if (NULL != graph->buff2) {
            free(graph->buff2);
            graph->buff2 = NULL;
        }

        free(graph);
    }
}

/**
 * calculate the distance of the route
 * params:
 *         route:   store the vertexes
 *         n:       number of vertex 
 */
PUBLIC int calc_route_distance(const graph_t *graph, const int *route, int n)
{
    VALIDATE_NOT_NULL2(graph, route);
    if (n <= 1) {
        LogE("route must have 2 vertexes");
        return -1;
    }

    int distance = 0;
    int i;
    for (i = 0; i + 1 < n; ++i) {
        distance += calc_distance(graph, route[i], route[i+1]); 
    }

    return distance;
}

PRIVATE Bool is_in_list(int *list, int n, int elem) {
    int i;
    for (i = 0; i < n; ++i) {
        if (list[i] == elem) {
            return True;
        }
    }

    return False;
}

/**
 * find the trips between 2 vertex
 * return:
 *        -1: failed
 *        otherwise:the number of trips
 */
PUBLIC int find_trips(
        graph_t *graph,
        int vertex1, 
        int vertex2, 
        trip_t **trips)
{
    VALIDATE_NOT_NULL2(graph, trips);
    if (vertex1 < 0 || vertex1 >= graph->nVertex || 
            vertex2 < 0 || vertex2 >= graph->nVertex) {
        LogE("Invalid vertex");
        return -1;
    }

    stack_t *stack = new_stack(graph->nVertex);
    if (NULL == stack) {
        LogE("Failed new stack");
        return -1;
    }

    free_stack(stack);
    stack =  NULL;

    return -1;
}

/**
 * init graph by input_data
 * return:
 *      0  success
 *      -1 failed
 */
PRIVATE int init_graph(graph_t *graph, const input_data *input) {
    VALIDATE_NOT_NULL2(graph, input);

    graph->nVertex = input->nVertex;
    graph->nEdge = input->nRow;
    int size = input->nVertex;
    graph->data = (int *)calloc(size * size, sizeof(int));
    if (NULL == graph->data) {
        LogE("Failed callc for data of graph");
        free (graph);
        return -1;
    }

    graph->buff1 = (int *)calloc(size, sizeof(int));
    if (NULL == graph->buff1) {
        LogE("Failed callc for buffer of graph");
        free(graph->data);
        graph->data = NULL;
        free(graph);
        return -1;
    }

    graph->buff2 = (int *)calloc(size, sizeof(int));
    if (NULL == graph->buff2) {
        LogE("Failed callc for buffer of graph");
        free(graph->data);
        graph->data = NULL;
        free(graph->buff1);
        graph->buff1 = NULL;
        free(graph);
        return -1;
    }

    int i, j;
    for (i = 0; i <  size; ++i) {
        for (j = 0; j < size; ++j) {
            if (i == j) {
                graph->data[i * size +j] = 0;
            }
            else {
                graph->data[i * size + j] = INFINITE;
            }
        }
    }

    for (i = 0; i < input->nRow; ++i) {
        int source = input->edges[i].source;
        int dest = input->edges[i].dest;
        int weight = input->edges[i].weight;
        graph->data[source * size + dest] = weight;
    }

    return 0;
}

/**
 * print the graph
 */
PRIVATE void print_graph(const graph_t *graph) {
    if (NULL == graph) {
        LogE("NULL pointer");
        return;
    }

    int i, j;
    printf("\n");

    for (i = 0; i < graph->nVertex; ++i) {
        for (j = 0; j < graph->nVertex; ++j) {
            printf("%-10d", graph->data[i * graph->nVertex + j] );
        }

        printf("\n");
    }

    printf("\n");
}

/**
 * calcuae distance between 2-vertexes
 * return:
 *      -1  noreachable or error occurs
 *      >=0 success
 */
PUBLIC int calc_distance(const graph_t *graph, int v1, int v2)
{
    VALIDATE_NOT_NULL(graph);
    if (v1 < 0 || v1 >= graph->nVertex ||
            v2 < 0 || v2 >= graph->nVertex) {
        LogE("Invalid vetex index");
        return -1;
    }

    return graph->data[v1 * graph->nVertex + v2];
}

/**
 * dijkstra algorithm
 * return:
 *      0  success
 *      -1 failed
 */
PUBLIC int dijkstra(graph_t *graph, int source)
{
    VALIDATE_NOT_NULL(graph);
    
    if (source < 0 || source >= graph->nVertex) {
        LogE("source is invalid");
        return -1;
    }

    memset(graph->buff1, 0, graph->nVertex * sizeof(int));
    memset(graph->buff2, 0, graph->nVertex * sizeof(int));

    int i, j;

    // graph->buff1 store the distance
    //
    // graph->buff2 represent the open-close table
    // 1 means closed, 0 meand open

    for (i = 0; i < graph->nVertex; ++i) {
        graph->buff1[i] = graph->data[source * graph->nVertex + i];
    }

    graph->buff2[source] = 1;

    int min, idx;
    for (i = 0; i < graph->nVertex; ++i) {
        min = INFINITE;
        for (j = 0; j < graph->nVertex; ++j) {
            if (!graph->buff2[j] && graph->buff1[j] < min) {
                min = graph->buff1[j];
                idx = j;
            }
        }    

        graph->buff2[idx] = 1;

        for (j = 0; j < graph->nVertex; ++j) {
            if (!graph->buff2[j] && 
                graph->buff1[idx] + graph->data[idx * graph->nVertex + j] < graph->buff1[j]) {
                graph->buff1[j] = graph->buff1[idx] + graph->data[idx * graph->nVertex + j];
            }
        }
    }

    return 0;
}

/**
 * get the vertex number
 * return:
 *      success:the number of vertex
 *      failed: -1
 */
PUBLIC int get_vertex_num(const graph_t *graph)
{
    VALIDATE_NOT_NULL(graph);
    return graph->nVertex;
}

/**
 * get the result of dijkstra algorithm
 * return:
 *     a memory for graph->nVertex * sizeof(int) 
 *
 * notice:
 *  call dijkstra() before call me, otherwise the return value is 
 *  uncertian
 */
PUBLIC int* read_graph_buff(const graph_t *graph)
{
    if (NULL == graph) {
        return NULL;
    }

    return graph->buff1;
}

/**
 * free trip_t
 */
PUBLIC void free_trip(trip_t *trip)
{
    if (NULL != trip) {
        if (NULL != trip->list) {
            free (trip->list);
            trip->list = NULL;
        }

        free (trip);
    }
}

/**
 * get the next reachables
 * return:
        -1  failed
        otherwise, the number of reachables
 */
PUBLIC int get_next_reachables(const graph_t *graph, int idx, int **result) {
    VALIDATE_NOT_NULL2(graph, result);
    if (idx < 0 || idx >= graph->nVertex) {
        LogE("idx is invalid");
        return -1;
    }

    *result = (int *)calloc(graph->nVertex, sizeof(int));
    if (NULL == *result) {
        LogE("Failed calloc for result");
        return -1;
    }

    int counter = 0;
    int i;
    for (i = 0; i < graph->nVertex; ++i) {
        if (i == idx) {
            continue;
        }
        
        if (graph->data[idx * graph->nVertex + i] < INFINITE) {
            *result[counter++] = i;
        }    
    } 

    return counter;
}

/**
 * get the prev reachables
 * return:
        -1  failed
        otherwise, the number of reachables
 */
PUBLIC int get_prev_reachables(const graph_t *graph, int idx, int **result) {
    VALIDATE_NOT_NULL2(graph, result);
    if (idx < 0 || idx >= graph->nVertex) {
        LogE("idx is invalid");
        return -1;
    }

    *result = (int *)calloc(graph->nVertex, sizeof(int));
    if (NULL == *result) {
        LogE("Failed calloc for result");
        return -1;
    }

    int counter = 0;
    int i;
    for (i = 0; i < graph->nVertex; ++i) {
        if (i == idx) {
            continue;
        }
        
        if (graph->data[i * graph->nVertex + idx] < INFINITE) {
            *result[counter++] = i;
        }    
    } 

    return counter;
}
