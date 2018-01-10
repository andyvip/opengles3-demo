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

    class TriangleRenderVAO :public GLRender {
    public:
        virtual ~TriangleRenderVAO();

        virtual bool Init();

        virtual void Resize(int w, int h);

        virtual void Render();

    private:
        GLuint program_;
        GLuint vao_ids[1];
    };

    bool TriangleRenderVAO::Init() {
        GLRender::Init();
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        program_ = CreateProgram(kVertexShader, kFragShader);
        if (!program_)
            return false;

        GLfloat vertex_postion[] =
            {
                0.0f,  0.5f, 0.0f,        // v0
                -0.5f, -0.5f, 0.0f,        // v1
                0.5f, -0.5f, 0.0f         // v2
            };
        GLfloat vertex_color[] =
            {
                1.0f, 0.0f, 0.0f, 1.0f,   // c0
                0.0f, 1.0f, 0.0f, 1.0f,   // c1
                0.0f, 0.0f, 1.0f, 1.0f    // c2
            };

        GLushort indices[] = { 0, 1, 2 };

        GLuint vbo_ids[3] = {0};
        glGenBuffers(3, vbo_ids);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_postion), vertex_postion, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_color), vertex_color, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenVertexArrays(1, vao_ids);
        glBindVertexArray(vao_ids[0]);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
        glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[2]);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return true;
    }

    void TriangleRenderVAO::Resize(int w, int h) {
        GLRender::Resize(w, h);
        glViewport(0, 0, w, h);
    }

    void TriangleRenderVAO::Render() {

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program_);

        glBindVertexArray(vao_ids[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    TriangleRenderVAO::~TriangleRenderVAO(){
        glDeleteProgram(program_);
    }

    GLRender *CreateTriangleRenderVAO() {
        TriangleRenderVAO *render = new TriangleRenderVAO;
        if (!render->Init()) {
            delete render;
            return NULL;
        }
        return render;
    }
}
