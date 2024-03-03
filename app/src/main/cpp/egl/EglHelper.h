//
// Created by ByteDance on 3/2/24.
//
#pragma once

#include "EGL/egl.h"
#include "GLLog.h"
#include "result.h"
#include <iostream>

class EglHelper {
public:
    EGLDisplay mEGLDisplay;
    EGLContext mEGLContext;
    EGLSurface mEGLSurface;

public:
    EglHelper();
    ~EglHelper();

    int initEGL(EGLNativeWindowType window);
    int swapBuffers();
    void destroyEGL();
};
