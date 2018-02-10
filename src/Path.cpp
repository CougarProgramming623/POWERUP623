#include "Path.h"

Path::Path() :
		index(0) {

}
Path::Path(Location point1) :
		index(0) {
	path.push_back(point1);
}
Path::Path(Location point1, Location point2) :
		index(0) {
	path.push_back(point1);
	path.push_back(point2);
}
Path::Path(Location point1, Location point2, Location point3) :
		index(0) {
	path.push_back(point1);
	path.push_back(point2);
	path.push_back(point3);
}

Location& Path::getNext() {
	return path[index];
}

void Path::next() {
	index++;
}

bool Path::hasNext() {
	return index < path.size();
}

