#ifndef GLES3JNI_TEXTURE_H
#define GLES3JNI_TEXTURE_H

#include <GLES3/gl3.h>

class Texture {
public:
	Texture(const char *filePath);
	virtual ~Texture();

	GLuint getHandle() { return handle; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	//int getChannels() { return channels; }

private:
	GLuint handle;
	int width, height, channels;
};

#endif //GLES3JNI_TEXTURE_H
