#ifndef CDPOINT_HPP
#define CDPOINT_HPP

#include <iostream>
#include <list>

namespace cdpoint
{

class cdpoint
{
private:
	float x = -1000;
	float y = 1000;
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
	friend bool operator !=(const cdpoint& p1, const cdpoint& p2);
	friend bool operator !=(const std::list<cdpoint>::iterator& p1, const cdpoint& p2);
	friend std::ostream& operator << (std::ostream& out, const cdpoint& source);

};

}

#endif // CDPOINT_HPP
