package com.example.egldemo.opengl;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

/**
 * Created by joe.chu on 3/2/24
 *
 * @author joe.chu@bytedance.com
 */
public class NativeGLSurfaceView extends SurfaceView implements SurfaceHolder.Callback {

    private NativeOpenGL mNativeOpenGL;

    public NativeGLSurfaceView(Context context) {
        this(context, null);
    }

    public NativeGLSurfaceView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public NativeGLSurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        mNativeOpenGL = new NativeOpenGL();
        getHolder().addCallback(this);
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder surfaceHolder) {
        mNativeOpenGL.nativeSurfaceCreate(surfaceHolder.getSurface());
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder surfaceHolder, int format, int width, int height) {
        mNativeOpenGL.nativeSurfaceChanged(width, height);
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder surfaceHolder) {
        mNativeOpenGL.nativeSurfaceDestroyed();
    }
}
