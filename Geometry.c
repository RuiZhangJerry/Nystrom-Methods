#include "Geometry.h"

Vector ManifoldGeometry::mapping(Vector ref){
	Vector x(1);
	x[0]=0.5*ref[0] + 0.5;
	return x;
}

double ManifoldGeometry::arcLength(Vector ref){
	return 0.5;
}


