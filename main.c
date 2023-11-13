#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project_header.h"

#define MAX_INPUT_LEN 100

int main() {
    int no_of_input_rows;
    struct FlightInfo data[MAX_ROWS];
    int unique_places_rows = 0;
    char places[MAX_ROWS][MAX_LEN];
    struct adjacency_matrix_data adj[MAX_ROWS][MAX_ROWS];
    struct allpaths *all_paths_src_dst = NULL;

    char start[MAX_LEN], end[MAX_LEN];
    int allpaths_row;

    printf("Welcome to the Flight and Hotel Booking System.\n");

    memset(data, 0, sizeof(data));
    memset(adj, 0, sizeof(adj));

    no_of_input_rows = get_flight_data(data, MAX_ROWS);

    if (no_of_input_rows == -1) {
        printf("Error reading flight data.\n");
        return -1;
    }

    unique_places_rows = find_all_unique_places(data, places, no_of_input_rows);

    display_places(places, unique_places_rows);

    create_adjacency_matrix(data, adj, no_of_input_rows, places, unique_places_rows);

    display_adj(adj, unique_places_rows);

    printf("Enter the source: ");
    fgets(start, sizeof(start), stdin);
    start[strcspn(start, "\n")] = '\0';  // Remove the newline character

    printf("Enter the destination: ");
    fgets(end, sizeof(end), stdin);
    end[strcspn(end, "\n")] = '\0';  // Remove the newline character

    allpaths_row = find_path(start, end, unique_places_rows, &all_paths_src_dst, adj, places);
    if (allpaths_row == -1) {
        printf("Error finding paths.\n");
        return -1;
    }

    find_total_cost_duration(all_paths_src_dst, allpaths_row, adj);

    int sort_type;
    printf("Enter the sort type (1 for duration, 2 for cost): ");
    if (scanf("%d", &sort_type) != 1) {
        printf("Invalid input for sort type.\n");
        return -1;
    }

    switch (sort_type) {
        case 1:
            heapSortByDuration(all_paths_src_dst, allpaths_row, places);
            break;
        case 2:
            heapSortByCost(all_paths_src_dst, allpaths_row, places);
            break;
        default:
            printf("Invalid sort type.\n");
            return -1;
    }

    struct HotelInfo hotels[MAX_HOTELS];
    int hotelCount = readHotelsData(hotels, "hotels.csv");

    printf("Hotels:\n");
    for (int i = 0; i < hotelCount; i++) {
        printf("Name: %s, Place: %s, Price: %.2f\n", hotels[i].name, hotels[i].place, hotels[i].price);
    }

    struct HotelInfo *cheapestHotel = findCheapestHotel(end);

    if (cheapestHotel != NULL) {
        printf("Cheapest hotel in %s:\n", end);
        printf("Name: %s, Price: %.2f\n", cheapestHotel->name, cheapestHotel->price);
    } else {
        printf("No hotels found in %s.\n", end);
    }

    // Clean up dynamically allocated memory if any
    // (e.g., all_paths_src_dst, and any other dynamically allocated data)


    return 0;
}

