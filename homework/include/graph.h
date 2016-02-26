/**********************
 * file name:   graph.h
 *
 *********************/

#ifndef __GRAPH__H__
#define __GRAPH__H__

#include <comm.h>
#include <parser.h>

typedef struct {
    int nVertex;
    int *list;
} trip_t;

typedef struct graph_s graph_t;

typedef int (*cmpfunc)(int, int);

/**
 * create graph_t varible from the data file specified by path
 * return:
 *       NULL if failed
 * 
 */
PUBLIC graph_t* new_graph(const char *path);

/**
 * free the resource
 */
PUBLIC void free_graph(graph_t *graph);

/**
 * calculate the distance of the route
 * params:
 *         route:   store the vertexes
 *         n:       number of vertex 
 */
PUBLIC int calc_route_distance(const graph_t *graph, const int *route, int n);

/**
 * dijkstra algorithm
 * return:
 *      0  success
 *      -1 failed
 */
PUBLIC int dijkstra(graph_t *graph, int source);

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
        trip_t **trips);

/**
 * free trip_t
 */
PUBLIC void free_trip(trip_t *trip);

/**
 * init graph by input_data
 * return:
 *      0  success
 *      -1 failed
 */
PRIVATE int init_graph(graph_t *graph, const input_data *input);

/**
 * print the graph
 */
PRIVATE void print_graph(const graph_t *graph);

/**
 * calcuae distance between 2-vertexes
 * return:
 *      -1  noreachable or error occurs
 *      >=0 success
 */
PUBLIC int calc_distance(const graph_t *graph, int v1, int v2);

/**
 * get the vertex number
 * return:
 *      success:the number of vertex
 *      failed: -1
 */
PUBLIC int get_vertex_num(const graph_t *graph);

/**
 * get the result of dijkstra algorithm
 * return:
 *     a memory for graph->nVertex * sizeof(int) 
 *
 * notice:
 *  call dijkstra() before call me, otherwise the return value is 
 *  uncertian
 */
PUBLIC int* read_graph_buff(const graph_t *graph);

/**
 * get the next reachables
 * return:
        -1  failed
        otherwise, the number of reachables
 */
PUBLIC int get_next_reachables(const graph_t *graph, int idx, int **result);

/**
 * get the prev reachables
 * return:
        -1  failed
        otherwise, the number of reachables
 */
PUBLIC int get_prev_reachables(const graph_t *graph, int idx, int **result);

#endif
