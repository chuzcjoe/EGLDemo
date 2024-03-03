//
// Created by ByteDance on 3/2/24.
//

#include "EglThread.h"

EglThread::EglThread() {

}

EglThread::~EglThread() {
    if (mEglThread.joinable()) {
        mEglThread.join();
    }
}

void EglThread::eglThreadImpl(EglThread* eglThread) {
    LOGD("Enter Thread Impl");
    if (!eglThread) {
        LOGE("thread is null");
        return;
    }
    std::unique_ptr<EglHelper> eglHelper(new EglHelper());
    if (eglHelper->initEGL(eglThread->mANativeWindow) == EGL_ERROR) {
        LOGE("eglHelper initEgl error");
        return;
    }

    eglThread->isExit = false;
    LOGD("Enter Rendering");
    while (!eglThread->isExit) {
        LOGD("Rendering");
        if (eglThread->isCreate) {
            eglThread->isCreate = false;
            eglThread->_onCreate();
        }

        if (eglThread->isChange) {
            eglThread->isChange = false;
            eglThread->isStart = true;
            eglThread->_onChange(eglThread->surfaceWidth, eglThread->surfaceHeight);
        }

        if (eglThread->isStart) {
            eglThread->_onDraw();
            eglHelper->swapBuffers();

            if (eglThread->mRenderType == RENDER_MODULE_AUTO) {
                usleep(1000000 / 60);
            } else {
                std::unique_lock<std::mutex> lock(eglThread->mut);
                LOGD("rendering waiting");
                eglThread->cond.wait(lock);
                LOGD("rendering restart");
            }
        }
    }

    eglHelper->destroyEGL();
}

void EglThread::onSurfaceCreate(EGLNativeWindowType window) {
    if (!mEglThread.joinable()) {
        isCreate = true;
        mANativeWindow = window;
        mEglThread = std::thread([this]{ eglThreadImpl(this);});
    }
}

void EglThread::onSurfaceChange(int width, int height) {
    if (mEglThread.joinable()) {
        surfaceWidth = width;
        surfaceHeight = height;
        isChange = true;
        notifyRender();
    }
}

void EglThread::setRenderType(int renderType) {
    mRenderType = renderType;
    notifyRender();
}

void EglThread::notifyRender() {
    std::lock_guard<std::mutex> lock(mut);
    cond.notify_one();
}

void EglThread::callBackOnCreate(EglThread::OnCreate onCreateFunc) {
    this->_onCreate = onCreateFunc;
}

void EglThread::callBackOnChange(EglThread::OnChange onChangeFunc) {
    this->_onChange = onChangeFunc;
}

void EglThread::callBackOnDraw(EglThread::OnDraw onDrawFunc) {
    this->_onDraw = onDrawFunc;
}