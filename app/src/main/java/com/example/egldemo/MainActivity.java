package com.example.egldemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.egldemo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'egldemo' library on application startup.
    static {
        System.loadLibrary("egldemo");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /**
     * A native method that is implemented by the 'egldemo' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}