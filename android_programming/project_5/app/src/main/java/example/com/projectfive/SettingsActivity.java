package example.com.projectfive;

import android.app.AlertDialog;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.preference.CheckBoxPreference;
import android.preference.EditTextPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;

public class SettingsActivity extends PreferenceActivity {
    protected static Integer brdcsts;

    @Override
    public void onCreate(Bundle bundle){
        super.onCreate(bundle);
        FragmentManager fragMan = getFragmentManager();
        FragmentTransaction fragTrans = fragMan.beginTransaction();
        PreferenceFrag prefs = new PreferenceFrag();
        fragTrans.replace(android.R.id.content,prefs);
        fragTrans.commit();
        Intent received = getIntent();
        Bundle b = received.getExtras();
        brdcsts = b.getInt("COUNT");
    }

    public static class PreferenceFrag extends PreferenceFragment{

        @Override
        public void onCreate(Bundle bundle){
            super.onCreate(bundle);
            addPreferencesFromResource(R.xml.prefs);
            final CheckBoxPreference enable = (CheckBoxPreference)findPreference("enable_custom_broadcast");
            final Preference count = findPreference("total_broads");
            count.setSummary("" + brdcsts);
            final CheckBoxPreference enableNotify = (CheckBoxPreference)findPreference("enable_notify");
            final EditTextPreference notification = (EditTextPreference)findPreference("set_notify_message");
            if(enable.isChecked() & enableNotify.isChecked()){
                count.setEnabled(true);
//                enableNotify.setChecked(false);
                enableNotify.setEnabled(true);
                notification.setEnabled(true);
            } else if(enable.isChecked()){
                count.setEnabled(true);
//                enableNotify.setChecked(false);
                enableNotify.setEnabled(true);
                notification.setEnabled(false);
            } else {
                count.setEnabled(false);
                enableNotify.setChecked(false);
                enableNotify.setEnabled(false);
                notification.setEnabled(false);
            }
            enable.setOnPreferenceClickListener(new Preference.OnPreferenceClickListener() {
                @Override
                public boolean onPreferenceClick(Preference preference) {
                    CheckBoxPreference cbf = (CheckBoxPreference)preference;
                    if(cbf.isChecked()){
                        count.setEnabled(true);
//                      enableNotify.setChecked(false);
                        enableNotify.setEnabled(true);
                        notification.setEnabled(false);
                    } else {
                        count.setEnabled(false);
                        enableNotify.setChecked(false);
                        enableNotify.setEnabled(false);
                        notification.setEnabled(false);
                    }
                    return true;
                }
            });
            enableNotify.setOnPreferenceClickListener(new Preference.OnPreferenceClickListener() {
                @Override
                public boolean onPreferenceClick(Preference preference) {
                    CheckBoxPreference cbf = (CheckBoxPreference)preference;
                    if(cbf.isChecked()){
                        notification.setEnabled(true);
                    } else {
                        notification.setEnabled(false);
                    }
                    return true;
                }
            });
        }
    }
}
