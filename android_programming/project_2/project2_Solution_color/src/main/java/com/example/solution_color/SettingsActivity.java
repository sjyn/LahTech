package com.example.solution_color;

import android.app.Activity;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.os.Environment;
import android.preference.Preference;
import android.preference.PreferenceFragment;
import android.widget.Toast;

import java.io.File;

public class SettingsActivity extends Activity {
	@Override
	  public void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);

		// Display the fragment as the main content.
		FragmentManager mFragmentManager = getFragmentManager();
		FragmentTransaction mFragmentTransaction = mFragmentManager
				.beginTransaction();
		PrefsFragment mPrefsFragment = new PrefsFragment();
		mFragmentTransaction.replace(android.R.id.content, mPrefsFragment);
		mFragmentTransaction.commit();	    
	  }
	
	public static class PrefsFragment extends PreferenceFragment {

		@Override
		public void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState);

			// Load the preferences from an XML resource
			addPreferencesFromResource(R.xml.preferences);
            Preference button = findPreference("button");
            button.setOnPreferenceClickListener(new Preference.OnPreferenceClickListener(){
                @Override
                public boolean onPreferenceClick(Preference pref){
                    String path0 = Environment.getExternalStoragePublicDirectory(
                            Environment.DIRECTORY_PICTURES) + "/picture.png";
                    File f0 = new File(path0);
                    if(f0.exists())
                        f0.delete();
                    String path1 = Environment.getExternalStoragePublicDirectory(
                            Environment.DIRECTORY_PICTURES) + "/picture_saved.png";
                    File f1 = new File(path1);
                    if(f1.exists())
                        f1.delete();
                    Toast.makeText(getActivity(),"Files Deleted",Toast.LENGTH_SHORT).show();
                    return true;
                }
            });
		}
	}
}
