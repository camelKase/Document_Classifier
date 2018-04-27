#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_KEYWORDS 6 //set the number of category keywords here

struct Health {
	char *category;
	char *health_bow[NUM_KEYWORDS];
	int key_hits;
};
struct Technology {
	char *category;
	char *tech_bow[NUM_KEYWORDS];
	int key_hits;
};
struct Sports {
	char *category;
	char *sports_bow[NUM_KEYWORDS];
	int key_hits
};
struct Food {
	char *category;
	char *food_bow[NUM_KEYWORDS];
	int key_hits
};

struct Health health_articles;
struct Technology tech_articles;
struct Sports sports_articles;
struct Food food_articles;

//TODO add your struct category;

void setHealthKeywords(struct Health *health_articles);
void setTechKeywords(struct Technology *tech_articles);
void setSportsKeywords(struct Sports *sports_articles);
void setFoodKeywords(struct Food *food_articles);
void* search_for_hits(struct Health *health_articles, struct Technology *tech_articles, 
		struct Sports *sports_articles, struct Food *food_articles, char *args[]);

int main(int argc, char *args[]) {
	if (argc != 2) {
		printf("Enter file name in command line!\n");
		exit(-1);
	}
	health_articles.category = "HEALTH";
	tech_articles.category = "TECHNOLOGY";
	sports_articles.category = "SPORTS";
	food_articles.category = "FOOD";

	//populating struct category with keywords retrieved from training data
	setHealthKeywords(&health_articles);
	setTechKeywords(&tech_articles);
	setSportsKeywords(&sports_articles);
	setFoodKeywords(&food_articles);

	char line[1000];
	FILE *file;
	/*file = fopen(args[1], "r");  //r for reading; will throw segmentation fault if file not found ; use commnad line input for filename!
	if (file == NULL) {
		printf("File not found!");
		return 0;
	}
	while (fgets(line, 1000, file) != NULL) {
		for (int i = 0; i < NUM_KEYWORDS; i++) {
			if (strcasestr(line, health_articles.health_bow[i]) != NULL) {
				health_articles.key_hits++;
			}
		}
		// TODO loop through the struct for your category here
	}*/
	search_for_hits(&health_articles, &tech_articles, &sports_articles, &food_articles, &args[1]);
	return 0;
}

void* search_for_hits(struct Health *health_articles, struct Technology *tech_articles, 
		struct Sports *sports_articles, struct Food *food_articles, char *args[]) {
	char line[1000];
	FILE *file;
	file = fopen(*args, "r");
	if (file == NULL) {
		printf("File not found");
	}
	while (fgets(line, 1000, file) != NULL) {
		for (int i = 0; i < NUM_KEYWORDS; i++) {
			if (strcasestr(line, health_articles -> health_bow[i]) != NULL) {
				health_articles -> key_hits++;
			}
			if (strcasestr(line, tech_articles -> tech_bow[i]) != NULL) {
				tech_articles -> key_hits++;
			}
			if (strcasestr(line, sports_articles -> sports_bow[i]) != NULL) {
				sports_articles -> key_hits++;
			}
			if (strcasestr(line, food_articles -> food_bow[i]) != NULL) {
				food_articles -> key_hits++;
			}
		}
	}
	fclose(file);   //must close file or else will throw Segmentation fault (core dumped)
	//print statements for debugging purposes
	printf("Number of hits for HEALTH category: %d\n", health_articles -> key_hits);
	printf("Number of hits for TECHNOLOGY category: %d\n", tech_articles -> key_hits);
	printf("Number of hits for SPORTS category: %d\n", sports_articles -> key_hits);
	printf("Number of hits for FOOD category: %d\n", food_articles -> key_hits);
	int hits[] = {health_articles -> key_hits, tech_articles -> key_hits,
		sports_articles -> key_hits, food_articles -> key_hits};
	int highest_hits = 0;
	int index_of_category = 0;
	for (int i = 0; i < 3; i++) {
		if (hits[i] > hits[i + 1]) {
			highest_hits = hits[i];
			index_of_category = i;
		}
	}
	printf("%d\n", highest_hits);
	//prints the category the article most likely falls in based off of number of hits
	switch (index_of_category) {
		case 0 : printf("%s\n", health_articles -> category);
				 break;
		case 1 : printf("%s\n", tech_articles -> category);
			     break;
		case 2 : printf("%s\n", sports_articles -> category);
				 break;
		case 3 : printf("%s\n", food_articles -> category);
				 break;
	}
}

//TODO have the method read from separate file that contains the keywords
void setHealthKeywords(struct Health *health_articles) {
	health_articles -> health_bow[0] = "pain";
	health_articles -> health_bow[1] = "study";
	health_articles -> health_bow[2] = "findings";
	health_articles -> health_bow[3] = "long-term";
	health_articles -> health_bow[4] = "healthy";
	health_articles -> health_bow[5] = "results";
	health_articles -> key_hits = 0;
}

//TODO add your method here to set the keywords for your struct
void setTechKeywords(struct Technology *tech_articles) {
	tech_articles -> tech_bow[0] = "computer";
	tech_articles -> tech_bow[1] = "processor";
	tech_articles -> tech_bow[2] = "network";
	tech_articles -> tech_bow[3] = "technology";
	tech_articles -> tech_bow[4] = "screen";
	tech_articles -> tech_bow[5] = "keyboard";
	tech_articles -> key_hits = 0;
}
void setSportsKeywords(struct Sports *sports_articles) {
	sports_articles -> sports_bow[0] = "point";
	sports_articles -> sports_bow[1] = "team";
	sports_articles -> sports_bow[2] = "baseball";
	sports_articles -> sports_bow[3] = "basketball";
	sports_articles -> sports_bow[4] = "throw";
	sports_articles -> sports_bow[5] = "catch";
	sports_articles -> key_hits = 0;
}
void setFoodKeywords(struct Food *food_articles) {
	food_articles -> food_bow[0] = "cook";
	food_articles -> food_bow[1] = "minutes";
	food_articles -> food_bow[2] = "prepare";
	food_articles -> food_bow[3] = "oven";
	food_articles -> food_bow[4] = "pan";
	food_articles -> food_bow[5] = "oil";
	food_articles -> key_hits = 0;
}
