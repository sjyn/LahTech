package example.com.projectfive;

import android.app.IntentService;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.v4.app.NotificationCompat;
import android.util.Log;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class MyService extends IntentService {
    private String defMessage;
    private boolean sendNotifs;
    private Integer broadcastsSent;

    public MyService(){
        super("MyService");
    }

    @Override
    public void onHandleIntent(Intent intent){
        Log.e("SERVICE","Service Started");
        checkPreferences();
        try {
            FileInputStream fis = openFileInput("int_store");
            ObjectInputStream ois = new ObjectInputStream(fis);
            broadcastsSent = (Integer)ois.readObject();
            ois.close();
            broadcastsSent++;
            FileOutputStream fos = openFileOutput("int_store", Context.MODE_PRIVATE);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(broadcastsSent);
            oos.close();
        } catch (Exception ignored){
            Log.e("SERVICE",ignored.getMessage());
        }
        if(sendNotifs){
            Log.e("SERVICE","Notification Sent");
            sendNotification();
        }
    }

    private void sendNotification(){
        NotificationCompat.Builder builder =
                new NotificationCompat.Builder(this).
                        setContentText("You have received "+ broadcastsSent +
                                ((broadcastsSent > 1) ? " notifications" : " notification")).
                        setContentTitle(defMessage).
                        setSmallIcon(R.drawable.android_icon_2);
        NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        manager.notify(123123,builder.build());

    }

    private void checkPreferences(){
        SharedPreferences sp = PreferenceManager.getDefaultSharedPreferences(this);
        sendNotifs = sp.getBoolean("enable_notify",false);
        defMessage = sp.getString("set_notify_message","");
    }

}
