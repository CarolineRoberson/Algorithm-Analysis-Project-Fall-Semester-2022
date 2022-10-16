#include "cdpoint.hpp"
#include <iostream>
#include <list>


namespace cdpoint {
	
cdpoint::cdpoint() { } //default constructor

cdpoint::cdpoint(float xx, float yy) {
		x = xx;
		y = yy;
}

cdpoint::~cdpoint(){
}
	
bool operator >(const cdpoint& p1, const cdpoint& p2) { 
	if(p1.x > p2.x) { return true; } 
	else if(p1.x == p2.x) { return(p1.y > p2.y); }
	else return false;
}
bool operator <(const cdpoint& p1, const cdpoint& p2) { 
	return !(p1 > p2);	// reuses code from the above overload
}
bool operator ==(const cdpoint& p1, const cdpoint& p2) { 
	return((p1.x == p2.x) && (p1.y == p2.y));
}
bool operator !=(const cdpoint& p1, const cdpoint& p2) { 
	return((p1.x != p2.x) || (p1.y != p2.y));
}
bool operator !=(const std::list<cdpoint>::iterator& p1, const cdpoint& p2) { 
	return((p1->x != p2.x) || (p1->y != p2.y));
}
std::ostream& operator << (std::ostream& outs, const cdpoint& source){
	outs << "(" << source.x << "," << source.y << ")";
	return outs;
}


}
