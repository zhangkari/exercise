/*******************************************
 * file name:   parser.c
 * description: parse the input file
 *   the input file must be like as follows
 *   AB1
 *   BC1
 *   BC3
 *   each edge store in a line
 *
 *******************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <config.h>
#include <parser.h>

PUBLIC int parse_file(const char *path, input_data *result)
{
    VALIDATE_NOT_NULL2(path, result);

    FILE *fp = fopen(path, "r");
    if (NULL == fp) {
        LogE("Failed fopen %s,%s", path, strerror(errno));
        return -1;
    }

    int counter = count_input_edges(fp);
    if (counter <= 0) {
        LogE("Failed count input edges");
        fclose(fp);
        return -1;
    }

#ifdef DEBUG
    printf("row=%d\n", counter);
#endif

    result->nRow = counter;
    result->edges = (edge_t *) calloc(counter, sizeof(edge_t));
    if (NULL == result->edges) {
        LogE("Failed calloc mem for edges");
        fclose(fp);
        return -1;
    }

    char line[8];
    counter = 0;
    fseek(fp, 0L, SEEK_SET);
    while (!feof(fp)) {
        memset(line, 0, 8);
        if(NULL == fgets(line, 8, fp) ) {
            break;
        }

        if (!validate_comment(line, fp) ) {
            continue;
        }

       char ch1 = line[0];
       char ch2 = line[1];
       int weight = atoi(line+2);

#ifdef DEBUG
        Log("%s -> %c %c %d\n", line, ch1, ch2, weight);
#endif

        result->edges[counter].source = ch1 - 'A';
        result->edges[counter].dest = ch2 - 'A';
        result->edges[counter].weight = weight;
        ++counter;
    }

    fclose(fp);
    fp = NULL;

    if (calc_vertex_num(result) < 0) {
        LogE("Failed calculate vertex number");
        return -1;
    }

    return 0;
}

/**
 * validate the format of each row
 * return:
 *      0  success
 *      -1 failed
 */
PRIVATE int validate_format(char *buf) {
    VALIDATE_NOT_NULL(buf);
    if (strlen(buf) < 3) {
        LogE("format like V1V2Value");
        return -1;
    }

    char ch1, ch2;
    int value;
    ch1 = buf[0];
    ch2 = buf[1];
    value = atoi(buf+2);

    if (ch1 < 'A' || ch1 > 'Z') {
        LogE("Vertex 1 must be A ~ Z");
        return -1;
    }

    if (ch2 < 'A' || ch2 > 'Z') {
        LogE("Vertex 2 must be A ~ Z");
        return -1;
    }

    if (value <= 0) {
        LogE("Weighting must be positive number");
        return -1;
    }

    if (value >= INFINITE) {
        LogE("Weighting must less than %lu", INFINITE);
        return -1;
    }

    return 0;
}

/**
 * validate the comment (include  the commit & \n)
 */
PRIVATE int validate_comment(char *line, FILE *fp) {
    // ignore '\n'
    if (!strcmp(line, "\n") ) {
        return 0;
    }

    // ingore #....
    if ('#' == line[0]) {
        char ch;
        do {
            ch = fgetc(fp);
        } while('\n' != ch);

        return 0;
    }

    return -1;
}

/**
 * calculate the number of vertex
 * return:
 *      0 if succcess
 *      -1, failed
 */
PRIVATE int calc_vertex_num(input_data *input) {
    VALIDATE_NOT_NULL2(input, input->edges);
    if (input->nRow <= 0) {
        LogE("row must be positive number");
        return -1;
    }

    char *slots = (char *)calloc(input->nRow + 1, 1);
    if (NULL == slots) {
        LogE("Failed calloc for slots to count vertex");
        return -1;
    }

    int i;
    for (i = 0; i < input->nRow; ++i) {
        *(slots + input->edges[i].source) = 1;
        *(slots + input->edges[i].dest) = 1;
    }

    int counter = 0;
    for (i = 0; i < input->nRow + 1; ++i) {
        if (slots[i]) {
            counter++;
        }
    }

#ifdef DEBUG
   Log("vertex count:%d\n", counter);
#endif

   input->nVertex = counter;

   return 0;
}

/**
 * count the number of edges that user input
 * return:
 *      positive number if success
 *      otherwise failed
 */
PRIVATE int count_input_edges(FILE *fp) {
    VALIDATE_NOT_NULL(fp);
    int counter = 0;
    char line[8];
    while (!feof(fp)) {
        memset(line, 0, 8);
        if(NULL == fgets(line, 8, fp) ) {
            break;
        }

        if (!validate_comment(line, fp) ) {
            continue;
        }

        if (validate_format(line) < 0) {
            LogE("Invalid foramt");
            return -1;
        }

        counter++;
    }

    return counter;
}

