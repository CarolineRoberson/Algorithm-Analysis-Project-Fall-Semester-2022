#include <stdio.h>
#include <cstdlib>
#include <iostream>
//#include <list>
#include <algorithm>
#include <array>
#include <cmath>
#include "cdpoint.hpp"

using namespace std;
using namespace cdpoint;


cdpoint::cdpoint* fillSet(cdpoint::cdpoint *set, int size){
	
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
	
	for(int i = 0; i < size; i++) {
		
		if(set[i] == coord) return true;
		
	}
	
	return false;
	
}

cdpoint::cdpoint* sort(cdpoint::cdpoint *set, int size) {
	
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

/*
cdpoint::cdpoint* comparePoints(cdpoint::cdpoint *set, int size) {
	cdpoint::cdpoint center = cdpoint(0,0);
	
	sort(set, size);
	
	for(int i = 0; i < size-1; i++){
		cdpoint::cdpoint p1 = set[i];
		dpoint::cdpoint p2 = set[i+1];
		
		float a1 = getAngle(center, p1);
		float a2 = getAngle(center, p2);
		
		if(a1 > a2) {
			//p1 comes before p2
			set[i] = 
		}
	}
}
*/
/*
cdpoint::cdpoint* orderClockwise(cdpoint::cdpoint *set, int size) {
	//Initialize a centerpoint that will be the average center for the set
	// of points
	cdpoint::cdpoint centerpoint = cdpoint(0,0);
	//Calculate the average center of the set
	for(int i = 0; i < size; i++) {
		centerpoint.setx(set[i].getx());
		centerpoint.sety(set[i].gety());
	}
	centerpoint.setx(centerpoint.getx() / size);
	centerpoint.sety(centerpoint.gety() / size);
	
	//Translate all points using the centerpoint to set the center to (0,0)
	for(int i = 0; i < size; i++) {
		set[i].setx(set[i].getx() - centerpoint.getx());
		set[i].sety(set[i].gety() - centerpoint.gety());
	}
	
	//Sort the points in counterclockwise order using the new centerpoint
	set = comparePoints(set, size);
	
	//Translate points back to their original location
	for(int i = 0; i < size; i++){
		set[i].setx(set[i].getx() + centerpoint.getx());
		set[i].sety(set[i].gety() + centerpoint.gety());
	}
	
	return set;
}
*/

/*
cdpoint::cdpoint findCenter(cdpoint::cdpoint *set, int size) {
	//Initialize a centerpoint that will be the average center for the set
	// of points
	cdpoint::cdpoint centerpoint = cdpoint(0,0);
	//Calculate the average center of the set
	for(int i = 0; i < size; i++) {
		centerpoint.setx(set[i].getx());
		centerpoint.sety(set[i].gety());
	}
	centerpoint.setx(centerpoint.getx() / size);
	centerpoint.sety(centerpoint.gety() / size);
	
	return centerpoint;
}

cdpoint::cdpoint* orderClockwise(cdpoint::cdpoint *set, int size) {
	cdpoint::cdpoint center = findCenter(set, size);
	
	
	return set;
}
*/

double getAngle(cdpoint::cdpoint point) {
	return atan2(point.getx(), -point.gety());
}

bool comparePoints(cdpoint::cdpoint p1, cdpoint::cdpoint p2) {
	return getAngle(p1) < getAngle(p2);
}

cdpoint::cdpoint* bruteForceCH(cdpoint::cdpoint *set, int size, cdpoint::cdpoint *convexhull){
	
	int answer_index = 0;
	
	//Choose a point to form the base of the line segment
	for(int i = 0; i < size - 1; i++){
		cout << "i = " << i << endl;
		cout << "EXAMINING STARTING POINT " << set[i] <<  " ----------" << endl;
		
		//Pick the next point to draw the line segment to
		//We always pick 1 entry ahead of i because a segment from i to j is the same as j to i
		for(int j = i+1; j < size; j++){
			
			cout << "j = " << j << endl;
			cout << "	Checking line segment " << set[i] << " to " << set[j] << " ----------" << endl;
			
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
					cout << "k = " << k << endl;
					//cout << "			sign2 = " << sign2 << "; sign1 = " << sign1 << endl;
					
					cout << "			Looking at point " << set[k] << endl;
					
					float val = (a * set[k].getx()) + (b * set[k].gety()) - c;	//Calculating the formula
					cout << "				This point value is " << val << endl;
					
					//Now check whether the value is above, below, or on the line
					if(val > 0) isLeft = true;
					else if(val < 0) isRight = true;
					else {
						if((set[k].getx() < set[i].getx()) || (set[k].getx() > set[j].getx())) {
							isHull = false;
							break;
						}
					}
					
					//if((sign2 != -1) && (sign1 != sign2)) {cout << "				Signs don't match. Breaking." << endl; isLine = false; break;}
					//else {cout << "				Signs match. Moving on." << endl; isLine = true;}
					
					//sign2 = sign1;
				
				
				
				}
				
				if(isLeft && isRight) {	//if point k is between point i and j, ij isn't part of the hull
					isHull = false;
					break;
				}
				
			}
			
			
			//If we reach here, the line segment must be part of the convex hull, so add it to the set
			if(isHull) {
				//cout << "answer_index = " << answer_index << "; answer_index + 1 = " << answer_index+1 << "answer_index + 2 = " << answer_index+2 << endl;
				cout << "Trying to add points " <<  set[i] << "," << set[j] << endl;
				if(!inSet(set[j], convexhull, size)) { cout << "Successfully added point " << set[j] << endl; convexhull[answer_index++] = set[j]; }
				if(!inSet(set[i], convexhull, size)) { cout << "Successfully added point " << set[i] << endl; convexhull[answer_index++] = set[i]; }
				
				for(int i = 0; i < size; i ++) { cout << convexhull[i] << " " << endl; }
	
			}
			
			
		}
		
				
		
		
	}
	
	return convexhull;
}

/*
float findSide(cdpoint::cdpoint p1, cdpoint::cdpoint p2, cdpoint::cdpoint p3){
	// x1y2 + x3y1 + x2y3 - x3y2 - x2y1 - x1y3
	return (p1.getx() * p2.gety()) + (p3.getx() * p1.gety()) - (p3.getx() * p2.gety()) - (p2.getx() * p1.gety()) - (p1.getx() * p3.gety());
}

void findHull(cdpoint::cdpoint *subset, cdpoint::cdpoint p1, cdpoint::cdpoint p2) {
	if(subset.empty()) return;
	
	//Find the furthest point from p1<->p2 in subset
	//Can calculate the distance of the point from the line using the
	//findSide() function
	cdpoint::cdpoint furthestPoint;
	
	int size = sizeof(subset)/sizeof(subset[0]);	//find length of subset array
	int maxVal = 0;	//keep track of the largest distance
	for(int i = 0; i < size - 1; i++){
		if(findSide(p1, p2, subset[i]) > maxVal) {
			maxVal = findSide(p1, p2, subset[i]);
			furthestPoint = subset[i];
		}
	}	
	
	//Add furthest point to convexhull between p1/p2
	
	
	
	//Divide remaining points in subset into left and right categories
	cdpoint::cdpoint s1[size-1];
	cdpoint::cdpoint s2[size-1];
	
	int inds1 = 0, inds2 = 0;
	for(int i = 0; i < size - 1; i++){
		if(findSide(p1, p2, subset[i]) > 0) { s1[inds1++] = subset[i]; }
		else if(findSide(p1, p2, subset[i]) < 0) { s2[inds2++] = subset[i]; }
	}	
	
	
	//Move on to the next subsets
	findHull(s1, p1, furthestPoint);
	findHull(s2, furthestPoint, p2);
}
*/

/*
cdpoint::cdpoint* quickhullCH(cdpoint::cdpoint set, int size, cdpoint::cdpoint *convexhull){
	sort(set, size);
	
	cdpoint::cdpoint leftpoint = set[0];
	cdpoint::cdpoint rightpoint = set[size-1];
	
	convexhull[0] = leftpoint;
	convexhull[1] = rightpoint;
	
	//divide remaining points into those above and below the line
	cdpoint::cdpoint s1[size-1];
	cdpoint::cdpoint s2[size-1];
	
	int inds1 = 0, inds2 = 0;
	for(int i = 0; i < size - 1; i++){
		if(findSide(leftpoint, rightpoint, set[i]) > 0) { s1[inds1++] = set[i]; }
		else if(findSide(leftpoint, rightpoint, set[i]) < 0) { s2[inds2++] = set[i]; }
	}
	
	findHull(s1, leftpoint, rightpoint);
	findHull(s2, rightpoint, leftpoint);
	
	return convexhull;
	
	
}
*/

int main(int argc, char **argv)
{
	
	//Create an array of 10 - 110 randomized points using the point struct
	/*int size = rand() % 100 + 10;
	cdpoint::cdpoint coordSet[size];
	cout << "Created a set of size " << size << endl;
	
	//Create and assign a pointer var to reference the array later on
	cdpoint::cdpoint *setptr;
	setptr = coordSet;
	
	//Fill the array with randomized points
	fillSet(coordSet, size);*/
	
	//Create a set to store the convex hull
	int size = 7;
	cdpoint::cdpoint convexhull[size];
	//Determine the convex hull with the brute force algorithm
	//point *bfsetptr = bruteForceSet;		//Passing the function a pointer to indirectly return a list of points with
	//bruteForceCH(setptr, size, answer);
	
	//Determine the convex hull with the quickhull algorithm
	//list<point> quickhullSet;
	//point *qhsetptr = quickhullSet;			//Passing the function a pointer to indirectly return a list of points with
	//quickhullCH(coordSet, size, quickhullSet);
	 
	 //cout.precision(2);
     //cout.setf(ios::fixed);
	 
	 cdpoint::cdpoint set[size] = {{-5,3},{0,0},{2,5},{-3,-2},{4,-1},{-1,6},{-1,3}};
	 //cdpoint::cdpoint set[size] = {{0.0,0.0},{-8.0,3.0},{5.0,-5.0},{1.0,8.0}};
	 cout<< "Before: " << endl; for(int i = 0; i < size; i ++) { cout << set[i] << " " << endl; }
	 //sort(set, size);
	 //cout<< "After: " << endl; for(int i = 0; i < size; i ++) { cout << set[i] << " " << endl; }
	 //cdpoint::cdpoint convexhull[7];
	 bruteForceCH(set, size, convexhull);
	 
	 cout << "done" << endl;
	 
	 
	 for(int i = 0; i < size; i ++) { cout << convexhull[i] << " " << endl; }
	 
	
	 //sort(begin(convexhull), end(convexhull), comparePoints);

	 
}





