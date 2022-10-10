#include "Point.hpp"
#include <iostream>

using namespace std;

namespace point {

Point::Point(int xx, int yy) {
		x = xx;
		y = yy;
}

Point::~Point(){
}
	
bool operator >(const Point& p1, const Point& p2) { 
	if(p1.x > p2.x) { return true; } 
	else if(p1.x == p2.x) { return(p1.y > p2.y); }
	else return false;
}
bool operator <(const Point& p1, const Point& p2) { 
	return !(p1 > p2);	// reuses code from the above overload
}
bool operator ==(const Point& p1, const Point& p2) { 
	return((p1.x == p2.x) && (p1.y == p2.y));
}
ostream& operator << (ostream& outs, const Point& source){
	outs << "(" << source.x << "," << source.y << ")";
}


}
