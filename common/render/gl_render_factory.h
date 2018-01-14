//
//  gl_render_factory.h
//  OpenGLESDemo
//
//  Created by andy on 14/01/2018.
//  Copyright © 2018 andy. All rights reserved.
//

#include <string>
#include <vector>

#ifndef gl_render_factory_h
#define gl_render_factory_h

#define GLRenderFactoryCreator(name) \
class GLRenderFactory##name : public GLRenderFactory { \
public: \
    virtual GLRender *NewInstance() { \
        return new name(); \
    } \
}; \
__attribute__((constructor)) void RegisterFactory##name() { \
    GLRenderFactory::RegisterFactory(#name, new GLRenderFactory##name()); \
}; \

namespace gl_render {
    
class GLRender;
class GLRenderFactory {
public:
    virtual GLRender *NewInstance() = 0;

    static GLRender *NewInstanceByName(std::string name);
    static GLRenderFactory* GetFactory(std::string name);
    static void RegisterFactory(std::string name, GLRenderFactory *factory);
    static std::vector<std::string>* GetAllRenderNames();
};

}
#endif /* gl_render_factory_h */
