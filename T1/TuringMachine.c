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

typedef struct {
	int bandSize;
	int transitionsSize;
}SizePackage;

#define LEFT_BOUNDARY '>'
#define RIGHT_BOUNDARY '<'
#define BAND_END '#'

#define True 1
#define False 0

// To allow more states/characters one could
// simply switch from chars to ints

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
#define Fail -1

Character band[MAX_BAND_LENGTH];
State currentState = S0;
int currentIndex = 1;
long transitionsMade = 0L;
Transition transitionTable[MAX_STATES][MAX_CHARACTERS];

static void initTransitionTable() {

}

static void initBand() {
	int currentIndex = 1;
	// Put an end to the band in the left
	band[0] = BAND_END;
	band[1] = LEFT_BOUNDARY;

	// Put an end to the band in the right
	band[MAX_BAND_LENGTH-1] = BAND_END;
	band[MAX_BAND_LENGTH-2] = RIGHT_BOUNDARY;
}

static Bool makeTransition() {
	// The machine went out of band or reached a Fail state
	if (currentIndex < 0 || currentIndex >= MAX_BAND_LENGTH ||
		currentState == Fail)
		return False;
	// The machine reached the Success state
	if (currentState == Success)
		return True;

	Transition currentTransition = transitionTable[currentState][band[currentIndex]];

	transitionsMade++;
	currentState = currentTransition.nextState;
	band[currentIndex] = currentTransition.toWrite;
	currentIndex += currentTransition.moveDirection;

	return makeTransition();
}

void insertVal(SizePackage *sizes){
	int i;
	char x[4];
	FILE *f = fopen("data.in","r");
	do{
		fscanf(f,"%c",&band[i]);
		i++;
	}while(band[i - 1] != '\n');
	sizes->bandSize = i;
	i = 0;
	while(fgets(x,sizeof(x),f)){
		transitionTable[i].nextState = x[0] - '0';
		transitionTable[i].toWrite = x[1];
		transitionTable[i].moveDirection = x[2];
		i++;
	}
	sizes->transitionsSize = i;
}

void display(int n){
	int i;
	while(n){
		printf("%c",band[i++]);
		n--;
	}
}

int main(void) {
	/*SizePackage sizes;
	initBand();
	insertVal(&sizes);
	Bool outcome = makeTransition();
	printf("MT made %ld transitions, and reached %s state.\n",
		transitionsMade, outcome ? "SUCCESS" : "FAIL");*/
	return 0;
}
