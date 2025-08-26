package com.example.esp_car.DIYView;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.MotionEvent;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.widget.AppCompatSeekBar;

public class SeekBarVertical extends AppCompatSeekBar {
    public SeekBarVertical(@NonNull Context context) {
        super(context);
    }

    public SeekBarVertical(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public SeekBarVertical(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh)
    {
        super.onSizeChanged(h, w, oldh, oldw);
    }

    @Override
    protected synchronized void onMeasure(int w,
                                          int h)
    {
        super.onMeasure(h, w);
        setMeasuredDimension(getMeasuredHeight(), getMeasuredWidth());
    }

    @Override
    protected synchronized void onDraw(Canvas canvas)
    {
        canvas.rotate(-90);
        canvas.translate(-getHeight(), 0);
        super.onDraw(canvas);
    }

    @SuppressLint("ClickableViewAccessibility")
    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        if (!isEnabled())
        {
            return false;
        }

        switch (event.getAction())
        {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_MOVE:
                int i=0;
                //获取滑动的距离
                i=getMax() - (int) (getMax() * event.getY() / getHeight());
                //设置进度
                setProgress(i);
                //每次拖动SeekBar都会调用
                onSizeChanged(getWidth(), getHeight(), 0, 0);
                break;
            case MotionEvent.ACTION_UP:
                System.out.println("ACTION_UP");
                //设置进度
                setProgress(10);
                //每次拖动SeekBar都会调用
                onSizeChanged(getWidth(), getHeight(), 0, 0);
                break;
            case MotionEvent.ACTION_CANCEL:
                System.out.println("ACTION_CANCEL");
                break;
        }
        return true;
    }
}
