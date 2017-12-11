#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

Texture::Texture(int width, int height) {
	this->width = width;
	this->height = height;
}

Texture::Texture(unsigned char* pixels, int width, int height) : Texture(width, height) {
	initialize(pixels);
}

Texture::Texture(const char* id, const char* filePath) {
	this->id = id;
	this->filePath = filePath;

	initialize();
}

Texture::~Texture() {
}

void Texture::destroy() {
	if (handle && glIsTexture(handle)) {
		glDeleteTextures(1, &handle);
		handle = 0;
	}
}

void Texture::initialize() {
	stbi_uc* pixels = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	initialize(pixels);
	stbi_image_free(pixels);
}

void Texture::initialize(unsigned char* pixels) {
	glGenTextures(1, &handle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
