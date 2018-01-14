//
//  texture_simple.cpp
//  OpenGLESDemo
//
//  Created by andy on 14/01/2018.
//  Copyright © 2018 andy. All rights reserved.
//

#include "gl_render.h"
#include "gl_render_utils.h"
#include "gl_render_factory.h"

namespace gl_render {
    class TextureSimpleRender: public GLRender {
    private:
        GLuint program;
        GLint sampler_loc;
        
    public:
        
        virtual ~TextureSimpleRender() {
            glDeleteProgram(program);
        }
        
        virtual bool Init(){
            char vertext_shader[] =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 a_position;   \n"
            "layout(location = 1) in vec2 a_texCoord;   \n"
            "out vec2 v_texCoord;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position = a_position;               \n"
            "   v_texCoord = a_texCoord;                \n"
            "}                                          \n";
            
            char frag_shader[] =
            "#version 300 es                                     \n"
            "precision mediump float;                            \n"
            "in vec2 v_texCoord;                                 \n"
            "layout(location = 0) out vec4 outColor;             \n"
            "uniform sampler2D s_texture;                        \n"
            "void main()                                         \n"
            "{                                                   \n"
            "  outColor = texture( s_texture, v_texCoord );      \n"
            "}                                                   \n";
            
            program = CreateProgram(vertext_shader, frag_shader);
            if (!program) {
                return  false;
            }
            sampler_loc = glGetUniformLocation(program, "s_texture");
            glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

            return true;
        }
        
        virtual void Resize(int w, int h) {
            GLRender::Resize(w, h);
            glViewport(0, 0, w, h);
        }
        
        virtual void Render() {
            GLuint vbo_id[2];
            GLuint texture_id;
            GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
            GLubyte texture_pixel[] = {
                255, 0, 0, //red
                0, 255, 0, //green
                0, 0, 255, //blue
                255, 255, 0 //yellow
            };
            GLfloat verteices[] = {
                //x, y, z, u, v
                -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f,  1.0f,
                0.5f, 0.5f, 0.0f, 1.0f,  0.0f
            };

            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(program);
            glGenBuffers(2, vbo_id);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_id[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verteices), verteices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void *)(3*sizeof(GLfloat)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_pixel);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(sampler_loc, 0);
            
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        }
    };
    GLRenderFactoryCreator(TextureSimpleRender);
}
