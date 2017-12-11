#ifndef GLES3JNI_TEXTURE_H
#define GLES3JNI_TEXTURE_H

#include <GLES3/gl3.h>
#include <string>

class Texture {
public:
	Texture(const char* id, int width, int height, int channels);
	Texture(const char* id, unsigned char* pixels, int width, int height, int channels);
	Texture(const char* id, const char *filePath);
	virtual ~Texture();

	void initialize();
	void initialize(unsigned char* pixels);

	inline const GLuint getHandle() const { return handle; }
	inline const int getWidth() const { return width; }
	inline const int getHeight() const { return height; }
	//inline int getChannels() const { return channels; }

private:
	std::string id;
	GLuint handle = 0;
	int width, height, channels;
	std::string filePath;

	void destroy();
};

#endif //GLES3JNI_TEXTURE_H
