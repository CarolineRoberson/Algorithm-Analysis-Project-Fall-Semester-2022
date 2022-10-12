#ifndef CDPOINT_HPP
#define CDPOINT_HPP

#include <iostream>

namespace cdpoint
{

class cdpoint
{
private:
	int x;
	int y;
public:
	cdpoint();
	cdpoint(int x, int y);
	~cdpoint();
	
	const int getx() { return x; }
	const int gety() { return y; }
	
	friend bool operator >(const cdpoint& p1, const cdpoint& p2);
	friend bool operator <(const cdpoint& p1, const cdpoint& p2);
	friend bool operator ==(const cdpoint& p1, const cdpoint& p2);
	friend std::ostream& operator << (std::ostream& out, const cdpoint& source);

};

}

#endif // CDPOINT_HPP
