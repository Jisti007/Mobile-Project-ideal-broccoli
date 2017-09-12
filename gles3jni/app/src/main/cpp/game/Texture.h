#ifndef GLES3JNI_TEXTURE_H
#define GLES3JNI_TEXTURE_H

#include <GLES3/gl3.h>

class Texture {
public:
    Texture(char* filePath);
    virtual ~Texture();

    GLuint getHandle() { return handle;}

private:
    GLuint handle;
    int Width, Height, Channels;
};

#endif //GLES3JNI_TEXTURE_H
