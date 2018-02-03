#pragma once

#include <stdarg.h>
#include <vector>
#include "Location.h"
#include <stdio.h>

class Path {
private:
	unsigned int index;
	std::vector<Location> path;
public:
	Path();
	Path(Location point1);
	Path(Location point1, Location point2);
	Path(Location point1, Location point2, Location point3);
	Location& getNext();
	void next();
	bool hasNext();
};
