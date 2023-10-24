#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "project_header.h"

int search_place(char places[MAX_ROWS][MAX_LEN], char place[MAX_LEN], int rows)
{
    int i;

    for(i=0; i<rows; i++) {
        if(strcmp(place, places[i]) == 0) {
            return i;
        }
    }

    return -1;
}

int find_all_unique_places(struct FlightInfo *data, char places[MAX_ROWS][MAX_LEN], int no_of_rows)
{
    int i, j, rows = 0, exists = 0;

    for(i=1; i<no_of_rows; i++) {
        for(j=0; j<rows; j++) {
            if(strcmp(data[i].source, places[j]) == 0) {
                exists = 1;
                break;
            }
        }
        if(exists == 0) {
            strcpy(places[j], data[i].source);
            rows++;
        }

        exists = 0;
    }

    return rows;
}

void display_places(char places[MAX_ROWS][MAX_LEN], int rows)
{
    int i, j;

    for(i=0; i<rows; i++) {
        printf("[%d] %s\n", i, places[i]);
    }
}
void display_adj(int adj[MAX_ROWS][MAX_ROWS][2], int rows)
{
    int i, j;

    for(i=0; i<rows; i++) {
        for(j=0; j<rows; j++) {
            printf("%d\t", adj[i][j][0]);
        }
        printf("\n");
    }
}

void create_adjacency_matrix(struct FlightInfo *data, int adj[MAX_ROWS][MAX_ROWS][2], int no_of_input_rows,
                             char places[MAX_ROWS][MAX_LEN], int unique_places_rows)
{   
    int i, j, pos_src, pos_dst;
    char src[MAX_LEN], dst[MAX_LEN];

    for(i=1; i<no_of_input_rows; i++) {
        strcpy(src, data[i].source);
        strcpy(dst, data[i].destination);

        pos_src = search_place(places, src, unique_places_rows);

        pos_dst = search_place(places, dst, unique_places_rows);
        assert(pos_src != pos_dst);
        adj[pos_src][pos_dst][0] = data[i].price;
        adj[pos_src][pos_dst][1] = data[i].duration;
    }
}

int  find_all_paths(int adj[MAX_ROWS][MAX_ROWS][2],
                    int pos_start,
                    int pos_end,
                    int unique_places_rows,
                    int path[],
                    struct allpaths **all_paths_src_dst,
                    int path_index,
                    int *allpaths_row,
                    int visited[])
{
    int i;

    visited[pos_start] = 1;
    path[path_index] = pos_start;

    if(pos_start == pos_end) {
        struct allpaths *temp = realloc(*all_paths_src_dst, sizeof(struct allpaths) * ((*allpaths_row)+1));
        if (temp == NULL) {
            return -1;
        }
        *all_paths_src_dst = temp;
        memcpy((*all_paths_src_dst)[*allpaths_row].path, path, (path_index+1)*(sizeof(int)));
        //printf("pos_start = %d, pos_end = %d path_index = %d allpaths_row = %d\n", pos_start, pos_end, path_index, *allpaths_row);
        /*for(int i=0; i<path_index+1; i++) {
            printf("%d\t", path[i]);
        }
        printf("\n");*/

        (*allpaths_row)++;
        visited[pos_start] = 0;
        return 0;
    }

    for(i=0; i<unique_places_rows; i++) {
        if(adj[pos_start][i][0] != 0) {
            if (visited[i] != 1) {
                if (find_all_paths(adj, i, pos_end, unique_places_rows,
                                   path, all_paths_src_dst, path_index+1,
                                   allpaths_row, visited) == -1) {
                    return -1;
                }
            }
        }
    }

    visited[pos_start] = 0;
    return 0;
}

int find_path(char start[MAX_LEN], char end[MAX_LEN], int unique_places_rows,
             struct allpaths **all_paths_src_dst, int adj[MAX_ROWS][MAX_ROWS][2], char places[MAX_ROWS][MAX_LEN])
{
    int pos_start, pos_end, path_index = 0, allpaths_row = 0;
    int path[MAX_ROWS];
    int visited[unique_places_rows];

    memset(visited, 0, sizeof(visited));
    pos_start = search_place(places, start, unique_places_rows);
    pos_end = search_place(places, end, unique_places_rows);

    //printf("pos_start = %d, pos_end = %d\n", pos_start, pos_end);

    if(pos_start == -1 || pos_end == -1) {
        return -1;
    }

    if (find_all_paths(adj, pos_start, pos_end,
                       unique_places_rows, path,
                       all_paths_src_dst, path_index,
                       &allpaths_row, visited) == -1) {
        return -1;
    }

    //printf("end of find_path func.\n");

    return allpaths_row;
}
