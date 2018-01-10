package example.andy.openglesdemo;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLActivity extends Activity {

    public static String LOG_TAG = "GLActivity";

    GLView mView;
    int mRenderType;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mRenderType = getIntent().getIntExtra("render_type", 1);
        mView = new GLView(getApplicationContext());
        setContentView(mView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    public class GLView extends GLSurfaceView {
        public GLView(Context context) {
            super(context);

            setEGLConfigChooser(8, 8, 8, 0, 16, 0);
            setEGLContextClientVersion(3);
            setRenderer(new MyRenderer());
        }

        private class MyRenderer implements GLSurfaceView.Renderer {
            public void onDrawFrame(GL10 gl) {
                //Log.d(LOG_TAG, "onDrawFrame");
                GLJNILib.render();
            }

            public void onSurfaceChanged(GL10 gl, int width, int height) {
                Log.d(LOG_TAG, "onSurfaceChanged:" + "(" + width + "*" + height + ")");
                GLJNILib.resize(width, height);
            }

            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                Log.d(LOG_TAG, "onSurfaceCreated");
                GLJNILib.init(mRenderType);
            }
        }
    }

}
