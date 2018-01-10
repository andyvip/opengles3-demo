package example.andy.openglesdemo;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends Activity {

    ListView mListView;
    List<ListData> mListData;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initListData();
        mListView = findViewById(R.id.listview);
        mListView.setAdapter(new ArrayAdapter<ListData>(this, android.R.layout.simple_list_item_1, mListData));
        mListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                ListData listData = mListData.get(position);
                Intent intent = new Intent(MainActivity.this, GLActivity.class);
                intent.putExtra("render_type", listData.mRenderType.ordinal());
                startActivity(intent);
            }
        });
    }

    private void initListData() {
        mListData = new ArrayList<ListData>(10);
        mListData.add(new ListData("triangle_render", ListData.RenderType.kTriangleRender));
        mListData.add(new ListData("triangle_render_vbo", ListData.RenderType.kTriangleRenderVBO));
        mListData.add(new ListData("triangle_render_ebo", ListData.RenderType.kTriangleRenderEBO));
        mListData.add(new ListData("triangle_render_vao", ListData.RenderType.kTriangleRenderVAO));
    }

    private static class ListData {
        String mName;
        RenderType mRenderType;

        ListData(String name, RenderType rendertype) {
            mName = name;
            mRenderType = rendertype;
        }

        @Override
        public String toString() {
            return mName;
        }

        public enum RenderType {
            kTriangleRender,
            kTriangleRenderVBO,
            kTriangleRenderEBO,
            kTriangleRenderVAO
        }
    }
}
