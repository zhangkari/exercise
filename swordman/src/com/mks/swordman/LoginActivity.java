package com.mks.swordman;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class LoginActivity extends Activity implements OnClickListener {

	private Button mBtnLogin;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		initView();
		setupListener();
	}

	private void initView() {
		mBtnLogin = (Button) findViewById(R.id.login_btn_login);
	}

	private void setupListener() {
		mBtnLogin.setOnClickListener(this);
	}

	@Override
	public void onClick(View view) {
		int id = view.getId();
		if (R.id.login_btn_login == id) {

		}
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}
}
