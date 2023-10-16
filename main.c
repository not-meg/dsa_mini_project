#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flight_node
{
	char source[30];
	char destination[30];
	char ans;
	int distance;
	int duration;
	int cost;
};

int main()
{
	char source[50], destination[50];
	int no_of_stops, sort_by, i;
	char places ["Natal (RN)", "Recife (PE)", "Rio de Janeiro (RJ)", "Campo Grande (MS)", "Salvador (BH)", "Aracaju (SE)", "Sao Paulo (SP)", "Brasilia (DF)", "Florianopolis (SC)"];

	printf("Places:\n");

	for(i=0; i<9; i++) {
		printf("places[i]\n");
	}

	printf("Enter the source location: ");
	scanf("%s", source);

	printf("Enter destination: ");
	scanf("%s", destination);

	printf("Do you want to add any stops? (Y/N) ");
	scanf("%c", &ans);

	if(ans == 'Y' || ans == 'y') {
		printf("Enter the number of stops: ");
		scanf("%d", no_of_stops);
		char stops[no_of_stops];

		for(i=0; i<no_of_stops; i++) {
			printf("Enter the stop: ");
			scanf("%s", &stops[i]);
		}
	}
	
}
