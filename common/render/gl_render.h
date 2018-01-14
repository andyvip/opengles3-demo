//
// Created by andy on 07/01/2018.
//

#ifndef CUBE_ANDROID_OPENGLDEMO_GLRENDER_H
#define CUBE_ANDROID_OPENGLDEMO_GLRENDER_H
#include <vector>
#include <string>

namespace gl_render {
    
    class GLRender  {
        
    public:
        
        virtual ~GLRender();
        
        virtual bool Init();
        
        virtual void Resize(int w, int h);
        
        virtual void Render();
    
    protected:
        int width_;
        int height_;
    };
    
    GLRender *CreateRenderExample(std::string name);
    std::vector<std::string>* GetAllRenderExampleName();
}

#endif //CUBE_ANDROID_OPENGLDEMO_GLRENDER_H
