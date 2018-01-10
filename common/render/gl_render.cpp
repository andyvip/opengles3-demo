//
// Created by andy on 07/01/2018.
//

#include "gl_render.h"
#include <stdlib.h>
#include <stdarg.h>

namespace glrender {

bool GLRender::Init() {
    GLRender_LOG("GL_VERSION: %s", glGetString(GL_VERSION));
    GLRender_LOG("GL_VENDOR: %s", glGetString(GL_VENDOR));
    GLRender_LOG("GL_RENDERER: %s", glGetString(GL_RENDERER));
    GLRender_LOG("GL_EXTENSIONS: %s", glGetString(GL_EXTENSIONS));

    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        GLRender_LOG("GL error: 0x%08x\n", err);
        return true;
    }
    return false;
}

void GLRender::Resize(int w, int h) {
    width_ = w;
    height_ = h;
}

void GLRender::Render() {

}

GLRender::~GLRender() {

}

bool GLRender::CheckGlError(const char *funcName) {
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        GLRender_LOG("GL error after %s(): 0x%08x\n", funcName, err);
        return true;
    }
    return false;
}

GLuint GLRender::CreateShader(GLenum shaderType, const char *src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        CheckGlError("glCreateShader");
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);

    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
                GLRender_LOG("Could not compile %s shader:\n%s\n",
                             shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
                             infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint GLRender::CreateProgram(const char *vtxSrc, const char *fragSrc) {
    GLuint vtxShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
    GLint linked = GL_FALSE;

    vtxShader = CreateShader(GL_VERTEX_SHADER, vtxSrc);
    if (!vtxShader)
        goto exit;

    fragShader = CreateShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragShader)
        goto exit;

    program = glCreateProgram();
    if (!program) {
        CheckGlError("glCreateProgram");
        goto exit;
    }
    glAttachShader(program, vtxShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLRender_LOG("Could not link program");
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen) {
            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
                GLRender_LOG("Could not link program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }

    exit:
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);
    return program;
}

extern GLRender *CreateTriangleRender();
extern GLRender *CreateTriangleRenderVBO();
extern GLRender *CreateTriangleRenderEBO();
extern GLRender *CreateTriangleRenderVAO();

GLRender *CreateRender(GLRenderType type) {
    GLRender *render = NULL;
    switch (type) {
        case kTriangleRender:
            render = CreateTriangleRender();
            break;
        case kTriangleRenderVBO:
            render = CreateTriangleRenderVBO();
            break;
        case kTriangleRenderEBO:
            render = CreateTriangleRenderEBO();
            break;
        case kTriangleRenderVAO:
            render = CreateTriangleRenderVAO();
        default:
            break;
    }
    return render;
}

void LogPrint(const char *fmt, ...)
{
    va_list ap;
    char buf[1024];

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

#ifdef __ANDROID__
    __android_log_print (ANDROID_LOG_DEBUG, "GLRender" , "%s", buf);
#else
    printf("%s", buf);
#endif

}
}
