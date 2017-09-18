#include "GameMap.h"
#include "../../../../../../../../astudio-sdk/ndk-bundle/platforms/android-18/arch-arm/usr/include/GLES3/gl3.h"
#include <jni.h>
#include <stdlib.h>
#include <time.h>
#include <GLES3/gl3.h>


float Hex[] = {
        0.25f, 0.5f,
        -0.25f, 0.5f,
        0.5f, 0.0f,
        0.25f, -0.5f,
        -0.25f, -0.5f,
        -0.5f, 0.0f};

const char* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main(){
        gl_Position = vec4(position, 0.0, 1.0)
    }
)glsl";

const char* fragmentSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main(){
        gl_Position = vec4(position, 0.0, 1.0)
    }
)glsl";

void GameMap::createMap() {

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Hex), Hex, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    //  test if shader works
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);


}

GameMap::GameMap() {
    createMap();
}


//int argc, char *argv[]
