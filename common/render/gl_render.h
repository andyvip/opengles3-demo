//
// Created by andy on 07/01/2018.
//

#ifndef CUBE_ANDROID_OPENGLDEMO_GLRENDER_H
#define CUBE_ANDROID_OPENGLDEMO_GLRENDER_H

#include <stdio.h>

#ifdef __ANDROID__
#include <android/log.h>
#include <GLES3/gl3.h>
#endif

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#endif

#define GLRender_LOG(...) LogPrint(__VA_ARGS__)

namespace glrender {

enum GLRenderType {
    kTriangleRender,
    kTriangleRenderVBO,
    kTriangleRenderEBO,
    kTriangleRenderVAO
};

class GLRender {

public:

    virtual ~GLRender();

    virtual bool Init();

    virtual void Resize(int w, int h);

    virtual void Render();

    GLuint CreateProgram(const char *vtxSrc, const char *fragSrc);

    bool CheckGlError(const char *funcName);

private:
    GLuint CreateShader(GLenum shaderType, const char *src);

public:
    int width_;
    int height_;
};

GLRender *CreateRender(GLRenderType type);
void LogPrint(const char *fmt, ...);

}

#endif //CUBE_ANDROID_OPENGLDEMO_GLRENDER_H
