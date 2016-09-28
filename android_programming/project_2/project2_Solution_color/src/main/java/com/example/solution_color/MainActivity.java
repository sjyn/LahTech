package com.example.solution_color;


import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Point;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.preference.PreferenceManager;
import android.provider.MediaStore;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.GridLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

import com.library.bitmap_utilities.BitMap_Helpers;

import java.io.File;
import java.io.IOException;
import java.net.URI;

public class MainActivity extends ActionBarActivity  {
    private final int CAMERA_CODE = 360;
    private final int SEND_CODE = 475;
    private final String SAVE_PATH = Environment.getExternalStoragePublicDirectory(
            Environment.DIRECTORY_PICTURES) + "/picture.png";
    private final String SEND_IMAGE_PATH = Environment.getExternalStoragePublicDirectory(
            Environment.DIRECTORY_PICTURES) + "/picture_saved.png";
    private Bitmap picture, sketchedPicture, coloredPicture;
    private ImageView frame;
    private boolean isSketched, isColored;
    private ImageButton cam,col,ske,sha;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        frame = (ImageView) findViewById(R.id.image_view);
        File f = new File(SAVE_PATH);
        if (!f.exists()) {
            try {
                f.createNewFile();
                    //Toast.makeText(this,"New file made",Toast.LENGTH_SHORT).show();
            } catch (Exception ignored) {
                //Toast.makeText(this, "Failed to create file", Toast.LENGTH_SHORT).show();
            }
            picture = BitmapFactory.decodeResource(getResources(), R.drawable.gutters);
        } else {
            picture = Camera_Helpers.loadAndScaleImage(SAVE_PATH, frame.getMaxHeight(), frame.getMaxWidth());
        }
        cam = (ImageButton) findViewById(R.id.camera_button);
        col = (ImageButton) findViewById(R.id.color_button);
        ske = (ImageButton) findViewById(R.id.sketch_button);
        sha = (ImageButton) findViewById(R.id.share_button);
        setButtonWidths(cam,col,ske,sha);
        frame.setImageBitmap(picture);
        isSketched = false;
        isColored = false;
    }

    @Override
    public void onResume(){
        super.onResume();
        File f = new File(SAVE_PATH);
        if(!f.exists())
            picture = BitmapFactory.decodeResource(getResources(), R.drawable.gutters);
        frame.setImageBitmap(picture);
    }

    private void setButtonWidths(ImageButton... buttons){
        Display display = getWindowManager().getDefaultDisplay();
        Point size = new Point();
        display.getSize(size);
        int width = size.x;
        for(ImageButton child : buttons){
            GridLayout.LayoutParams params = (GridLayout.LayoutParams) child.getLayoutParams();
            params.width = (width/4) - params.rightMargin - params.leftMargin;
            child.setLayoutParams(params);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    public void disableButtons(){
        cam.setEnabled(false);
        col.setEnabled(false);
        ske.setEnabled(false);
        sha.setEnabled(false);
    }

    public void enableButtons(){
        cam.setEnabled(true);
        col.setEnabled(true);
        ske.setEnabled(true);
        sha.setEnabled(true);
    }

    public void onCameraClick(View v){
        Intent in = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        in.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(new File(SAVE_PATH)));
        startActivityForResult(in,CAMERA_CODE);
    }

    public void onSketchClick(View v){
        new SketchImageTask().execute(sketchedPicture);
    }

    public void onColorClick(View v){
        new ColorImageTask().execute(coloredPicture,sketchedPicture);
    }

    public void onShareClick(View v){
        Intent send = new Intent();
        send.setAction(Intent.ACTION_SEND);
        send.setType("image/*");
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);
        send.putExtra(Intent.EXTRA_SUBJECT,sp.getString("message_subject",""));
        send.putExtra(Intent.EXTRA_TEXT,sp.getString("message_text",""));
        Bitmap there = BitMap_Helpers.copyBitmap(frame.getDrawable());
        Camera_Helpers.saveProcessedImage(there,SEND_IMAGE_PATH);
        File f = new File(SEND_IMAGE_PATH);
        if(!f.exists()){
            try {
                f.createNewFile();
            }
            catch (IOException ignored){

            }
        }
        Uri imagePath = Uri.fromFile(f);
        send.putExtra(Intent.EXTRA_STREAM,imagePath);
        startActivityForResult(Intent.createChooser(send,"Send..."),SEND_CODE);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data){
        switch(requestCode){
            case CAMERA_CODE:
                switch(resultCode) {
                    case RESULT_OK:
                        picture = Camera_Helpers.loadAndScaleImage(SAVE_PATH, frame.getMaxHeight(), frame.getMaxWidth());
                        frame.setImageBitmap(picture);
                        isSketched = false;
                        isColored = false;
                        break;
                }
                break;
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_settings:
                Intent myIntent = new Intent(this, SettingsActivity.class);
                startActivity(myIntent);
                break;
            case R.id.about:
                Intent in = new Intent(this,AboutActivity.class);
                startActivity(in);
                break;
            default:
                break;
        }
        return true;
    }

    private class SketchImageTask extends AsyncTask<Bitmap,Void,Bitmap> {
        private ProgressDialog pd;
        protected void onPreExecute(){
            disableButtons();
            pd = ProgressDialog.show(MainActivity.this,"Sketching Image",
                    "It takes time to do these things. Math is hard.");
        }

        protected Bitmap doInBackground(Bitmap... bitmaps){
            SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(MainActivity.this);
            final int sketchiness = sp.getInt("sketch_level",50);
            bitmaps[0] = BitMap_Helpers.thresholdBmp(picture, sketchiness);
            isSketched = true;
            return bitmaps[0];
        }

        public void onPostExecute(Bitmap addMe){
            frame.setImageBitmap(addMe);
            sketchedPicture = addMe;
            if(pd.isShowing())
                pd.dismiss();
            enableButtons();
        }
    }

    private class ColorImageTask extends AsyncTask<Bitmap,Void,Bitmap> {
        private ProgressDialog pd;
        protected void onPreExecute(){
            disableButtons();
            pd = ProgressDialog.show(MainActivity.this,"Coloring Image",
                    "It takes a slightly longer time to color these images. " +
                    "This math is even worse than the sketching!");
        }

        protected Bitmap doInBackground(Bitmap... bitmaps){
            SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(MainActivity.this);
            final int colorness = sp.getInt("color_level",50);
            final int sketchiness = sp.getInt("sketch_level",50);
            if(isSketched) {
                bitmaps[0] = BitMap_Helpers.colorBmp(picture, colorness);
            } else {
                bitmaps[1] = BitMap_Helpers.thresholdBmp(picture,sketchiness);
                bitmaps[0] = BitMap_Helpers.colorBmp(picture,colorness);
            }
            BitMap_Helpers.merge(bitmaps[0],bitmaps[1]);
            isColored = true;
            return bitmaps[0];
        }

        public void onPostExecute(Bitmap addMe){
            frame.setImageBitmap(addMe);
            coloredPicture = addMe;
            if(pd.isShowing())
                pd.dismiss();
            enableButtons();
        }
    }

}

