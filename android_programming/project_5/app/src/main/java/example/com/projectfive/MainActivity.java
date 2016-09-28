package example.com.projectfive;

import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;


public class MainActivity extends ActionBarActivity {
    private Integer broadcastsSent;
    public boolean keepTrack, sendNotifs;
    private final String filename = "int_store";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        broadcastsSent = 0;
        setContentView(R.layout.activity_main);
        checkPreferences();
        try {
            File f = new File(filename);
            if(!f.exists()){
                broadcastsSent = 0;
                FileOutputStream fos = openFileOutput(filename, Context.MODE_PRIVATE);
                ObjectOutputStream oos = new ObjectOutputStream(fos);
                oos.writeObject(broadcastsSent);
                oos.close();
            }
            FileInputStream fis = openFileInput(filename);
            ObjectInputStream ois = new ObjectInputStream(fis);
            broadcastsSent = (Integer)ois.readObject();
            ois.close();
        } catch (Exception ignored){

        }
    }

    @Override
    public void onResume(){
        super.onResume();
        checkPreferences();
    }

    private void checkPreferences(){
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);
        keepTrack = sp.getBoolean("enable_custom_broadcast",false);
        sendNotifs = sp.getBoolean("enable_notify",false);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()){
            case R.id.action_settings:
                Intent in = new Intent(this,SettingsActivity.class);
                try {
                    FileInputStream fis = openFileInput(filename);
                    ObjectInputStream ois = new ObjectInputStream(fis);
                    broadcastsSent = (Integer)ois.readObject();
                    ois.close();
                } catch (Exception ignored){}
                in.putExtra("COUNT",broadcastsSent);
                startActivity(in);
                break;
            default:
                break;
        }
        return super.onOptionsItemSelected(item);
    }



    public void onSendClick(View v){
        Log.e("BRDCST","Broadcast clicked");
        if(keepTrack){
            Intent in = new Intent("com.example.br1.MYACTION");
            sendBroadcast(in);
            Log.e("BRDCST","Broadcast sent");
        } else {
            Log.e("BRDCST","Broadcast not sent");
            Toast.makeText(this,"Broadcasts are not enabled",Toast.LENGTH_SHORT).show();
        }
    }

    public void onResetClick(View v){
        try {
            broadcastsSent = 0;
            FileOutputStream fos = openFileOutput(filename,Context.MODE_PRIVATE);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(broadcastsSent);
            oos.close();
            Toast.makeText(this,"Count Reset",Toast.LENGTH_SHORT).show();
        } catch (Exception ignored){}
    }
}
