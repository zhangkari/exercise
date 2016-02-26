package com.org;

import java.awt.Color;
import java.awt.Graphics;

public class Bullet extends Sprite 
{
	protected boolean mIsShot;
	private int[] mGroundData;

	public Bullet(int x, int y, int w, int h)
	{
		super(x, y, w, h);
		mIsShot = false;
	}

	public void shoot()
	{
		mIsShot = true;
		goForward();
	}

	public void destroy()
	{
		mIsShot = false;
	}

	public void goForward()
	{

	}

	public void goBack()
	{

	}


	public void draw(Graphics g)
	{
		if(mIsShot)
		{
			super.draw(g);
		}
	}

}
