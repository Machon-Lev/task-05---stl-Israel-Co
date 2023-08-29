#pragma once
#include <string>
#include <iostream>

class Coordinate {
public:
	double x;
	double y;

	std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, const Coordinate& city);
};