#ifndef CDPOINT_HPP
#define CDPOINT_HPP

#include <iostream>

namespace cdpoint
{

class cdpoint
{
private:
	float x;
	float y;
public:
	cdpoint();
	cdpoint(float x, float y);
	~cdpoint();
	
	const float getx() { return x; }
	const float gety() { return y; }
	
	void setx(float xx) { x = xx; }
	void sety(float yy) { y = yy; }
	
	friend bool operator >(const cdpoint& p1, const cdpoint& p2);
	friend bool operator <(const cdpoint& p1, const cdpoint& p2);
	friend bool operator ==(const cdpoint& p1, const cdpoint& p2);
	friend std::ostream& operator << (std::ostream& out, const cdpoint& source);

};

}

#endif // CDPOINT_HPP
