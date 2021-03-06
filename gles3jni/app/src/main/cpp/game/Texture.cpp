#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture(const char* id, int width, int height, int channels) {
	this->id = id;
	this->width = width;
	this->height = height;
	this->channels = channels;
}

/*
Texture::Texture(const char* id, unsigned char* pixels, int width, int height, int channels) :
	Texture(id, width, height, channels)
{
	this->pixels = pixels;
	reload();
	//initialize(pixels);
}
*/

Texture::Texture(const char* id, const char* filePath) {
	this->id = id;
	//this->filePath = filePath;

	auto pixels = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
	setPixels(pixels);
	stbi_image_free(pixels);
	reload();
	//initialize();
}

Texture::~Texture() {
}

/*
void Texture::initialize() {
	pixels = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	initialize(pixels);
}

void Texture::initialize(unsigned char* pixels) {
	GLenum format;
	switch (channels) {
		case 1:
			format = GL_RED;
			break;
		default:
			format = GL_RGBA;
			break;
	}

	glGenTextures(1, &handle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
*/
void Texture::setPixels(unsigned char* pixels) {
	this->pixels = std::vector<unsigned char>(pixels, pixels + width * height * channels);
}

void Texture::reload() {
	glGenTextures(1, &handle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy() {
	if (handle && glIsTexture(handle)) {
		glDeleteTextures(1, &handle);
		handle = 0;
	}
}
