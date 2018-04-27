#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_KEYWORDS 6 //set the number of category keywords here
#define NUM_CATEGORIES 6

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
	int key_hits;
};
struct Food {
	char *category;
	char *food_bow[NUM_KEYWORDS];
	int key_hits;
};

struct Science {
    char *category;
    char *science_bow[NUM_KEYWORDS];
    int key_hits;
};

struct Education {
    char *category;
    char *education_bow[NUM_KEYWORDS];
    int key_hits;
};


struct Health health_articles;
struct Technology tech_articles;
struct Sports sports_articles;
struct Food food_articles;
struct Science science_articles;
struct Education education_articles;
//TODO add your struct category;
void setScienceKeywords(struct Science *science_articles);
void setHealthKeywords(struct Health *health_articles);
void setTechKeywords(struct Technology *tech_articles);
void setSportsKeywords(struct Sports *sports_articles);
void setFoodKeywords(struct Food *food_articles);
void setEducationKeywords(struct Education *education_articles);
void search_for_hits(struct Health *health_articles, struct Technology *tech_articles, 
		struct Sports *sports_articles, struct Food *food_articles, struct Science *science_articles, struct Education *education_articles, char *args[]);

int main(int argc, char *args[]) {
	if (argc != 2) {
		printf("Enter file name in command line!\n");
		exit(-1);
	}
	health_articles.category = "HEALTH";
	tech_articles.category = "TECHNOLOGY";
	sports_articles.category = "SPORTS";
	food_articles.category = "FOOD";
	science_articles.category = "SCIENCE";
	education_articles.category = "EDUCATION";
	//populating struct category with keywords retrieved from training data
	setHealthKeywords(&health_articles);
	setScienceKeywords(&science_articles);
	setTechKeywords(&tech_articles);
	setSportsKeywords(&sports_articles);
	setFoodKeywords(&food_articles);
	setEducationKeywords(&education_articles);

	
	search_for_hits(&health_articles, &tech_articles, &sports_articles, &food_articles,&science_articles,&education_articles, &args[1]);
	return 0;
}

void search_for_hits(struct Health *health_articles, struct Technology *tech_articles, 
		struct Sports *sports_articles, struct Food *food_articles,struct Science *science_articles, struct Education *education_articles, char *args[]) {
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
		    if (strcasestr(line, science_articles -> science_bow[i]) != NULL) {
                science_articles -> key_hits++;
            }
			if (strcasestr(line, education_articles -> education_bow[i]) != NULL) {
                education_articles -> key_hits++;
            }
		}
	}
	fclose(file);   //must close file or else will throw Segmentation fault (core dumped)
	//print statements for debugging purposes
	printf("Number of hits for HEALTH category: %d\n", health_articles -> key_hits);
	printf("Number of hits for TECHNOLOGY category: %d\n", tech_articles -> key_hits);
	printf("Number of hits for SCIENCE category: %d\n", science_articles -> key_hits);
	printf("Number of hits for FOOD category: %d\n", food_articles -> key_hits);
	printf("Number of hits for SPORTS category: %d\n", sports_articles -> key_hits);
	printf("Number of hits for HEALTH category: %d\n", health_articles -> key_hits);
	printf("Number of hits for EDUCATION category: %d\n", education_articles -> key_hits);
	int hits[] = {health_articles -> key_hits, tech_articles -> key_hits,  
		sports_articles -> key_hits, food_articles -> key_hits, science_articles -> key_hits, education_articles -> key_hits}; //{health, tech, sports, food, science, education}
	int highest_hits = 0;
	int index_of_category = 0;
	for (int i = 0; i < NUM_CATEGORIES; i++) {
		if (hits[i] > highest_hits) {
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
        case 4 : printf("%s\n", science_articles -> category);
                 break;
		case 5 : printf("%s\n", education_articles -> category);
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
	tech_articles -> tech_bow[5] = "data";
	tech_articles -> key_hits = 0;
}
void setSportsKeywords(struct Sports *sports_articles) {
	sports_articles -> sports_bow[0] = "points";
	sports_articles -> sports_bow[1] = "team";
	sports_articles -> sports_bow[2] = "baseball";
	sports_articles -> sports_bow[3] = "games";
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
void setScienceKeywords(struct Science *science_articles) {
    science_articles -> science_bow[0] = "astronomy";
    science_articles -> science_bow[1] = "biology";
    science_articles -> science_bow[2] = "genetics";
    science_articles -> science_bow[3] = "scienetist";
    science_articles -> science_bow[4] = "antimatter";
    science_articles -> science_bow[5] = "organism";
    science_articles -> key_hits = 0;
}

void setEducationKeywords(struct Education *education_articles) {
    education_articles -> education_bow[0] = "semester";
    education_articles -> education_bow[1] = "school";
    education_articles -> education_bow[2] = "college";
    education_articles -> education_bow[3] = "grades";
    education_articles -> education_bow[4] = "teachers";
    education_articles -> education_bow[5] = "majors";
    education_articles -> key_hits = 0;
}


