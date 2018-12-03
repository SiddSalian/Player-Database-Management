#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct player_data{
	char name[50];
	char current_status[10];
	int jersey_no;
	char jersey_name[15];
	char batch[10];
	int age;
	char gender[6];
	int tournaments_played;
};

void add_player(struct player_data player, FILE *fp){
	printf("Name -> ");
	scanf("%s", player.name);
	fflush(stdin);
	printf("Current Status -> ");
	scanf("%s", player.current_status);
	fflush(stdin);
	printf("Jersey Number -> ");
	scanf("%d", &player.jersey_no);
	fflush(stdin);
	printf("Jersey Name -> ");
	scanf("%s", player.jersey_name);
	fflush(stdin);
	printf("Batch -> ");
	scanf("%s", player.batch);
	fflush(stdin);
	printf("Age -> ");
	scanf("%d", &player.age);
	fflush(stdin);
	printf("Gender -> ");
	scanf("%s", player.gender);
	fflush(stdin);
	printf("Number of tournaments played -> ");
	scanf("%d", &player.tournaments_played);
	fflush(stdin);
	fwrite(&player, sizeof(player), 1, fp);
	fclose(fp);
}

int main(void){

	struct player_data player;
	FILE* fp;

	return 0;
}