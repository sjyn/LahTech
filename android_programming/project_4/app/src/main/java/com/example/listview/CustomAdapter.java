package com.example.listview;

import java.io.InputStream;
import java.net.URL;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.TimeUnit;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

class CustomAdapter extends ArrayAdapter<BDBuilder.BikeData> {
    private List<BDBuilder.BikeData> data;
    Context context;
    private int sortValue = 0;
    private String url;
    private boolean flinging;

    /**
     * @author lynn
     *         class that holds pointers to all the views in listview_row_layout.xml
     *         you can hold additional data as well, for instance I held a copy of the
     *         the images pictureID (its filename) so that I could match the picture
     *         to the bike when sorting so
     */
    private static class ViewHolder {
        ImageView imageView1;
        TextView Model;
        TextView Price;
        TextView Description;
        String id;
    }

    public CustomAdapter(Context context, int textViewResourceId,
                         List<BDBuilder.BikeData> data, String url) {
        super(context, textViewResourceId, data);
        this.data = data;
        this.context = context;
        this.url = url;
        flinging = false;

    }


    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        if(convertView == null){
            LayoutInflater inflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.listview_row_layout,parent,false);
            ViewHolder vh = new ViewHolder();
            vh.imageView1 = (ImageView)convertView.findViewById(R.id.imageView1);
            vh.Model = (TextView)convertView.findViewById(R.id.Model);
            vh.Price = (TextView)convertView.findViewById(R.id.Price);
            vh.Description = (TextView)convertView.findViewById(R.id.Description);
            vh.id = data.get(position).getData().get("Link");
            convertView.setTag(vh);
        }
        final ViewHolder holder = (ViewHolder)convertView.getTag();
        BDBuilder.BikeData bike = data.get(position);
        holder.Description.setText(bike.getData().get("Description"));
        holder.Price.setText(bike.getData().get("Price"));
        holder.Model.setText(bike.getData().get("Model"));
        String gotoThis = url.replace("bikes.json","");
        holder.id = bike.getData().get("Link");
        //AsyncTask<String,Void,Boolean> task = null;
        if(!flinging && data.get(position).getData().get("Link").equals(holder.id)) {
            convertView.setTag(holder);
            new AsyncTask<String, Void, Boolean>() {
                private Bitmap image;

                @Override
                public void onPreExecute() {

                }

                @Override
                public Boolean doInBackground(String... args) {
                    try {
                        //if(!runner) {
                            InputStream in = (InputStream) new URL(args[0]).getContent();
                            image = BitmapFactory.decodeStream(in);
                        //}
                        //else
                        //    return false;
                    } catch (Exception e) {
                        return false;
                    }
                    return true;
                }

                @Override
                public void onPostExecute(Boolean res) {
                    if (res) {
                        holder.imageView1.setImageBitmap(image);
                    } else {
                        holder.imageView1.setImageResource(R.drawable.inf);
                    }
                }
            }.execute(gotoThis + "/" + data.get(position).getData().get("Picture"));
        }
        return convertView;
    }

    public void setFling(boolean fling){
        this.flinging = fling;
    }

    public void setNewURL(String string) {
        url = string;
    }

    public void sortList(int pos) {
        sortValue = pos;
        for(BDBuilder.BikeData b : data){
            b.setMode(pos);
        }
        Collections.sort(data);
        notifyDataSetChanged();
    }

    public int getSortValue(){
        return sortValue;
    }
}