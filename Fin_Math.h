#ifndef __FIN_MATH__
#define __FIN_MATH__

float fbound(float x, float min, float max) {
	if (x > max) {
		return max;
	}
	if (x < min) {
		return min;
	}
	return x;
};

#endif