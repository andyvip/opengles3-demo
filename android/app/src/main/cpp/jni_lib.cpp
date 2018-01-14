#include <vector>
#include <string>
#include <jni.h>
#include <gl_render.h>

#define LOG_TAG "jni_lib"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#else
#define ALOGD(...)
#endif

extern "C" {
JNIEXPORT void JNICALL Java_example_andy_openglesdemo_GLJNILib_init(JNIEnv *env, jobject obj, jint type);
JNIEXPORT void JNICALL
Java_example_andy_openglesdemo_GLJNILib_resize(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_example_andy_openglesdemo_GLJNILib_render(JNIEnv *env, jobject obj);
};

using namespace gl_render;
static GLRender *kRenderer = NULL;

JNIEXPORT void JNICALL
Java_example_andy_openglesdemo_GLJNILib_init(JNIEnv *env, jobject obj, jint type) {
    if (kRenderer) {
        delete kRenderer;
        kRenderer = NULL;
    }

    std::vector<std::string> *name_vec = GetAllRenderExampleName();
    kRenderer = CreateRenderExample((*name_vec)[type]);
    if (kRenderer == NULL) {
        ALOGD("Java_example_andy_cube_GLJNILib_init fail");
    }
    delete name_vec;
}

JNIEXPORT void JNICALL
Java_example_andy_openglesdemo_GLJNILib_resize(JNIEnv *env, jobject obj, jint width, jint height) {
    if (kRenderer == NULL) {
        return;
    }
    kRenderer->Resize(width, height);
}

JNIEXPORT void JNICALL
Java_example_andy_openglesdemo_GLJNILib_render(JNIEnv *env, jobject obj) {
    if (kRenderer == NULL) {
        return;
    }
    kRenderer->Render();
}


