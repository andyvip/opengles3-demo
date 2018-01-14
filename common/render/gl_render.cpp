//
// Created by andy on 07/01/2018.
//

#include <vector>
#include <string>
#include "gl_render.h"
#include "gl_render_utils.h"
#include "gl_render_factory.h"

namespace gl_render {

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
    
    GLRender* CreateRenderExample(std::string name) {
        return GLRenderFactory::NewInstanceByName(name);
    }
    
    std::vector<std::string>* GetAllRenderExampleName() {
        return GLRenderFactory::GetAllRenderNames();
    }
    
}
