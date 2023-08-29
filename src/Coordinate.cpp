#include "..\include\Coordinate.h"

std::string Coordinate::toString() const
{
	return "Coordinates (x, y): " + std::to_string(x) + ", " + std::to_string(y);
}

std::ostream& operator<<(std::ostream& os, const Coordinate& city)
{
	os << city.toString() << std::endl;
	return os;
}
