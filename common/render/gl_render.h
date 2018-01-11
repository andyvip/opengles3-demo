//
// Created by andy on 07/01/2018.
//

#ifndef CUBE_ANDROID_OPENGLDEMO_GLRENDER_H
#define CUBE_ANDROID_OPENGLDEMO_GLRENDER_H

#include "gl_render_utils.h"

namespace glrender {

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

}

#endif //CUBE_ANDROID_OPENGLDEMO_GLRENDER_H
