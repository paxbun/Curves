package com.freiyer.curves;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    ImageView imageView;
    Paint paint;
    Paint paint2;
    Canvas canvas;
    Bitmap bitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        imageView = findViewById(R.id.imageView);

        paint = new Paint(Paint.ANTI_ALIAS_FLAG);
        paint.setAntiAlias(true);
        paint.setColor(Color.BLACK);
        paint.setStyle(Paint.Style.STROKE);
        paint.setStrokeJoin(Paint.Join.ROUND);
        paint.setStrokeWidth(4f);

        paint2 = new Paint(Paint.ANTI_ALIAS_FLAG);
        paint2.setAntiAlias(true);
        paint2.setColor(Color.RED);
        paint2.setStyle(Paint.Style.STROKE);
        paint2.setStrokeJoin(Paint.Join.ROUND);
        paint2.setStrokeWidth(5f);

        canvas = new Canvas();
    }

    public void onClick(View v) {
        bitmap = Bitmap.createBitmap(
                imageView.getMeasuredWidth(),
                imageView.getMeasuredHeight(),
                Bitmap.Config.ARGB_8888
        );
        canvas.setBitmap(bitmap);
        imageView.setImageBitmap(bitmap);

        float[] curve;
        float[] pivots;

        long st = System.nanoTime();
        String log;
        if(v.getId() == R.id.cppButton) {
            log = "C++: ";
            pivots = new float[]{200, 800, 700, 800, 700, 600};
            curve = getBezierCurve(pivots);
        }
        else {
            log = "Java: ";
            pivots = new float[]{1000, 200, 700, 600, 400, 800};
            curve = getJavaBezierCurve(pivots);
        }
        long res = System.nanoTime() - st;

        log += Long.toString(res) + " ns";
        Log.d("Curves", log);
        Toast.makeText(this, log, Toast.LENGTH_SHORT).show();

        for(int i = 0; i < 20000; i += 2)
            canvas.drawLine(
                    curve[i], curve[i+1], curve[i+2], curve[i+3],
                    paint
            );

        for(int i = 0; i < 6; i+= 2)
            canvas.drawCircle(pivots[i], pivots[i+1],10f, paint2);
    }

    public native float[] getBezierCurve(float[] beg_mid_end_6);
    public native float[] getCubicHermiteCurve(float[] beg_end_begt_endt_8);

    public float[] getCurvePoint(float[] bezierCurve, float t)
    {
        if(bezierCurve.length < 6)
            return null;

        float[] res = new float[2];

        res[0]
                = (1 - t) * (1 - t) * bezierCurve[0]
                  + 2 * t * (1 - t) * bezierCurve[2]
                  + t * t           * bezierCurve[4]
                ;

        res[1]
                = (1 - t) * (1 - t) * bezierCurve[1]
                  + 2 * t * (1 - t) * bezierCurve[3]
                  + t * t           * bezierCurve[5]
                ;

        return res;
    }

    public float[] getJavaBezierCurve(float[] beg_mid_end_6)
    {
        float[] copy = new float[6];
        for(int i = 0; i < 6 && i < beg_mid_end_6.length; i++)
            copy[i] = beg_mid_end_6[i];
        for(int i = beg_mid_end_6.length; i < 6; i++)
            copy[i] = 0;

        float[] rtn = new float[20002];

        for(int i = 0; i <= 10000; i++) {
            float[] pos = getCurvePoint(beg_mid_end_6, i / 10000.f);
            rtn[2*i] = pos[0];
            rtn[2*i+1] = pos[1];
        }

        return rtn;
    }
}
