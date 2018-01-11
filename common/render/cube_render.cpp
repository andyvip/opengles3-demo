//
// Created by andy on 08/01/2018.
//

//
// Created by andy on 07/01/2018.
//

#include "gl_render.h"

namespace glrender {
    
    static const char kVertexShader[] =
    "#version 300 es                             \n"
    "uniform mat4 u_mvpMatrix;                   \n"
    "layout(location = 0) in vec4 a_position;    \n"
    "layout(location = 1) in vec4 a_color;       \n"
    "out vec4 v_color;                           \n"
    "void main()                                 \n"
    "{                                           \n"
    "   v_color = a_color;                       \n"
    "   gl_Position = u_mvpMatrix * a_position;  \n"
    "}                                           \n";
    
    
    static const char kFragShader[] =
    "#version 300 es            \n"
    "precision mediump float;   \n"
    "in vec4 v_color;           \n"
    "out vec4 o_fragColor;      \n"
    "void main()                \n"
    "{                          \n"
    "    o_fragColor = v_color; \n"
    "}";
    
    
    class CubeRender : public GLRender {
    public:
        virtual ~CubeRender();
        
        virtual bool Init();
        
        virtual void Resize(int w, int h);
        
        virtual void Render();
        
    private:
        GLuint program_;
        GLint mvp_loc;
        ESMatrix  mvp_matrix;

        void UpdateMvpMatrix();
    };
    
    bool CubeRender::Init() {
        GLRender::Init();
        program_ = CreateProgram(kVertexShader, kFragShader);
        if (!program_)
            return false;
        mvp_loc = glGetUniformLocation (program_, "u_mvpMatrix" );
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        return true;
    }
    
    void CubeRender::Resize(int w, int h) {
        GLRender::Resize(w, h);
        glViewport(0, 0, w, h);
    }
    
    void CubeRender::UpdateMvpMatrix() {
        ESMatrix perspective;
        ESMatrix modelview;
        float    aspect;
        GLfloat   angle;
    
        angle = 30.0f;
        aspect = ( GLfloat )width_/ ( GLfloat )height_;
        
        esMatrixLoadIdentity ( &modelview );
        esTranslate ( &modelview, 0.0, 0.0, -5.0 );
        esRotate ( &modelview, 45, 0.0, 1.0, 0.0);
        esRotate ( &modelview, 45, 0.0, 0.0, 1.0 );
        
        esMatrixLoadIdentity ( &perspective );
        esPerspective ( &perspective, 60.0f, aspect, 1.0f, 900.0f );
        esMatrixMultiply (&mvp_matrix, &modelview, &perspective );
    }
    
    void CubeRender::Render() {
        GLfloat vertex_postion[] = {
            -0.5, -0.5, 0.5, //前面左下
            0.5, -0.5, 0.5, //前面右下
            0.5, 0.5, 0.5, //前面右上
            -0.5, 0.5, 0.5, //前面左上
            -0.5, -0.5, -0.5, //后面左下
            0.5, -0.5, -0.5, //后面右下
            0.5, 0.5, -0.5, //后面右上
            -0.5, 0.5, -0.5, //后面左上
        };
        
        GLfloat vertex_color[] =
        {
            1.0f, 0.0f, 0.0f, 1.0f,   // c0
            0.0f, 1.0f, 0.0f, 1.0f,   // c1
            0.0f, 0.0f, 1.0f, 1.0f,   // c2
            1.0f, 0.0f, 0.0f, 1.0f,   // c0
            0.0f, 1.0f, 0.0f, 1.0f,   // c1
            0.0f, 0.0f, 1.0f, 1.0f,   // c2
            1.0f, 0.0f, 0.0f, 1.0f,   // c0
            0.0f, 1.0f, 0.0f, 1.0f,   // c1
        };

        GLushort indices[] = {
            0, 1, 2, 0, 3, 2, //前面
            0, 4, 7, 0, 3, 7, //左面
            0, 2, 5, 0, 4, 5, //底面
            6, 2, 3, 6, 7, 3, //顶面
            6, 5, 4, 6, 7, 4, //后面
            6, 5, 1, 6, 2, 1, //右面
        };
        
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program_);

        GLuint vbo_ids[3] = {0};
        glGenBuffers(3, vbo_ids);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_postion), vertex_postion, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_color), vertex_color, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[2]);
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        UpdateMvpMatrix();
        glUniformMatrix4fv (mvp_loc, 1, GL_FALSE, ( GLfloat * )(&mvp_matrix.m[0][0]));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    
    
    CubeRender::~CubeRender() {
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
