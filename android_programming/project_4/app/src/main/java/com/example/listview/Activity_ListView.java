package com.example.listview;

import android.app.ActionBar;
import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.graphics.drawable.ColorDrawable;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Spinner;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;


public class Activity_ListView extends ListActivity {
    private final String TETON = "http://www.tetonsoftware.com/bikes/";
    private final String CNU = "http://www.pcs.cnu.edu/~kperkins/bikes/";
    private List<BDBuilder.BikeData> bikes;
    OnSharedPreferenceChangeListener listener;
    private CustomAdapter adapter;
    private SharedPreferences myPreference;
    private boolean prefChangedFlag = false;
    private boolean rotateFlag;
    private String prefURL;
    private int sortBy;
    private ArrayAdapter<CharSequence> adapterL;
    private Spinner spinner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        bikes = new ArrayList<BDBuilder.BikeData>();
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);
        boolean isTeton = sp.getBoolean("teton",false);
        prefURL = (isTeton) ? TETON + "bikes.json" : CNU + "bikes.json";
        adapter = new CustomAdapter(this, R.layout.listview_row_layout, bikes, prefURL);
        if (!prefChangedFlag)
            new DLJSONTask().execute(prefURL);
        setListAdapter(adapter);
        myPreference = PreferenceManager.getDefaultSharedPreferences(this);
        listener = new SharedPreferences.OnSharedPreferenceChangeListener() {
            public void onSharedPreferenceChanged(SharedPreferences prefs, String key) {
                bikes.clear();
                adapter.notifyDataSetChanged();
                prefChangedFlag = true;
            }
        };
        myPreference.registerOnSharedPreferenceChangeListener(listener);
        getListView().setOnScrollListener(new AbsListView.OnScrollListener() {
            @Override
            public void onScrollStateChanged(AbsListView view, int scrollState) {
                if (scrollState != AbsListView.OnScrollListener.SCROLL_STATE_FLING){
                    adapter.setFling(false);
                    adapter.notifyDataSetChanged();
                } else {
                    adapter.setFling(true);
                    adapter.notifyDataSetChanged();
                }
            }

            @Override
            public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {

            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        spinner = (Spinner) menu.findItem(R.id.spinner).getActionView();
        adapterL = ArrayAdapter.createFromResource(this,R.array.spinner_choices,
                android.R.layout.simple_spinner_dropdown_item);
        adapterL.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapterL);
        spinner.setPopupBackgroundDrawable(new ColorDrawable(getResources().getColor(R.color.ForestGreen)));
        spinner.setOnItemSelectedListener(new OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if(!rotateFlag) {
                    sortBy = position;
                    adapter.sortList(sortBy);
                }
                rotateFlag = false;
                spinner.setSelection(sortBy);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                spinner.setSelection(sortBy);
            }
        });
        return true;
    }

    @Override
    public void onSaveInstanceState(Bundle icicle){
        super.onSaveInstanceState(icicle);
        icicle.putInt("SORT_VAL",sortBy);
        icicle.putBoolean("HAS_PREF_CHANGE",prefChangedFlag);
    }

    @Override
    public void onRestoreInstanceState(Bundle icicle){
        super.onRestoreInstanceState(icicle);
        sortBy = icicle.getInt("SORT_VAL");
        prefChangedFlag = icicle.getBoolean("HAS_PREF_CHANGED");
        rotateFlag = true;
    }

    @Override
    public void onResume(){
        super.onResume();
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);
        boolean isTeton = sp.getBoolean("teton",false);
        prefURL = (isTeton) ? TETON + "bikes.json" : CNU + "bikes.json";
        bikes.clear();
        adapter.notifyDataSetChanged();
        if(prefChangedFlag)
            new DLJSONTask().execute(prefURL);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_settings:
                Intent myIntent = new Intent(this, activityPreference.class);
                startActivity(myIntent);
                break;
            case R.id.action_about:
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setMessage("An app about bikes\nBy Steven Rosendahl")
                    .setTitle("About")
                    .setPositiveButton("Dismiss", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                        }
                    });
                AlertDialog dialog = builder.create();
                dialog.show();
                break;
            default:
                break;
        }
        return true;
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        super.onListItemClick(l, v, position, id);
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(bikes.get(position).toString())
            .setPositiveButton("Close",new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.dismiss();
                }
            })
            .setTitle(bikes.get(position).getData().get("Model"));
        AlertDialog dialog = builder.create();
        dialog.show();
    }

    class DLJSONTask extends AsyncTask<String,Void,List<BDBuilder.BikeData>>{

        @Override
        public void onPreExecute(){
            bikes.clear();
            adapter.notifyDataSetChanged();
        }

        @Override
        public List<BDBuilder.BikeData> doInBackground(String... args){
            String url = args[0];
            return getJSONFromURL(url);
        }

        @Override
        public void onPostExecute(List<BDBuilder.BikeData> data){
            if(data != null){
                for(BDBuilder.BikeData bk : data){
                    if(!bikes.contains(bk)) {
                        bikes.add(bk);
                    }
                }
                adapter.notifyDataSetChanged();
                adapter.sortList(sortBy);
            }

        }

        private List<BDBuilder.BikeData> getJSONFromURL(String url){
            InputStream in;
            List<BDBuilder.BikeData> ret;
            try {
                DefaultHttpClient client = new DefaultHttpClient();
                HttpPost poster = new HttpPost(url);
                HttpResponse responder = client.execute(poster);
                HttpEntity entity = responder.getEntity();
                in = entity.getContent();
                BufferedReader reader = new BufferedReader(new InputStreamReader(in));
                String line;
                String res = "";
                while((line = reader.readLine()) != null){
                    res += line;
                }
                in.close();
                JSONObject obj = new JSONObject(res);
                JSONArray jArray = obj.getJSONArray("Bikes");
                ret = new ArrayList<BDBuilder.BikeData>();
                for(int i = 0; i < jArray.length(); i++){
                    JSONObject temp = jArray.getJSONObject(i);
                    BDBuilder bd = new BDBuilder()
                        .comp(temp.getString("Company"))
                        .model(temp.getString("Model"))
                        .location(temp.getString("Location"))
                        .price(temp.getDouble("Price"))
                        .date(temp.getString("Date"))
                        .description(temp.getString("Description"))
                        .picture(temp.getString("Picture"))
                        .link(temp.getString("Link"));
                    ret.add(bd.build());
                }
            } catch (Exception e){
                return null;
            }
            return ret;
        }
    }
}
