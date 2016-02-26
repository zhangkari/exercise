/*******************************************
 * file name:   parser.h
 * description: parse the input file
 *   the input file must be like as follows
 *   AB1
 *   BC1
 *   BC3
 *   each edge store in a line
 *
 *******************************************/

#ifndef __PARSER__H__
#define __PARSER__H__

#include <comm.h>

typedef struct edge_s{
    int source;
    int dest;
    int weight;
} edge_t;

typedef struct input_data {
    int nRow;
    int nVertex;
    edge_t *edges;
} input_data;

/**
 * parse the input file & store the result
 * return:
 *      0  success
 *      -1 failed
 **/
PUBLIC int parse_file(const char *path, input_data *result);

/**
 * count the number of edges that user input
 * return:
 *      positive number if success
 *      otherwise failed
 */
PRIVATE int count_input_edges(FILE *fp);

/**
 * validate the format of each row
 * return:
 *      0  success
 *      -1 failed
 */
PRIVATE int validate_format(char *buffer);

/**
 * validate the comment (include  the commit & \n)
 */
PRIVATE int validate_comment(char *buffer, FILE *fp);

/**
 * calculate the number of vertex
 * return:
 *      0 if succcess
 *      -1, failed
 */
PRIVATE int calc_vertex_num(input_data *input);

#endif
