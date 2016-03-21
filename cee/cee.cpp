/************************************
 * file name:   cee.h
 * description: computer eyes engine
 * author:      kari.zhang
 * date:        2016-01-28
 ***********************************/

#include <stdio.h>
#include <stdlib.h>
#include "cee.h"
#include "Feature.h"

static int countFeatures(int width, int height);
static int countEdgeFeatures(int width, int height);
static int countLinearFeatures(int width, int height);
static int countDirectionFeatures(int width, int height);

int main(int argc, char *argv[])
{
#define SAMPLE_SIZE 24
#define SIZE_MIN 2

    int width = SAMPLE_SIZE;
    int height = SAMPLE_SIZE;
    if (argc == 2) {
        int size = atoi(argv[1]);
        if (size < SIZE_MIN) {
            printf("sample size (%d x %d) is too small.\n", size, size);
            return -1;
        }
        
        width = size;
        height = size;
    }

    if (argc >= 3) {
        int size = atoi(argv[1]);
        if (size < SIZE_MIN) {
            printf("sample width (%d) is too small.\n", size);
            return -1;
        }

        size = atoi(argv[2]);
        if (size < SIZE_MIN) {
            printf("sample height (%d) is too small.\n", size);
            return -1;
        }
    }

    countFeatures(width, height);
}

static int countFeatures(int width, int height) {
    int edges = countEdgeFeatures(width, height);
    int linears = countLinearFeatures(width, height);
    int directions = countDirectionFeatures(width, height);
    int num = 2 * edges + 2 * linears + directions;
    printf("total features:%d\n", num);
    return num;
}

static int countEdgeFeatures(int width, int height) {
	int num = 0;

	for (int i = 2; i <= width; i+=2) {
		int k = width + 1 - i;
		for (int j = 1; j <= k; ++j) {
			for (int m = 1; m <= height; m += 1) {
				int t = height + 1 - m;
				for (int n = 1; n <= t; ++n) {
					num++;
				}
			}
		}
	}

    printf("edge features:%d\n", num);
    return num;
}

static int countLinearFeatures(int width, int height) {
	int num = 0;
	for (int i = 3; i <= width; i+=3) {
		int k = width + 1 - i;
		for (int j = 1; j <= k; ++j) {
			for (int m = 1; m <= height; m += 1) {
				int t = height + 1 - m;
				for (int n = 1; n <= t; ++n) {
					num++;
				}
			}
		}
	}

    printf("linear features:%d\n", num);
    return num;
}

static int countDirectionFeatures(int width, int height) {
	int num = 0;
	for (int i = 2; i <= width; i+=2) {
		int k = width + 1 - i;
		for (int j = 1; j <= k; ++j) {
			for (int m = 2; m <= height; m += 2) {
				int t = height + 1 - m;
				for (int n = 1; n <= t; ++n) {
					num++;
				}
			}
		}
	}

    printf("direction features:%d\n", num);
    return num;
}
