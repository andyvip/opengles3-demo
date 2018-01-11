//
//  triangle_render_mapbuffer.cpp
//  OpenGLESDemo
//
//  Created by andy on 11/01/2018.
//  Copyright © 2018 andy. All rights reserved.
//



#include "gl_render.h"
#include <string.h>

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
    
    class TriangleRenderMapBuffer : public GLRender {
    public:
        virtual ~TriangleRenderMapBuffer();
        
        virtual bool Init();
        
        virtual void Resize(int w, int h);
        
        virtual void Render();
        
    private:
        GLuint program_;
        GLuint vao_ids[1];
    };
    
    bool TriangleRenderMapBuffer::Init() {
        GLRender::Init();
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        program_ = CreateProgram(kVertexShader, kFragShader);
        if (!program_)
            return false;
        
        GLfloat vertices[] =
        {
            //x, y, z, r, g, b, a
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };
        
        GLushort indices[] = {0, 1, 2};
        
        GLfloat *vtx_mapped_buf;
        GLushort *inc_mapped_buf;

        GLuint vbo_ids[2] = {0};
        
        glGenBuffers(2, vbo_ids);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        vtx_mapped_buf = (GLfloat *)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertices), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        memcpy(vtx_mapped_buf, vertices, sizeof(vertices));
        glUnmapBuffer(GL_ARRAY_BUFFER);
        
        inc_mapped_buf = (GLushort *)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        memcpy(inc_mapped_buf, indices, sizeof(indices));
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

        glGenVertexArrays(1, vao_ids);
        glBindVertexArray(vao_ids[0]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), 0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (const void *)(3*sizeof(GLfloat)));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[1]);
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        return true;
    }
    
    void TriangleRenderMapBuffer::Resize(int w, int h) {
        GLRender::Resize(w, h);
        glViewport(0, 0, w, h);
    }
    
    void TriangleRenderMapBuffer::Render() {
        
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program_);
        
        glBindVertexArray(vao_ids[0]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }
    
    TriangleRenderMapBuffer::~TriangleRenderMapBuffer() {
        glDeleteProgram(program_);
    }
    
    GLRender *CreateTriangleRenderMapBuffer() {
        TriangleRenderMapBuffer *render = new TriangleRenderMapBuffer;
        if (!render->Init()) {
            delete render;
            return NULL;
        }
        return render;
    }
    
}



