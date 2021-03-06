//
// Created by andy on 07/01/2018.
//

#include "gl_render.h"
#include "gl_render_utils.h"
#include "gl_render_factory.h"

namespace gl_render {
    class TriangleRender : public GLRender {
        
    private:
        GLuint program_;
        
    public:
        virtual ~TriangleRender() {
            glDeleteProgram(program_);
        }
        
        virtual bool Init() {
            GLRender::Init();

            const char vertext_shader[] =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 a_position;   \n"
            "layout(location = 1) in vec4 a_color;      \n"
            "out vec4 v_color;                          \n"
            "void main()                                \n"
            "{                                          \n"
            "    v_color = a_color;                     \n"
            "    gl_Position = a_position;              \n"
            "}";
            
            
            const char frag_shader[] =
            "#version 300 es            \n"
            "precision mediump float;   \n"
            "in vec4 v_color;           \n"
            "out vec4 o_fragColor;      \n"
            "void main()                \n"
            "{                          \n"
            "    o_fragColor = v_color; \n"
            "}";
            
            program_ = CreateProgram(vertext_shader, frag_shader);
            if (!program_)
                return false;
            
            glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
            return true;
        }
        
        virtual void Resize(int w, int h) {
            GLRender::Resize(w, h);
        }
        
        virtual void Render() {
            static const GLfloat vertex_postion[] = {
                1.0, -1.0, 0,
                -1.0, -1.0, 0,
                0, 1.0, 0
            };
            
            static const GLfloat vertex_color[] = {1.0f, 0.0f, 0.0f, 1.0f};
            
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(program_);
            
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertex_postion);
            glVertexAttrib4fv(1, vertex_color);
            
            glViewport(0, 0, GLRender::width_ / 2, GLRender::height_ / 2);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            glViewport(GLRender::width_ / 2, GLRender::height_ / 2, GLRender::width_ / 2,
                       GLRender::height_ / 2);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        
    };
    
    GLRenderFactoryCreator(TriangleRender);
}
