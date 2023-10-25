#include <stdio.h>
#include <stdlib.h>
#include "project_header.h"
#include <string.h>

int main()
{
    int no_of_input_rows;
    struct FlightInfo data[MAX_ROWS];
    int unique_places_rows = 0;
    char places[MAX_ROWS][MAX_LEN];
    struct adjacency_matrix_data adj[MAX_ROWS][MAX_ROWS];
    struct allpaths *all_paths_src_dst = NULL;

    char start[MAX_LEN], end[MAX_LEN];
    int allpaths_row;

    printf("came to main.\n");

    memset(data, 0, sizeof(data));
    memset(adj, 0, sizeof(adj));

    no_of_input_rows = get_flight_data(data, MAX_ROWS);

    if(no_of_input_rows == -1) {
        return no_of_input_rows;
    }

    unique_places_rows = find_all_unique_places(data, places, no_of_input_rows);

    display_places(places, unique_places_rows);

    create_adjacency_matrix(data, adj, no_of_input_rows, places, unique_places_rows);

    display_adj(adj, unique_places_rows);

    printf("Enter the source: ");
    gets(start);

    //strcpy(start, "Natal (RN)");

    printf("Enter the destination: ");
    gets(end);

    //strcpy(end, "Salvador (BH)");

    printf("got start and end.\n");

    allpaths_row = find_path(start, end, unique_places_rows, &all_paths_src_dst, adj, places);
    if(allpaths_row == -1) {
        printf("Bad input.\n");
        return -1;
    }

    find_total_cost_duration(all_paths_src_dst, allpaths_row, adj);

    /*heapSortByDuration(all_paths_src_dst, allpaths_row);

    printf("\nSorted flights by duration:\n");
    for (int i = 0; i < allpaths_row; i++) {
        printf("Duration: %d\n", all_paths_src_dst[i].duration);
    }

    printf("done with sorting.\n");*/
    int sort_type;
  printf("Enter the sort type (1 for duration, 2 for cost): ");
  scanf("%d", &sort_type);

  switch (sort_type) {
    case 1:
      heapSortByDuration(all_paths_src_dst, allpaths_row,places);
      break;
    case 2:
      heapSortByCost(all_paths_src_dst, allpaths_row,places);
      break;
    default:
      printf("Invalid sort type.\n");
      return -1;
  }
 /* if (allpaths_row > 0) {
    struct allpaths first_element = all_paths_src_dst[0];
    printf("First element after sorting:\n");
    // Access properties of first_element like first_element.duration, first_element.cost, etc.
} else {
    printf("No paths found.\n");
}*/
}

