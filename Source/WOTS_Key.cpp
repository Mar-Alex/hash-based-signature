#include "WOTS_Key.h"

WOTS_Key::WOTS_Key(int w, int m){
	this->w = w;
	this->numberOfIterations = (1 << w) - 1;
	double mw = (double) m / w;
	this->t1 = (mw > (int)mw) ? mw + 1 : mw;
	this->t2 = log2(t1 * numberOfIterations) / w + 1;
	this->t = t1 + t2;
	key.resize(t);
}
