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
    glrender::GLRender *_render;
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
    _render = glrender::CreateRender(glrender::kTriangleRenderVAO);
    _render->Init();
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
    _render->Resize(rect.size.width*_dpi, rect.size.height*_dpi);
}

- (void)update {
    _render->Render();
}

@end

