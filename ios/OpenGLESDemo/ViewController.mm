//
//  ViewController.m
//  OpenGLESDemo
//
//  Created by andy on 10/01/2018.
//  Copyright © 2018 andy. All rights reserved.
//

#import "ViewController.h"
#include "../../common/render/gl_render.h"

@interface ViewController ()
{
    gl_render::GLRender *_render;
    CGFloat _dpi;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    EAGLContext *context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    GLKView *view = (GLKView *)[self view];
    [view setContext:context];
    [view setDrawableDepthFormat:GLKViewDrawableDepthFormat24];
    [EAGLContext setCurrentContext:context];
    
    _dpi = [[UIScreen mainScreen] scale];
    _render = gl_render::CreateRenderExample("TextureSimpleRender");
    if(_render != NULL) {
        _render->Init();
    }
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
    
    [EAGLContext setCurrentContext:nil];
    delete _render;
    _render = nil;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if(_render != NULL) {
        _render->Resize(rect.size.width*_dpi, rect.size.height*_dpi);
    }
}

- (void)update {
    if(_render != NULL) {
        _render->Render();
    }
}

@end

