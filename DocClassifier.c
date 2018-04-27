#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2000
#define NUM_KEYWORDS 6 //set the number of category keywords here
#define STR_LENGTH 30

struct Health {
	char *health_bow[NUM_KEYWORDS];
	int key_hits;
};

//TODO add your struct category;

struct Health health_articles;

void setHealthKeywords(struct Health *health_articles);

int main(int argc, char *args[]) {
	if (argc != 2) {
		printf("Enter file name in command line!\n");
		return 0;
	}
	//populating struct category with keywords retrieved from training data
	setHealthKeywords(&health_articles); 
	char line[1000];
	FILE *file;
	file = fopen(args[1], "r");  //r for reading; will throw segmentation fault if file not found ; use commnad line input for filename!
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
	}
	printf("Number of hits for HEALTH category: %d\n", health_articles.key_hits);
	//largest number of hits will determine the category of the article.
	fclose(file);
	return 0;
}

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
