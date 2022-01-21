package com.sh.registernatives;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

//参考：https://www.jianshu.com/p/0121f591a261
public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI2());
//        Log.d(TAG, "onCreate: "+stringFromJNI2());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String stringFromJNI2(); // 一个静态注册的函数，如果没有被使用 定制rom就不会输出日志 ,动态函数没有使用会被输出日志 TODO
    public native int sum(int num1,int num2);
}