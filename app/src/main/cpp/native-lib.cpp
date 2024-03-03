#include "EglThread.h"
#include "GLES3/gl3.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <jni.h>
#include <string>

EglThread* eglThread = nullptr;

void callBackOnCreate() {
    LOGE("callBackOnCreate");
}

void callBackOnChange(int width, int height) {
    glViewport(0, 0, width, height);
    LOGE("callBackChange");
}

void callBackOnDraw() {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    LOGE("callBackOnDraw");
}

extern "C" JNIEXPORT void JNICALL
        Java_com_example_egldemo_opengl_NativeOpenGL_nativeSurfaceCreate(JNIEnv* env, jobject obj, jobject surface) {
    eglThread = new EglThread();
    eglThread->callBackOnCreate(callBackOnCreate);
    eglThread->callBackOnChange(callBackOnChange);
    eglThread->callBackOnDraw(callBackOnDraw);
    eglThread->setRenderType(RENDER_MODULE_MANUAL);

    ANativeWindow* nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread->onSurfaceCreate(nativeWindow);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_egldemo_opengl_NativeOpenGL_nativeSurfaceChanged(JNIEnv* env, jobject obj, jint width, jint height) {
    if (eglThread) {
        eglThread->onSurfaceChange(width, height);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_egldemo_opengl_NativeOpenGL_nativeSurfaceDestroyed(JNIEnv* env, jobject obj) {
    if (eglThread) {
        eglThread->isExit = true;
        eglThread->mEglThread.join();
    }
    delete eglThread;
    eglThread = nullptr;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_egldemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}