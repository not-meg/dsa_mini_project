#define MAX_ROWS 200
#define MAX_COLS 6
#define MAX_LEN 30

struct FlightInfo {
    char source[50];
    char destination[50];
    char flightType[20];  
    float price;
    int duration;  
    int distance;
};

struct allpaths
{
    int path[MAX_ROWS];
    int duration;
    float cost;
};

void display_adj(int adj[MAX_ROWS][MAX_ROWS][2], int rows);
void display_places(char places[MAX_ROWS][MAX_LEN], int rows);
int get_flight_data(struct FlightInfo *data, int maxFlightCount);
int find_all_unique_places(struct FlightInfo *data, char places[MAX_ROWS][MAX_LEN], int no_of_rows);
void create_adjacency_matrix(struct FlightInfo *data, int adj[MAX_ROWS][MAX_ROWS][2], int no_of_input_rows,
                             char places[MAX_ROWS][MAX_LEN], int unique_places_rows);
int find_path(char start[MAX_LEN], char end[MAX_LEN], int unique_places_rows,
              struct allpaths **all_paths_src_dst, int adj[MAX_ROWS][MAX_ROWS][2],
              char places[MAX_ROWS][MAX_LEN]);
