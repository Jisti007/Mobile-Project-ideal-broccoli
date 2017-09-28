#ifndef GLES3JNI_PIPELINE_H
#define GLES3JNI_PIPELINE_H

#include <GLES3/gl3.h>

class Pipeline {
public:
    Pipeline();
    ~Pipeline();

    void initialize();
    void destroy();
    inline GLuint getProgram() { return program; }

private:
    GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;

    GLuint createShader(const char* source, GLenum type);
};

#endif //GLES3JNI_PIPELINE_H
