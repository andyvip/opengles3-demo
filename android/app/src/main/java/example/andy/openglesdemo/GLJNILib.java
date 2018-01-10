package example.andy.openglesdemo;

/**
 * Created by andy on 07/01/2018.
 */

public class GLJNILib {
    static {
        System.loadLibrary("render");
    }

    public static native void init(int type);

    public static native void resize(int w, int h);

    public static native void render();
}
