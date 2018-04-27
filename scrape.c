#include <stdio.h>
#include <string.h>

main(void){
	//Will store all the words counted from the files
	char *words[2000];
	int wordcount = ReadWordsInFile("Bayern.txt",words,2000);
	//Counts & prints the number of occurences for each word
	/*for(int i=0;i<wordcount, i++){
	int n=CountWordOccurences(words[i],"Bayern.txt");
	printf("we found the word %s in the file %d time\n", words[i], );
	}*/
	
	//StoreToTxtFile("StoreWords",words,2000);
	printf("There are %d words in your input file\n", wordcount);
	int i;
	for(i=0;i<wordcount;i++){
	printf("The %d word is %s\n",i, words[i]);
	}
}

int ReadWordsInFile(const char *filename, char *words[], int max){
	//Open the text file for reading
	FILE *fileptr = fopen(filename, "r");
	if(fileptr == NULL){
	//Debugging purposes
	printf("The file does not exist");
	return 0;
	}
	int i; //control the for loop
	char temp[200]; //Holds the words that are read from the file individually
	for(i=0; i<max; ++i){
	//use fscanf to read wors from the file.
	//fscanf(file ptr,arguments,ptr to store)
	if(fscanf(fileptr,"%s",temp) != 1)
	//checks for syntax errors in the input and EOF
	break;
	//Allocate memory or the word, and store in array
	words[i] = strdup(temp);
}
	//close the opened file
	fclose(fileptr);
	//Returns the number of words in the file
	return i;

}
