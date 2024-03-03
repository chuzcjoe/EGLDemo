package com.example.egldemo.opengl;

import android.view.Surface;

/**
 * Created by joe.chu on 3/2/24
 *
 * @author joe.chu@bytedance.com
 */
public class NativeOpenGL {
    static {
        System.loadLibrary("egldemo");
    }

    public native void nativeSurfaceCreate(Surface surface);
    public native void nativeSurfaceChanged(int width, int height);
    public native void nativeSurfaceDestroyed();
}
