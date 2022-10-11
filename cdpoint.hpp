#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
using namespace std;

namespace point
{

class Point
{
private:
	int x;
	int y;
public:
	Point(int x, int y);
	~Point();
	
	friend bool operator >(const Point& p1, const Point& p2);
	friend bool operator <(const Point& p1, const Point& p2);
	friend bool operator ==(const Point& p1, const Point& p2);
	friend ostream& operator << (ostream& out, const Point& source);

};

}
 
#endif // POINT_HPP
