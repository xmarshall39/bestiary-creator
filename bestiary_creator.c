#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAMES 10
typedef unsigned int UI;

struct enemy {
	char name[32];
	int level;
	int health;
	char type;
};


int rand_range(int upper, int lower) {
	return (rand() % (upper - lower + 1) + lower);
}



void request_names(char ** names, int num_names) {
	
	char buffer[64];
	
	for (UI i = 0; i < num_names; ++i) {	//If I didn't have MAX_NAMES, use this for i limit: sizeof(names) / sizeof(names[0]
		printf("Looping %d Times:\n", num_names);
		printf("Enemy %d: ", i+1);
		fgets(buffer, 64, stdin);
		//Elim new line
		buffer[strcspn(buffer, "\n")] = 0;
		
		//Allocate memory for each array value
		puts("Before Malloc");
		names[i] = (char *)malloc((strlen(buffer) + 1));
		//Copy data over
		puts("After Malloc");
		strcpy_s(names[i], strlen(buffer) + 1, buffer);
		
		printf("%s :: Bytes: %d\n", names[i], _msize(names[i]));
		//Buffer Reset Automatically
		
	}
}

//Dynamically generate an array of struct pointers
//This really only makes sense if I'm rearranging the array at all
//But I'm doing it for the sake of writing the code
void build_bestiary(struct enemy ** bestiary, char ** names, int num_names){
	
	
	//How can I determine the lenght of bestiary if I somehow lost num_names?
	//_msize(bestiary) / sizeof(names[0]) -- Will tell me how many pointers I have in the sequence
	
	//Request user input for enemy names.
	for (UI i = 0; i < num_names; ++i) {

		bestiary[i] = (struct enemy *)malloc(sizeof(struct enemy));
		
		//Remember, you can't use = to copy over an array
		strcpy_s(bestiary[i]->name, 32, names[i]);
		bestiary[i]->level = rand_range(100, 0);
		bestiary[i]->health = bestiary[i]->level * 13;
		bestiary[i]->type = rand_range(90, 65);

		
	}
	//Change the return to void and have it take in a parameter instead
	return;
}

void print_bestiary(struct enemy ** bestiary, int num_names) {
	puts("\t\t~BESTIARY~\n");
	for (UI i = 0; i < num_names; ++i) {
		printf("%s (Lv%d)\n", bestiary[i]->name, bestiary[i]->level);
		printf("Health: %d/%d\nType: %c\n\n", bestiary[i]->health, bestiary[i]->health, bestiary[i]->type);
	}
}

void write_bestirary(struct enemy ** bestiary, int num_names, FILE * bestiary_file) {

	if (bestiary_file == NULL) {
		printf("Unable to read file.");
		return;
	}
	
	fputs("\t\t~BESTIARY~\n", bestiary_file);
	for (UI i = 0; i < num_names; ++i) {
		fprintf(bestiary_file, "%s (Lv%d)\n", bestiary[i]->name, bestiary[i]->level);
		fprintf(bestiary_file, "Health: %d/%d\nType: %c\n\n", bestiary[i]->health, bestiary[i]->health, bestiary[i]->type);
	}

	
}

int main(int argc, char* argv[]) {

	char buffer[32];
	char * ptr;
	int num_names;
	

	//Ask for a valid number of monster names
	do {
		printf("How many monsters (up to 10) would you like to create?\t");
		fgets(buffer, 32, stdin);
		buffer[strcspn(buffer, "\n")] = 0;
		strtol(buffer, &ptr, 10);
		num_names = strtol(buffer, &ptr, 10);
	} while (num_names > MAX_NAMES || num_names <= 0);
	
	printf("Please enter %d names:\n", num_names);

	
	
	char ** names = malloc(num_names * sizeof(char*));
	
	printf("Memory Allocated for array of name pointers: %d Bytes.\n", _msize(names));
	request_names(names, num_names);

	struct enemy ** bestiary = (struct enemy**)malloc(num_names * sizeof(struct enemy *));
	build_bestiary(bestiary, names, num_names);
	print_bestiary(bestiary, num_names);
	
	//Write to a file
	FILE* bestiary_file;
	fopen_s(&bestiary_file, "bestiary.txt", "w");
	write_bestirary(bestiary, num_names, bestiary_file);
	fclose(bestiary_file);
    return 0;
}