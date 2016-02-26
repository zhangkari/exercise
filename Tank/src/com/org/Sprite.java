package com.org;

import java.awt.*;

public class Sprite extends DrawableComponent
{
	protected Image[] mFrames;
	protected Image mCurFrame;

	public Sprite(int x, int y, int w, int h)
	{
		super(x, y, w, h);
	}

	public void setFrames(Image[] frames)
	{
		mFrames = frames;
	}

	public void setCurrentFrame(int index)
	{
		if(index < 0 || index >= mFrames.length)
		{
			System.out.println("ERROR:invalid frame index");
			System.exit(1);
		}
		mCurFrame = mFrames[index];
	}

	public void setCurrentFrame(Image frame)
	{
		mCurFrame = frame;
	}

	public void draw(Graphics g)
	{
		if(null == mCurFrame)
		{
			if(null == mFrames)
				return;

			for(int i=0; i<mFrames.length; ++i)
			{
				g.drawImage(mFrames[i], mX, mY, mWidth, mHeight, null);
			}

			return;
		}

		g.drawImage(mCurFrame, mX, mY, mWidth, mHeight, null);
	}
}
