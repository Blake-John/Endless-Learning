#include "mathfunc.h"
#include <cmath>

double getDistance (int x1, int y1, int x2, int y2)
{
	return std::sqrt (std::pow ((x1 - x2), 2) + std::pow ((y1 - y2), 2));
}
