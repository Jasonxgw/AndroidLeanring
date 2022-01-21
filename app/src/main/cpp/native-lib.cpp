#include <jni.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#define JNIREG_CLASS "com/sh/registernatives/MainActivity"//指定要注册的类

extern "C" JNIEXPORT jstring JNICALL
Java_com_sh_registernatives_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


jstring call(JNIEnv* env, jobject thiz)
{
    return env->NewStringUTF("动态注册JNI,居然可以把头文件删掉也不会影响结果，牛逼不咯");
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_sh_registernatives_MainActivity_sum(JNIEnv* env, jobject clazz,jint num1,jint num2){
    return num1+num2;
}
/**
* 方法对应表
*/
static JNINativeMethod gMethods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void*)call},
        {"sum", "(II)I", (void*)Java_com_sh_registernatives_MainActivity_sum},
};

/*
* 为某一个类注册本地方法
*/
static int registerNativeMethods(JNIEnv* env
        , const char* className
        , JNINativeMethod* gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}


/*
* 为所有类注册本地方法
*/
static int registerNatives(JNIEnv* env) {
    return registerNativeMethods(env, JNIREG_CLASS, gMethods,
                                 sizeof(gMethods) / sizeof(gMethods[0]));
}

/*
* System.loadLibrary("lib")时调用
* 如果成功返回JNI版本, 失败返回-1
*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);

    if (!registerNatives(env)) { //注册
        return -1;
    }
    //成功
    result = JNI_VERSION_1_4;

    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sh_registernatives_MainActivity_stringFromJNI2(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromJNI2()
    return env->NewStringUTF("2123");
}