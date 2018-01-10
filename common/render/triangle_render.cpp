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

class TriangleRender :public GLRender {
public:
    virtual ~TriangleRender();

    virtual bool Init();

    virtual void Resize(int w, int h);

    virtual void Render();

private:
    GLuint program_;
};

bool TriangleRender::Init() {
    GLRender::Init();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    program_ = CreateProgram(kVertexShader, kFragShader);
    if (!program_)
        return false;

    return true;
}

void TriangleRender::Resize(int w, int h) {
    GLRender::Resize(w, h);
}

void TriangleRender::Render() {
    static const GLfloat vertex_postion[] = {
        1.0, -1.0, 0,
        -1.0, -1.0, 0,
        0, 1.0, 0
    };
    
    static const GLfloat vertex_color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program_);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vertex_postion);
    glVertexAttrib4fv (1, vertex_color);

    glViewport(0, 0, GLRender::width_/2, GLRender::height_/2);
    glDrawArrays (GL_TRIANGLES, 0, 3);

    glViewport(GLRender::width_/2, GLRender::height_/2, GLRender::width_/2,GLRender::height_/2);
    glDrawArrays (GL_TRIANGLES, 0, 3);
}

TriangleRender::~TriangleRender(){
    glDeleteProgram(program_);
}

GLRender *CreateTriangleRender() {
    TriangleRender *render = new TriangleRender;
    if (!render->Init()) {
        delete render;
        return NULL;
    }
    return render;
}
}
