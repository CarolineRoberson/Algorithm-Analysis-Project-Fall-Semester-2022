#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <list>
#include "Point.hpp"

using namespace std;
using namespace point;


void fillSet(list<Point>& set, int size){
	
	for(int i = 0; i < size; i++){
		//Create and add a coordinate pair to each entry in the set
		
		Point coordPair = Point( 						// Generate a number between 0 and 99, then subtract 50 to create semi-random negative values
								((rand() % 100) - 50),	// = x
								((rand() % 100) - 50)	// = y
								);
		cout << "Adding coordPair " << coordPair << " to the set." << endl;
		set.push_back(coordPair);
		
	}
	cout << "Total number of points added: " << size << endl;
	
}

void bruteForceCH(list<Point>& set, int size, list<Point>& result){
	//Choose a point to form the base of the line segment
	for(int i = 0; i < size - 1; i++){
		cout << "i = " << i << endl;
		cout << "EXAMINING STARTING POINT (" << set[i].x << "," << set[i].y << ") ----------" << endl;
		
		//Pick the next point to draw the line segment to
		//We always pick 1 entry ahead of i because a segment from i to j is the same as j to i
		for(int j = i+1; j < size; j++){
			
			cout << "j = " << j << endl;
			//bool isLine = false;	// This will become true if the innermost loop never breaks
			cout << "	Checking line segment (" << set[i].x << "," << set[i].y << ") to (" << set[j].x << "," << set[j].y << ") ----------" << endl;
			
			//Calculate the line segment formed by points i and j
			//using the formula ax + by = c, where a = y2 - y1, b = x1 - x2, and c = x1y2 - y1x2
			//Point 1 (i) will form (x1, y1) and Point 2 (j) will form (x2, y2)
			
			int a = set[j].y - set[i].y; 	// a = y2 - y1
			int b = set[i].x - set[j].x;	// b = x1 - x2
			int c = (set[i].x * set[j].y) - (set[i].y * set[j].x); // c = x1y2 - y1x2 
			
			//Now examine all points to see if they're above, below, or on the line using the formula ax + by - c,
			//where x = set[k].x and y = set[k].y
			//If the next point does not have the same sign as the previous point, this line segment
			//is discarded and we move to the next iteration of loop 2.
			
			bool isLeft = false;	// If the point being compared is left of point i
			bool isRight = false;	// or right of point j, then i-j isn't part of the convex hull
			bool isHull = true;
			for(int k = 0; k < size; k++){
				if((k != i) && (k != j)) { // Skip an iteration if the comparison involves one of the segment endpoints
					cout << "k = " << k << endl;
					//cout << "			sign2 = " << sign2 << "; sign1 = " << sign1 << endl;
					
					cout << "			Looking at point (" << set[k].x << "," << set[k].y << ")" << endl;
					
					int val = (a * set[k].x) + (b * set[k].y) - c;	//Calculating the formula
					cout << "				This point value is " << val << endl;
					
					//Now check whether the value is above, below, or on the line
					//if(val == 0) {cout << "				Part of the line. Skipping" << endl; continue;}	// if it's already part of the line, skip
					if(val > 0) isLeft = true;
					else if(val < 0) isRight = true;
					else {
						if((set[k].x < set[i].x) || (set[k].x > set[j].x)) {
							isHull = false;
							break;
						}
					}
					
					//if((sign2 != -1) && (sign1 != sign2)) {cout << "				Signs don't match. Breaking." << endl; isLine = false; break;}
					//else {cout << "				Signs match. Moving on." << endl; isLine = true;}
					
					//sign2 = sign1;
				
				
				
				}
				
				if(isLeft && isRight) {
					isHull = false;
					break;
				}
				
			}
			
			
			//If we reach here, the line segment must be part of the convex hull, so add it to the set
			if(isHull) {
			cout << "Adding point (" <<  set[j].x << "," <<  set[j].y << ")" << endl; cout << endl;
			result.push_back(set[i]); result.push_back(set[j]);
		
		
	
			}
			
			
		}
		
				
		
		
	}
	
	
}


void quickhullCH(list<Point>& set, int size, list<Point>& result){
	
	
}


int main(int argc, char **argv)
{
	
	//Create an array of 10 - 110 randomized points using the point struct
	int size = rand() % 100 + 10;
	list<point> coordSet;
	cout << "Created a set of size " << size << endl;
	
	//Create and assign a pointer var to reference the array later on
	//point *setptr;
	//setptr = coordSet;
	
	//Fill the array with randomized points
	fillSet(coordSet, size);
	
	
	//Determine the convex hull with the brute force algorithm
	list<point> bruteForceSet;
	//point *bfsetptr = bruteForceSet;		//Passing the function a pointer to indirectly return a list of points with
	bruteForceCH(coordSet, size, bruteForceSet);
	
	//Determine the convex hull with the quickhull algorithm
	list<point> quickhullSet;
	//point *qhsetptr = quickhullSet;			//Passing the function a pointer to indirectly return a list of points with
	quickhullCH(coordSet, size, quickhullSet);
	 
	 
	 /*point set[7] = {{0,0},{2,5},{-3,-2},{4,-1},{-5,3},{-1,6},{-1,3}};
	 point *setptr;
	 setptr = set;
	 list<point> bruteForceSet;
	 bruteForceCH(setptr, 7, bruteForceSet);*/
	 
	 cout << "done" << endl;
	 
	for(auto coord : bruteForceSet) {
		cout << "(" << coord.x << "," << coord.y << ") " << endl;
	}
	

	 
}





