//
// Created by ByteDance on 3/2/24.
//

#pragma once

#include "EGL/egl.h"
#include "EglHelper.h"
#include "GLLog.h"
#include "GLES2/gl2.h"
#include <android/native_window.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

const int RENDER_MODULE_AUTO = 1;
const int RENDER_MODULE_MANUAL = 2;

class EglThread {
public:
    std::thread mEglThread;
    ANativeWindow *mANativeWindow = nullptr;

    int mRenderType = RENDER_MODULE_MANUAL;

    bool isCreate = false;
    bool isChange = false;
    bool isExit = false;
    bool isStart = false;

    int surfaceWidth = 0;
    int surfaceHeight = 0;


    using OnCreate = void(*)();
    OnCreate _onCreate;

    using OnChange = void(*)(int width, int height);
    OnChange _onChange;

    using OnDraw = void(*)();
    OnDraw _onDraw;


    std::mutex mut;
    std::condition_variable cond;

public:
    EglThread();

    ~EglThread();

    void onSurfaceCreate(EGLNativeWindowType window);
    void onSurfaceChange(int width, int height);

    void setRenderType(int renderType);
    void notifyRender();

    void callBackOnCreate(OnCreate onCreate);
    void callBackOnChange(OnChange onChange);
    void callBackOnDraw(OnDraw onDraw);

private:
    void eglThreadImpl(EglThread* context);
};