#include "Common.h"

float floatMod(float x, float m) {
	float r = fmod(x, m);
	return r < 0 ? r + m : r;
}

int mod(int x, int m){
	int r = x % m;
	return r < 0 ? r + m : r;
}
