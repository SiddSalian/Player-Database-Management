#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structure for Player's Database
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

//Structure for tournaments database
#define SQUADMAX 20 // Maximum Squad size
struct tournament_data{
	char tournName[50];
	char level[50];
	char date[8]; /* YYYY/MM */
	char host[50];
	int noOfPlayers;
	char squad[20][50];
};

int player_count(struct player_data player, FILE* fp){
	int player_count = 0;
	while(fread(&player, sizeof(player), 1, fp)){
		player_count++;
	}
	return player_count;
}

void add_tournament(struct tournament_data tourn, struct player_data player, FILE *afp, FILE *fp){
	printf("Tournament Name -> ");
	scanf(" %50[^\n]", tourn.tournName);
	fflush(stdin);
	printf("Level -> ");
	scanf(" %50[^\n]", tourn.level);
	fflush(stdin);
	printf("Dates (YYYY/MM) -> ");
	scanf(" %50[^\n]", tourn.date);
	fflush(stdin);
	printf("Hosted by -> ");
	scanf(" %50[^\n]", tourn.host);
	fflush(stdin);
	printf("Enter the number of players in the squad: ");
	scanf("%d", &tourn.noOfPlayers);
	fflush(stdin);
	printf("Squad list -> \n");
	for (int i=0; i<tourn.noOfPlayers; i++) {
		printf("%d. ", i+1);
		scanf(" %50[^\n]", tourn.squad[i]);
		fflush(stdin);
		int temp_count = 0;
		while(fread(&player, sizeof(player), 1, fp)){
			if(strcmp(tourn.squad[i], player.name) != 0){
				temp_count++;
			}
			if(temp_count == player_count(player ,fp)){
				printf("Doesn't match any record in database. Please insert correct name!\n");
				i--;
			}
		}
		rewind(fp);
	}
	fflush(stdin);
	fwrite(&tourn, sizeof(tourn), 1, afp);
	fclose(afp);
	fclose(fp);
}

void see_tournament_records(struct tournament_data tourn, FILE* afp){
	while(fread(&tourn, sizeof(tourn), 1, afp)){
		printf("\nName: %s\nLevel: %s\nDates: %s\nHosted by: %s\n", 
			tourn.tournName, tourn.level, tourn.date, tourn.host);
		printf("Squad List:\n");
		for(int i=0; i<tourn.noOfPlayers; i++){
			printf("%d. %s\n", i+1, tourn.squad[i]);
		}
	}
	fclose(afp);
}

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

void search_name(struct player_data player, FILE* fp){
	printf("Enter the name: ");
	char name[20];
	scanf("%s", name);
	fflush(stdin);
	while(fread(&player, sizeof(player), 1, fp)){
		if(strcmp(name, player.name)==0){
			printf ("\nname = %s\ncurrent status = %s\njersey_no = %d\njersey name = %s\nbatch = %s\nage = %d\ngender = %s\ntournaments played = %d\n", player.name, player.current_status, 
			        player.jersey_no, player.jersey_name, player.batch, player.age, player.gender, player.tournaments_played);
		}
	}
}

void search_jersey_no(struct player_data player, FILE* fp){
	printf("Enter the jersey number: ");
	int number;
	scanf("%d", &number);
	fflush(stdin);
	while(fread(&player, sizeof(player), 1, fp)){
		if(number == player.jersey_no){
			printf ("\nname = %s\ncurrent status = %s\njersey_no = %d\njersey name = %s\nbatch = %s\nage = %d\ngender = %s\ntournaments played = %d\n", player.name, player.current_status, 
			        player.jersey_no, player.jersey_name, player.batch, player.age, player.gender, player.tournaments_played);
		}		
	}
}

void see_player_records(struct player_data player, FILE* fp){
	while(fread(&player, sizeof(player), 1, fp)){
	printf ("\nname = %s\ncurrent status = %s\njersey_no = %d\njersey name = %s\nbatch = %s\nage = %d\ngender = %s\ntournaments played = %d\n", player.name, player.current_status, 
		        player.jersey_no, player.jersey_name, player.batch, player.age, player.gender, player.tournaments_played);}
		fclose (fp);
		/*player_count(player, fp);
		printf("\nplayer count: %d\n", player_count(player, fp));*/
}

void edit_record(struct player_data player,FILE* fp){
	char name[20];
	printf("Enter name to edit: ");
	scanf("%s", name);
	fflush(stdin);
	while(fread(&player, sizeof(player), 1, fp)){
		if(strcmp(name, player.name) == 0){
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

			fseek(fp, -sizeof(player), SEEK_CUR);
			fwrite(&player, sizeof(player), 1, fp);
			fclose(fp);
		}
	}
}

void search_by_category(struct player_data player, FILE* fp){
	int category;
	printf("Categories: 1- Current Status, 2- Batch, 3- Gender\n--> ");
	scanf("%d", &category);
	int current_status;
	switch(category){
		case 1:
			printf("Get a list of 1- Active Players, 2- Inactive players, 3- Alumni\n--> ");
			scanf("%d", &current_status);
			int i = 1;
			switch(current_status){
				case 1:
					while(fread(&player, sizeof(player), 1, fp)){
						if(strcmp("active", player.current_status) == 0){
							printf("%d. %s\n", i, player.name);
							i++;
						}
					}
				break;

				case 2:
					while(fread(&player, sizeof(player), 1, fp)){
						if(strcmp("inactive", player.current_status) == 0){
							printf("%d. %s\n", i, player.name);
							i++;
						}
					}
				break;

				case 3:
					while(fread(&player, sizeof(player), 1, fp)){
						if(strcmp("alumni", player.current_status) == 0){
							printf("%d. %s\n", i, player.name);
							i++;
						}
					}
				break;
			break;}
		

		{case 2:
			printf("Enter the batch(eg., ug18): ");
			char batch[10];
			scanf("%s", batch);
			int l = 1;
			while(fread(&player, sizeof(player), 1, fp)){
					if(strcmp(batch, player.batch) == 0){
							printf("%d. %s\n", l, player.name);
							i++;
					}
				}
		break;}

		{case 3:
			printf("Get a list of 1- Female players, 2- Male players\n--> ");
			int gender;
			scanf("%d", &gender);
			int p = 1;
			switch(gender){
				case 1:
					while(fread(&player, sizeof(player), 1, fp)){
						if(strcmp("female", player.gender) == 0){
								printf("%d. %s\n", p, player.name);
							p++;
						}
					}
				break;

				case 2:
					while(fread(&player, sizeof(player), 1, fp)){
						if(strcmp("male", player.gender) == 0){
								printf("%d. %s\n", p, player.name);
							p++;
						}
					}
				break;
		break;}
		}
	}
	fclose(fp);
}


int main(){
	struct player_data player; 
	struct tournament_data tourn;
	FILE* fp;
	FILE* afp;

	int opt = 0;
		while(opt != 9){
		printf("\nMENU\n");
		printf("1. Add a player\n");
		printf("2. Search player by name\n");
		printf("3. Search player by jersey number\n");
		printf("4. See all player records\n");
		printf("5. Edit a record\n");
		printf("6. Search by category\n");
		printf("7. Add a tournament\n");
		printf("8. See all tournament records\n");
		printf("9. Exit\n");
		printf("Choose an option: ");
		scanf("%d", &opt);

		switch(opt){
			case 1:
				fp = fopen("player_database.txt","ab");
				add_player(player, fp);
				break;

			case 2:
				fp = fopen("player_database.txt","rb");
				search_name(player, fp);
				break;

			case 3:
				fp = fopen("player_database.txt","rb");
				search_jersey_no(player, fp);
				break;

			case 4:
				fp = fopen("player_database.txt", "rb");
				see_player_records(player, fp);
				break;

			case 5:
				fp = fopen("player_database.txt","rb+");
				edit_record(player, fp);
				break;

			case 6:
				fp = fopen("player_database.txt", "rb");
				search_by_category(player, fp);
				break;

			case 7:
				afp = fopen("tournament_database.txt", "ab");
				fp = fopen("player_database.txt", "rb");
				add_tournament(tourn, player, afp, fp);
				break;
			case 8:
				afp = fopen("tournament_database.txt", "rb");
				see_tournament_records(tourn, afp);
				break;
			case 9:
				exit(1);
		}
	}
	return 0;
}