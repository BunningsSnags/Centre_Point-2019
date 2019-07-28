#include "Common.h"

float floatMod(float x, float m) {
	float r = fmod(x, m);
	return r < 0 ? r + m : r;
}