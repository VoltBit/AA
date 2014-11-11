#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BAND_LENGTH 1000
#define MAX_CHARACTERS 255
#define MAX_STATES 255

// Characters and are encoded using 'char'
typedef char Character;
typedef int State;
typedef int Bool;
typedef struct {
	State nextState;
	Character toWrite;
	int moveDirection;
} Transition;

#define LEFT_BOUNDARY 0
#define BAND_END 3

#define True 1
#define False 0

/* the alpahbet:
	sig = { >, 0, 1, #}
	sig will be represented in the input file like this:
	> -> 
*/

#define LEFT -1 // Move the current index to the left
#define RIGHT 1 // Move the current index to the right
#define HALT 0

/* States */

#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7
#define Success 8
#define Fail 9

int states[] = {0,1,2,3,4,5,6,7}; // non-final states
char sig[] = ">01#";
Character band[MAX_BAND_LENGTH];
State currentState = S0;
int currentIndex = 1;
long transitionsMade = 0L;
Transition transitionTable[MAX_STATES][MAX_CHARACTERS];

int convert(char x){
	/* 
		function that creates a relationship between alphabet characters
		and memory representation
		note that alphabet order si important
		sig = { >, 0, 1, #} 
	*/
	int i;
	for(i = 0; i < strlen(sig); i++){
		if(x == sig[i])return i;
	}
	printf("\n\nConvert error: %c\n\n",x);
	return -1;
}

static void initTransitionTable() {

}

static void initBand() {
	int currentIndex = 1;

	band[0] = LEFT_BOUNDARY;
	band[MAX_BAND_LENGTH-1] = BAND_END;
}

static Bool makeTransition() {
	// The machine went out of band or reached a Fail state
	if (currentIndex < 0 || currentIndex >= MAX_BAND_LENGTH ||
		currentState == Fail)
		return False;
	// The machine reached the Success state
	if (currentState == Success)
		return True;
	Transition currentTransition;
	if(convert(band[currentIndex])!=-1)
		currentTransition = transitionTable[currentState][convert(band[currentIndex])];
	else return 0;

	transitionsMade++;
	currentState = currentTransition.nextState;
	band[currentIndex] = currentTransition.toWrite;
	currentIndex += currentTransition.moveDirection;

	return makeTransition();
}

void insertVal(char *file){
	int i = 0,j,q;
	char dump;
	FILE *f = fopen(file,"r");
	do{
		fscanf(f,"%c",&band[i]);
		printf("%c",band[i]);
		i++;
	}while(band[i - 1] != '\n');
	band[i] = '\0';
	i = 0;
	while(!feof(f)){
		q = 0;
		for(j = 0; j < 3 * strlen(sig); j+=3){
			fscanf(f,"%i",&transitionTable[i][q].nextState);
			fscanf(f,"%c",&transitionTable[i][q].toWrite);
			fscanf(f,"%i",&transitionTable[i][q].moveDirection);
			q++;
		}
		i++;
		fscanf(f,"%c",&dump);
	}
}

void display(){
	int i = 0,j,q;
	int statesNumber = sizeof(states)/sizeof(states[0]);
	printf("Band: %i\n",statesNumber);
	while(band[i]){
		printf("%c",band[i++]);
	}

	printf("\nTransitions: \n");
	for(i = 0; i < statesNumber; i++){
		q = 0;
		for(j = 0; j < strlen(sig); j++){
			printf("%i ",transitionTable[i][q].nextState);
			printf("%c ",transitionTable[i][q].toWrite);
			printf("%i ",transitionTable[i][q].moveDirection);
			q++;
		}
		printf("\n");
	}
}

int main(void) {
	initBand();
	insertVal("data.in");
	Bool outcome = makeTransition();
	printf("MT made %ld transitions, and reached %s state.\n",
		transitionsMade, outcome ? "SUCCESS" : "FAIL");
	display();
	return 0;
}
