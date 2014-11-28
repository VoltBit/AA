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

int sortX(const void* a, const void* b){
    Point *pA = (Point *)a,  *pB = (Point *)b;
    return (pA->x - pB->x);
}

int sortY(const void* a, const void* b){
    Point *pA = (Point *)a,   *pB = (Point *)b;
    return (pA->y - pB->y);
}

int minStripDistance1(Point strip[], int size, float d, Point &p1, Point &p2){
	/*
		Functia returneza distana minima dintre doua puncta aflate intr-o
		banda de dimensiune size. Parametrii p1 si p2 retin coordonatele celor
		mai apropiate doua puncte (despartite de d). Distanta minima pana in
		momentul apelarii este d.
	*/
	float min = d;
	int i,j;
	float aux;
	for(i = 0; i < size; i++){
		for(j = i+1; j < size && (strip[j].y - strip[i].y) < min; j++){
			/*
				Punctele din banda sunt ordonate dupa y deci daca distanta
				minima este depasita pe axa y nu se continua verificarea pentru
				punctul curent.
			*/
			aux = getDistance(strip[i],strip[j]);
			if( aux < min ){
				min = aux;
				p1.x = strip[i].x;
				p1.y = strip[i].y;
				p2.x = strip[j].x;
				p2.y = strip[j].y;
			}
		}
	}
	return min;
}

int minStripDistance2(Point strip[], int size, float d, Point &p1, Point &p2){
	float min = d;
	int i,j;
	for(i = 0; i < size; i++){
		for(j = i+1; j < size; j++){
			aux = getDistance(strip[i],strip[j]);
			if( aux < min ){
				min = aux;
				p1.x = strip[i].x;
				p1.y = strip[i].y;
				p2.x = strip[j].x;
				p2.y = strip[j].y;
			}
		}
	}
	return min;
}
float closestPair(Point points[], Point strip[], int pointNumber, Point &p1, Point &p2){
	/*
		Gaseste perechea cu ce mai mica distanta si returneaza distanta.
		Cele doua puncte sunt returnate prin parametrii p1 si p2.
	*/
	Point aux1, aux2, aux3, aux4, midPoint;
	int i, j = 0, mid = pointNumber / 2;
	float right,left,minDistance;
	midPoint = points[mid];
	if(pointNumber <= 3){
		/*
			Caz in care nu pot creea benzi si verifica direct.
		*/
			return minStripDistance2(points,pointNumber,aux1,aux2);
	}
	right = closestPair(points,strip,pointNumber,aux1,aux2);
	left = closestPair(points + mid,strip,pointNumber,aux3,aux4);
	if(right < left){
		p1.x = aux3.x;
		p1.y = aux3.y;
		p2.x = aux4.x;
		p2.y = aux4.y;
		minDistance = right;
	}else{
		p1.x = aux1.x;
		p1.y = aux1.y;
		p2.x = aux2.x;
		p2.y = aux2.y;
		minDistance = left;
	}
	for(i = 0; i < pointNumber; i++){
		if(abs(points[i].x - midPoint.x) < minDistance){
			strip[j] = points[i];
			j++;
		}
	}
}

void findClosest(){
	
}

int main(){

	findClosest();
	return 0;
}