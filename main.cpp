#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <list>
#include <algorithm>
#include <array>
#include <cmath>
#include <cassert>
#include "cdpoint.hpp"

using namespace std;
using namespace cdpoint;


cdpoint::cdpoint* fillSet(cdpoint::cdpoint *set, int size){
	//Generates a full set of random points
	
	
	for(int i = 0; i < size; i++){
		//Create and add a coordinate pair to each entry in the set
		
		cdpoint::cdpoint coordPair = cdpoint::cdpoint( 						// Generate a number between 0 and 99, then subtract 50 to create semi-random negative values
								((rand() % 100) - 50),	// = x
								((rand() % 100) - 50)	// = y
								);
		cout << "Adding coordPair " << coordPair << " to the set." << endl;
		set[i] = coordPair;
		
	}
	cout << "Total number of points added: " << size << endl;
	
	return set;
	
}

bool inSet(cdpoint::cdpoint coord, cdpoint::cdpoint set[], int size) {
	//Checks whether the specified coordinate is in the set
	
	for(int i = 0; i < size; i++) {
		
		if(set[i] == coord) return true;
		
	}
	
	return false;
	
}

cdpoint::cdpoint* sort(cdpoint::cdpoint *set, int size) {
	//Sorts the set in ascending order
	
	cdpoint::cdpoint temp;
	int min;
	for(int i = 0; i < size - 1; i++) {
		min = i;
		
		for(int j = i+1; j < size; j++){
			if(set[j] < set[min]) min = j;
		}
		
		if(min != i) {
			temp = set[i];
			set[i] = set[min];
			set[min] = temp;
		}
		
	}
	
	return set;
	
}

cdpoint::cdpoint* bruteForceCH(cdpoint::cdpoint *set, int size, cdpoint::cdpoint *convexhull){
	//Calculates the convexhull of a set of points by brute force
	//Time complexity: O(n^3)
	
	int answer_index = 0;
	
	//Choose a point to form the base of the line segment
	for(int i = 0; i < size - 1; i++){
		
		//Pick the next point to draw the line segment to
		//We always pick 1 entry ahead of i because a segment from i to j is the same as j to i
		for(int j = i+1; j < size; j++){			
			//Calculate the line segment formed by points i and j
			//using the formula ax + by = c, where a = y2 - y1, b = x1 - x2, and c = x1y2 - y1x2
			//Point 1 (i) will form (x1, y1) and Point 2 (j) will form (x2, y2)
			
			float a = set[j].gety() - set[i].gety(); 	// a = y2 - y1
			float b = set[i].getx() - set[j].getx();	// b = x1 - x2
			float c = (set[i].getx() * set[j].gety()) - (set[i].gety() * set[j].getx()); // c = x1y2 - y1x2 
			
			//Now examine all points to see if they're above, below, or on the line using the formula ax + by - c,
			//where x = set[k].x and y = set[k].y
			//If the next point does not have the same sign as the previous point, this line segment
			//is discarded and we move to the next iteration of loop 2.
			
			bool isLeft = false;	// If the point being compared is left of point i
			bool isRight = false;	// or right of point j, then i-j isn't part of the convex hull
			bool isHull = true;
			for(int k = 0; k < size; k++){
				if((k != i) && (k != j)) { // Skip an iteration if the comparison involves one of the segment endpoints
					
					float val = (a * set[k].getx()) + (b * set[k].gety()) - c;	//Calculating the formula
					
					//Now check whether the value is above, below, or on the line
					if(val > 0) isLeft = true;
					else if(val < 0) isRight = true;
					else {
						if((set[k].getx() < set[i].getx()) || (set[k].getx() > set[j].getx())) {
							isHull = false;
							break;
						}
					}
				
				}
				
				if(isLeft && isRight) {	//if point k is between point i and j, ij isn't part of the hull
					isHull = false;
					break;
				}
				
			}
			
			
			//If we reach here, the line segment must be part of the convex hull, so add it to the set
			if(isHull) {
				//cout << "answer_index = " << answer_index << "; answer_index + 1 = " << answer_index+1 << "answer_index + 2 = " << answer_index+2 << endl;
				if(!inSet(set[j], convexhull, size)) { convexhull[answer_index++] = set[j]; }
				if(!inSet(set[i], convexhull, size)) { convexhull[answer_index++] = set[i]; }
			}
			
			
		}
		
		
	}
	
	return convexhull;
}

float findSide(cdpoint::cdpoint p1, cdpoint::cdpoint p2, cdpoint::cdpoint p3){
	// x1y2 + x3y1 + x2y3 - x3y2 - x2y1 - x1y3
	return (p1.getx() * p2.gety()) + (p3.getx() * p1.gety()) - (p3.getx() * p2.gety()) - (p2.getx() * p1.gety()) - (p1.getx() * p3.gety());
}

void findHull(cdpoint::cdpoint *subset, int size, cdpoint::cdpoint p1, cdpoint::cdpoint p2, list<cdpoint::cdpoint>& convexhull) {
	if(size == 0) { return; }
	
	//Find the furthest point from p1<->p2 in subset
	//Can calculate the distance of the point from the line using the
	//findSide() function
	cdpoint::cdpoint furthestPoint;
	
	int maxVal = 0;	//keep track of the largest distance
	bool pointFound = false;
	for(int i = 0; i < size; i++){
		if(findSide(p1, p2, subset[i]) > maxVal) {
			pointFound = true;
			maxVal = findSide(p1, p2, subset[i]);
			furthestPoint = subset[i];
		}
	}	
	
	//Add furthest point to convexhull between p1/p2
	if(pointFound) convexhull.push_back(furthestPoint);
	
	//Divide remaining points in subset into left and right categories
	cdpoint::cdpoint s1[size-1];
	cdpoint::cdpoint s2[size-1];
	
	int inds1 = 0, inds2 = 0;
	for(int i = 0; i < size - 1; i++){
		if(findSide(p1, p2, subset[i]) > 0) { s1[inds1++] = subset[i]; }
		else if(findSide(p1, p2, subset[i]) < 0) { s2[inds2++] = subset[i]; }
	}	
	
	
	//Move on to the next subsets
	findHull(s1, inds1, p1, furthestPoint, convexhull);
	findHull(s2, inds2, furthestPoint, p2, convexhull);
}

list<cdpoint::cdpoint>& quickhullCH(cdpoint::cdpoint *set, int size, list<cdpoint::cdpoint>& convexhull){
	sort(set, size);
	
	cdpoint::cdpoint leftpoint = set[0]; 
	cdpoint::cdpoint rightpoint = set[size-1]; 
	
	convexhull.push_back(leftpoint);
	convexhull.push_back(rightpoint);
	
	//divide remaining points into those above and below the line
	cdpoint::cdpoint s1[size-1];
	cdpoint::cdpoint s2[size-1];
	
	int inds1 = 0, inds2 = 0;
	for(int i = 0; i < size - 1; i++){
		if(findSide(leftpoint, rightpoint, set[i]) > 0) { 
			s1[inds1++] = set[i]; 
			}
		else if(findSide(leftpoint, rightpoint, set[i]) < 0) { 
			s2[inds2++] = set[i]; 
			}
	}
	
	findHull(s1, inds1, leftpoint, rightpoint, convexhull);
	findHull(s2, inds2, rightpoint, leftpoint, convexhull);
	
	return convexhull;
	
	
}

int main(int argc, char **argv)
{
	 //Input set
	 int size = 7;
	 cdpoint::cdpoint set[size] = {{-1,6},{-5,3},{-3,-2},{0,0},{-1,3},{4,-1},{2,5}};
	 
	 //Print input set
	 cout << "Input set: ";
	 for(int i = 0; i < size; i ++) { cout << set[i] << " "; }
	 cout << endl << endl;
	 
	 //Output set for Brute Force
	 cdpoint::cdpoint BFconvexhull[7];
	 
	 //Output set for QuickHull
	 list<cdpoint::cdpoint> QHconvexhull;
	 
	 //Compute the convex hull using the brute force algorithm
	 bruteForceCH(set, size, BFconvexhull);
	 
	 //Print the brute force output
	 cout << "Processing set...\n" << "	Results of brute force: ";
	 for(int i = 0; i < size; i ++) { if(BFconvexhull[i].getx() > -1000) cout << BFconvexhull[i] << " "; }
	 cout << endl << endl; 
	 
	 //Compute the convex hull using the quickhull algorithm
	 quickhullCH(set, size, QHconvexhull);
	 
	 cout << "Processing set...\n" << "	Results of quickhull: ";
	 list<cdpoint::cdpoint>::iterator it;
	 for(it = QHconvexhull.begin(); it != QHconvexhull.end(); ++it){
		 cout << " " << *it;
	 }
	 cout << endl << endl; 

	 
}





