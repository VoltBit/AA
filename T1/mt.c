#include <stdio.h>

#define MAX_BAND_LENGTH 1000
#define MAX_CHARACTERS 255
#define MAX_STATES 255

// Characters and are encoded using 'char'
typedef char Character;
typedef char State;
typedef int Bool;
typedef struct {
	State nextState;
	Character toWrite;
	int moveDirection;
} Transition;

#define LEFT_BOUNDARY '>'
#define RIGHT_BOUNDARY '<'
#define BAND_END '#'

#define True 1
#define False 0

// To allow more states/characters one could
// simply switch from chars to ints

#define LEFT -1 // Move the current index to the left
#define RIGHT 1 // Move the current index to the right

// Common states
#define Start 0
#define Running 1
#define Success 2
#define Fail 3

Character band[MAX_BAND_LENGTH];
State currentState = Start;
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

int main(void) {
	initBand();
	Bool outcome = makeTransition();
	printf("MT made %ld transitions, and reached %s state.\n",
		transitionsMade, outcome ? "SUCCESS" : "FAIL");
	return 0;
}
