//
//  gl_render_utils.h
//  OpenGLESDemo
//
//  Created by andy on 12/01/2018.
//  Copyright © 2018 andy. All rights reserved.
//

#ifndef gl_render_utils_h
#define gl_render_utils_h

#include <stdio.h>

#ifdef __ANDROID__
#include <android/log.h>
#include <GLES3/gl3.h>
#endif

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#endif

#define GLRender_LOG(...) LogPrint(__VA_ARGS__)

namespace gl_render {
    typedef struct {
        GLfloat   m[4][4];
    } Matrix;
        
    void LogPrint(const char *fmt, ...);
    void Translate(Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
    void Rotate(Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    void MatrixLoadIdentity(Matrix *result);
    void Perspective(Matrix *result, float fovy, float aspect, float nearZ, float farZ);
    void MatrixMultiply(Matrix *result, Matrix *srcA, Matrix *srcB);
    GLuint CreateProgram(const char *vtxSrc, const char *fragSrc);
}

#endif /* gl_render_utils_h */
