package rosendahl.steven.com.jsonderulo;

import android.app.Activity;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.preference.CheckBoxPreference;
import android.preference.Preference;
import android.preference.PreferenceFragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;


public class SettingsActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FragmentManager fragger = getFragmentManager();
        FragmentTransaction transaction = fragger.beginTransaction();
        PlaceholderFragment prefsFrag = new PlaceholderFragment();
        transaction.replace(android.R.id.content,prefsFrag);
        transaction.commit();
    }

    public static class PlaceholderFragment extends PreferenceFragment {

        public PlaceholderFragment() {
        }

        @Override
        public void onCreate(Bundle instance){
            super.onCreate(instance);
            addPreferencesFromResource(R.xml.preferences);
            final CheckBoxPreference teton =
                    (CheckBoxPreference)getPreferenceManager().findPreference("dl_from_teton");
            final CheckBoxPreference cnu =
                    (CheckBoxPreference)getPreferenceManager().findPreference("dl_from_pcse");
            final CheckBoxPreference supsec =
                    (CheckBoxPreference)getPreferenceManager().findPreference("dl_from_supsec");
            teton.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
                @Override
                public boolean onPreferenceChange(Preference preference, Object newValue) {
                    if(newValue.toString().equals("true")){
                        cnu.setChecked(false);
                        supsec.setChecked(false);
                        teton.setChecked(true);
                    }
                    return false;
                }
            });
            cnu.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
                @Override
                public boolean onPreferenceChange(Preference preference, Object newValue) {
                    if(newValue.toString().equals("true")){
                        teton.setChecked(false);
                        supsec.setChecked(false);
                        cnu.setChecked(true);
                    }
                    return false;
                }
            });
            supsec.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener() {
                @Override
                public boolean onPreferenceChange(Preference preference, Object newValue) {
                    if(newValue.toString().equals("true")) {
                        teton.setChecked(false);
                        supsec.setChecked(true);
                        cnu.setChecked(false);
                    }
                    return false;
                }
            });
        }
    }
}
