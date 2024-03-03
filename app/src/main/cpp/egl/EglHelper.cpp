//
// Created by ByteDance on 3/2/24.
//

#include "EglHelper.h"

EglHelper::EglHelper() : mEGLDisplay(EGL_NO_DISPLAY),
                        mEGLSurface(EGL_NO_SURFACE),
                        mEGLContext(EGL_NO_CONTEXT) {}

EglHelper::~EglHelper() {
    // release resources
}

int EglHelper::initEGL(EGLNativeWindowType window) {
    // 1. get default display
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        LOGE("EGL get display error");
        return EGL_ERROR;
    }

    // 2. initialize display
    std::shared_ptr<EGLint> version(new EGLint[2]);
    if (!eglInitialize(mEGLDisplay, version.get(), version.get()+1)) {
        LOGE("EGL init display error");
        return EGL_ERROR;
    }

    // 3. display configuration
    const EGLint attributeList[] = {EGL_RED_SIZE, 8,
                                    EGL_GREEN_SIZE, 8,
                                    EGL_BLUE_SIZE, 8,
                                    EGL_ALPHA_SIZE, 8,
                                    EGL_DEPTH_SIZE, 8,
                                    EGL_STENCIL_SIZE, 8,
                                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
                                    EGL_NONE};
    EGLint numConfig;
    if (!eglChooseConfig(mEGLDisplay, attributeList, NULL, 1, &numConfig)) {
        LOGE("EGL choose config error");
        return EGL_ERROR;
    }
    EGLConfig eglConfig;
    if (!eglChooseConfig(mEGLDisplay, attributeList, &eglConfig, numConfig, &numConfig)) {
        LOGE("EGL choose config error");
        return EGL_ERROR;
    }

    // 4. create context
    const EGLint attributeContext[] = {EGL_CONTEXT_CLIENT_VERSION, 3,
                                       EGL_NONE};
    mEGLContext = eglCreateContext(mEGLDisplay, eglConfig, NULL, attributeContext);
    if (mEGLContext == EGL_NO_CONTEXT) {
        LOGE("EGL create context error");
        return EGL_ERROR;
    }

    // 5. create surface
    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, eglConfig, window, NULL);
    if (mEGLSurface == EGL_NO_SURFACE) {
        LOGE("EGL create surface error");
        return EGL_ERROR;
    }

    // 6. build connection between egl context and rendering surface
    if (!eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
        LOGE("EGL make current error");
        return EGL_ERROR;
    }

    return EGL_OK;
}

int EglHelper::swapBuffers() {
    if (mEGLDisplay != EGL_NO_DISPLAY &&
        mEGLSurface != EGL_NO_SURFACE &&
        eglSwapBuffers(mEGLDisplay, mEGLSurface)) {
        return EGL_OK;
    }
    return EGL_ERROR;
}

void EglHelper::destroyEGL() {
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        // unbind
        eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (mEGLSurface != EGL_NO_SURFACE) {
            eglDestroySurface(mEGLDisplay, mEGLSurface);
            mEGLSurface = EGL_NO_SURFACE;
        }
        if (mEGLDisplay != EGL_NO_DISPLAY) {
            eglDestroyContext(mEGLDisplay, mEGLContext);
            mEGLContext = EGL_NO_CONTEXT;
        }
        if (mEGLDisplay != EGL_NO_DISPLAY) {
            eglTerminate(mEGLDisplay);
            mEGLDisplay = EGL_NO_DISPLAY;
        }
    }
}