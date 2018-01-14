//
//  gl_render_factory.cpp
//  OpenGLESDemo
//
//  Created by andy on 14/01/2018.
//  Copyright © 2018 andy. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <map>
#include "gl_render_factory.h"

using namespace std;
namespace gl_render {
    
    map<string, GLRenderFactory*>* ObjectFactoryMap() {
        static map<string, GLRenderFactory*> *factory_map_ = new map<string, GLRenderFactory*>();
        return factory_map_;
    }
    
    void GLRenderFactory::RegisterFactory(string name, GLRenderFactory *factory) {
        map<string, GLRenderFactory*> *factory_map = ObjectFactoryMap();
        factory_map->insert(make_pair(name, factory));
    }
    
    GLRenderFactory* GLRenderFactory::GetFactory(string name) {
        map<string, GLRenderFactory*> *factory_map = ObjectFactoryMap();
        if (factory_map->find(name) != factory_map->end()) {
            return (*factory_map)[name];
        }
        return NULL;
    }
    
    GLRender* GLRenderFactory::NewInstanceByName(std::string name) {
        GLRenderFactory *factory = GLRenderFactory::GetFactory(name);
        if (factory != NULL) {
            return factory->NewInstance();
        }
        return NULL;
    }
    
    vector<string>* GLRenderFactory::GetAllRenderNames() {
        vector<string> *names = new vector<string>();
        map<string, GLRenderFactory*> *factory_map = ObjectFactoryMap();
        map<string, GLRenderFactory*>::iterator iter = factory_map->begin();
        while (iter != factory_map->end()) {
            names->push_back(iter->first);
            iter++;
        }
        return names;
    }
}
