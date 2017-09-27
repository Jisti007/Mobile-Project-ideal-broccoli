#ifndef GLES3JNI_TEXTURE_H
#define GLES3JNI_TEXTURE_H

#include <GLES3/gl3.h>

class Texture {
public:
	Texture(const char *filePath);
	virtual ~Texture();

	inline const GLuint getHandle() const { return handle; }
	inline const int getWidth() const { return width; }
	inline const int getHeight() const { return height; }
	//inline int getChannels() const { return channels; }

private:
	GLuint handle;
	int width, height, channels;
};

#endif //GLES3JNI_TEXTURE_H
