//
// Created by andy on 08/01/2018.
//

//
// Created by andy on 07/01/2018.
//

#include "gl_render.h"

namespace glrender {

static const char kVertexShader[] =
    "#version 300 es                            \n"
        "layout(location = 0) in vec4 a_position;   \n"
        "layout(location = 1) in vec4 a_color;      \n"
        "out vec4 v_color;                          \n"
        "void main()                                \n"
        "{                                          \n"
        "    v_color = a_color;                     \n"
        "    gl_Position = a_position;              \n"
        "}";


static const char kFragShader[] =
    "#version 300 es            \n"
        "precision mediump float;   \n"
        "in vec4 v_color;           \n"
        "out vec4 o_fragColor;      \n"
        "void main()                \n"
        "{                          \n"
        "    o_fragColor = v_color; \n"
        "}";


class CubeRender :public GLRender {
public:
    virtual ~CubeRender();

    virtual bool Init();

    virtual void Resize(int w, int h);

    virtual void Render();

private:
    GLuint program_;
};

bool CubeRender::Init() {
    GLRender::Init();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    program_ = CreateProgram(kVertexShader, kFragShader);
    if (!program_)
        return false;

    return true;
}

void CubeRender::Resize(int w, int h) {
    GLRender::Resize(w, h);
    //glViewport(0, 0, w/2, h/2);

}

void CubeRender::Render() {
    GLfloat color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat vertex_postion[] = {
        1.0, -1.0, 0,
        -1.0, -1.0, 0,
        0, 1.0, 0
    };

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program_);

    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vertex_postion);
    glEnableVertexAttribArray (0);
    glVertexAttrib4fv (1, color);

    glViewport(0, 0, GLRender::width_/2, GLRender::height_/2);
    glDrawArrays (GL_TRIANGLES, 0, 3);

    glViewport(GLRender::width_/2, GLRender::height_/2, GLRender::width_/2,GLRender::height_/2);
    glDrawArrays (GL_TRIANGLES, 0, 3);

}

CubeRender::~CubeRender(){
    glDeleteProgram(program_);
}

GLRender *CreateCubeRender() {
    CubeRender *cube_render = new CubeRender;
    if (!cube_render->Init()) {
        delete cube_render;
        return NULL;
    }
    return cube_render;
}
}
