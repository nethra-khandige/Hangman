#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct word {
	size_t length;//size_t is a data type which contains the return value of sizeof and can store the maximum size of an array in the system(32,64 bit)
	char * text;
};

struct wordlist {
	size_t count;
	struct word * list[90000];
	size_t maxlen;
} * words;

void load(char * path) {
	char temp[30];
	size_t index = 0;

	words = malloc(sizeof(struct wordlist));
	words->maxlen = 1;

	FILE * pf;
	pf = fopen(path, "r");
	if (pf == NULL) {
		printf("\nno wordlist found at %s\n", path);
		exit(1);
	} 
	while (fscanf(pf, "%s", temp) != EOF) {
		size_t length = strlen(temp);
		if (words->maxlen < length) {
			words->maxlen = length;
		}
		words->list[index] = malloc(sizeof(struct word));
		words->list[index]->text = (char *)malloc(length*sizeof(char)+1);
		strcpy(words->list[index]->text, temp);
		words->list[index]->length = length;
		index++;
	}
	words->count = index;
}

int play(int minlen) {
	printf("\n");

	srand(time(NULL));//to make sure same random words dont repeat
	do {
		struct word * word;
		do {
			word = words->list[rand()%words->count];//generating random words
		} while (word->length < minlen);

		int guess;
		int chances =5;
		int w=0;
		char wrong[30] = "";
		char found[word->length+1];
//ptr ==> Starting address of memory to be filled
// x   ==> Value to be filled
// n   ==> Number of bytes to be filled starting 
//         from ptr to be filled
//void *memset(void *ptr, int x, size_t n);
		memset(found, '\0', word->length+1);//memset() is used to fill a block of memory with a particular value.
		memset(found, '_', word->length);

		printf("The word: %s | chances remaining: %i | wrongly guessed: '%s'  ", found, chances, wrong);
		do {
			guess = getchar();
			if (guess == '\n') {
				printf("The word: %s | chances remaining: %i | wrongly guessed: '%s'  Enter your guessed alphabet:", found, chances, wrong);
				continue;
			}
			else if (guess == EOF) {
				printf("\n");
				return 0;
			}
			else if (guess < 97 || guess > 122) {
				continue;
			}
			else {
				int i;
				for (i = 0; i < strlen(found); i++) {
					if (word->text[i] == guess) {
						found[i] = guess;
					}
					//else ();
				}
				if (strchr(found, guess) == NULL && strchr(wrong, guess) == NULL) {//strchr(stringtobescanned,character)->returns a pointer to the first occurrence of the character c in the string str or NULL if the character is not found.
					strncat(wrong, (char *)&guess, 30);//strncat(stringwheretoappend,stringfromwheretoappend,maxno.ofchartoappend)
					w++;
					switch (w)
					{
						case 1:
							printf(" O\n");
							break;
						case 2:
							printf(" O\n |\n");
							break;
						case 3:
							printf(" O\n |\n /\n");
							break;
						case 4:
							printf(" O\n |\n /\\\n");
							break;
						case 5:
							printf(" O\n +\n /\\\n");
							break;

					}
					
					chances--;
				}
			}
		} while (strchr(found, '_') != NULL && chances > 0);
		printf("solved %s | chances %i | wrong '%s'\n", word->text, chances, wrong);
		if (chances > 0) {
			printf("Phew!Escaped the noose!:-)\n\n");
		} else {
			printf("You got hanged!:-(\n\n");
		}
		while (getchar() != '\n') { /* do nothing */ };
	} while(1);
	return 0;
}

int main(int argc, char * argv[]) {

	char * path = "C:/Users/Gaurav/Desktop/C,Scilab/projects-C/hangman/wordlist";
	long minlen = 3;
	load(path);
 	return play(minlen);
}