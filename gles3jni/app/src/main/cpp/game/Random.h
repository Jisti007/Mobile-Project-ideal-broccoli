#ifndef GLES3JNI_RANDOM_H
#define GLES3JNI_RANDOM_H

#include <cstdlib>

class Random {
public:
	static float generateFloat() { return rand() / static_cast<float>(RAND_MAX); }
};

#endif //GLES3JNI_RANDOM_H
