package rosendahl.steven.com.jsonderulo;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.text.Html;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SubMenu;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;


public class MainActivity extends ActionBarActivity {
    private Map<String,String> jsonfiles;
    private ImageView view;
    private boolean isLoaded;
    private String template = "http://www.tetonsoftware.com/pets/";
    private String currLoaded;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jsonfiles = new LinkedHashMap<>();
        view = (ImageView)findViewById(R.id.image_view);
        currLoaded = "default";
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);
        boolean isCNU = sp.getBoolean("dl_from_pcse",false);
        boolean isSupSec = sp.getBoolean("dl_from_supsec",false);
        if(isCNU)
            template = "http://www.pcs.cnu.edu/~kperkins/pets/";
        else if(isSupSec)
            template = "http://bsnewline.tumblr.com/mobile_test/";
        else
            template = "http://www.tetonsoftware.com/pets/";
        if (isNetworkAvailable()) {
            new InitJSONTask().execute(template + "pets.json");
        } else {
             Toast.makeText(this, "No Network Connection :(", Toast.LENGTH_SHORT).show();
        }
        if(savedInstanceState == null){
            view.setImageResource(R.drawable.montanas);
        }
        if(savedInstanceState != null){
            currLoaded = (String)savedInstanceState.get("LOADED_IMAGE");
            if(currLoaded.equals("default")){
                view.setImageResource(R.drawable.montanas);
            }
            else {
                for (int i = 0; i < 10; i++) {
                    if (currLoaded.contains("" + i)) {
                        new LoadPictureTask().execute(currLoaded);
                        break;
                    }
                }
            }
        }
    }

    @Override
    public void onResume(){
        super.onResume();
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);
        boolean isCNU = sp.getBoolean("dl_from_pcse",false);
        boolean isSupSec = sp.getBoolean("dl_from_supsec",false);
        if(isCNU)
            template = "http://www.pcs.cnu.edu/~kperkins/pets/";
        else if(isSupSec)
            template = "http://bsnewline.tumblr.com/mobile_test/";
        else
            template = "http://www.tetonsoftware.com/pets/";
        if (isNetworkAvailable()) {
            new InitJSONTask().execute(template + "pets.json");
        } else {
            Toast.makeText(this, "No Network Connection :(", Toast.LENGTH_SHORT).show();
            invalidateOptionsMenu();
        }
    }

    @Override
    public void onSaveInstanceState(Bundle saveMe){
        saveMe.putCharSequence("LOADED_IMAGE",currLoaded);
        super.onSaveInstanceState(saveMe);
    }

    private boolean isNetworkAvailable() {
        ConnectivityManager connectivityManager
                = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
        return activeNetworkInfo != null && activeNetworkInfo.isConnected();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        final Set<String> picNamesSet = jsonfiles.keySet();
        final List<String> picNames = new ArrayList<>(picNamesSet);
        final Collection<String> picUrlsCollec = jsonfiles.values();
        final List<String> picUrls = new ArrayList<>(picUrlsCollec);
        MenuItem topLevel = menu.findItem(R.id.action_pics);
        SubMenu sub = topLevel.getSubMenu();
        if(isLoaded) {
            for (String s : picNames) {
                sub.add(s).setOnMenuItemClickListener(new MenuItem.OnMenuItemClickListener() {
                    @Override
                    public boolean onMenuItemClick(MenuItem item) {
                        for(int i = 0; i < picNames.size(); i++){
                            if(item.getTitle().toString().equals(picNames.get(i)))
                                new LoadPictureTask().execute(picUrls.get(i));
                        }
                        return true;
                    }
                });
            }
        }
        else {
            sub.clear();
        }
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        switch(id){
            case R.id.action_settings:
                startActivity(new Intent(this,SettingsActivity.class));
                break;
            case R.id.action_about:
                createAboutDialog();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    private void createAboutDialog(){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setPositiveButton("Dismiss",new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        });
        builder.setMessage("JSON Derulo\nCreated by Steven Rosendahl\n");
        AlertDialog dialog = builder.create();
        dialog.show();
    }

    class LoadPictureTask extends AsyncTask<String,Void,Bitmap>{
        private String templateCpy;
        private String carryOver;
        ProgressDialog pd;
        @Override
        protected void onPreExecute(){
            pd = new ProgressDialog(MainActivity.this,ProgressDialog.STYLE_SPINNER);
            pd.setMessage("Loading image...");
            if(isNetworkAvailable())
                pd.show();
            templateCpy = template;
        }

        @Override
        protected Bitmap doInBackground(String... args){
            carryOver = args[0];
            templateCpy += args[0];
            try{
                InputStream in = (InputStream)new URL(templateCpy).getContent();
                Bitmap map = BitmapFactory.decodeStream(in);
                in.close();
                return map;
            } catch (Exception e){
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap result){
            currLoaded = carryOver;
            view.setImageBitmap(result);
            pd.dismiss();
        }
    }

    class InitJSONTask extends AsyncTask<String,Void,Boolean> {
        private String json;
        private String url;
        private Map<String,String> localMap;

        @Override
        protected void onPreExecute(){
            localMap = new LinkedHashMap<>();
        }

        @Override
        public Boolean doInBackground(String... urls){
            url = urls[0];
            try {
                JSONObject obj = getJSONFromURL(urls[0]);
                if(obj == null)
                    return false;
                JSONArray array = obj.getJSONArray("pets");
                for(int i = 0; i < array.length(); i++){
                    JSONObject temp = array.getJSONObject(i);
                    String name = temp.getString("name");
                    String filename = temp.getString("file");
                    localMap.put(name,filename);
                }
            } catch (Exception e) {
                return false;
            }
            return true;
        }

        @Override
        protected void onPostExecute(Boolean res){
            if(res) {
                jsonfiles = new LinkedHashMap<>(localMap);
                isLoaded = true;
            }
            else {
                Toast.makeText(MainActivity.this,
                        "Failed to load from " + url, Toast.LENGTH_SHORT).show();
                isLoaded = false;
                view.setImageResource(R.drawable.montanas);
            }
            invalidateOptionsMenu();
        }

        private JSONObject getJSONFromURL(String url){
            InputStream in;
            JSONObject ret;
            try {
                DefaultHttpClient client = new DefaultHttpClient();
                HttpPost poster = new HttpPost(url);
                HttpResponse responder = client.execute(poster);
                HttpEntity entity = responder.getEntity();
                in = entity.getContent();
                BufferedReader reader = new BufferedReader(new InputStreamReader(in, "iso-8859-1"),8);
                StringBuilder builder = new StringBuilder();
                String line;
                while((line = reader.readLine()) != null){
                    builder.append(line + "\n");
                }
                in.close();
                json = builder.toString();
                ret = new JSONObject(json);
            } catch (Exception e){
                return null;
            }
            return ret;
        }
    }
}
