#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Point Point{
	int x,y;
};

float getDistance(Point a, Point b){
	int difX = a.x - b.x;
	int difY = a.y - b.y;
	return sqrt(difX * difX + difY * difY);
}

int main(){

}