#ifndef GLES3JNI_COMPARABLE_H
#define GLES3JNI_COMPARABLE_H

class Comparable {
public:
	virtual ~Comparable() {};
	virtual int compareTo(Comparable* other) = 0;
};

#endif //GLES3JNI_COMPARABLE_H
