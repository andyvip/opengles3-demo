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

namespace glrender {
    class GLRender;
    
    enum GLRenderType {
        kTriangleRender,
        kTriangleRenderVBO,
        kTriangleRenderEBO,
        kTriangleRenderVAO,
        kTriangleRenderMapBuffer,
        KCubeRender,
    };
    
    typedef struct
    {
        GLfloat   m[4][4];
    } ESMatrix;
    
    GLRender *CreateRender(GLRenderType type);
    
    void LogPrint(const char *fmt, ...);
    void esTranslate ( ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz );
    void esRotate ( ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z );
    void
    esMatrixLoadIdentity ( ESMatrix *result );
    
    
    void
    esMatrixLoadIdentity ( ESMatrix *result );
    void
    esPerspective ( ESMatrix *result, float fovy, float aspect, float nearZ, float farZ );
    void esMatrixMultiply ( ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB );

}

#endif /* gl_render_utils_h */
