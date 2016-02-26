package com.org;

import com.org.DirectionEnum;

public class Component
{
	protected DirectionEnum mCurDirection;
	protected int mX;
	protected int mY;
	protected int mWidth;
	protected int mHeight;

	public Component()
	{
		this(DirectionEnum.FRONT, 0, 0);
	}

	public Component(DirectionEnum direc)
	{
		this(direc, 0, 0);
	}

	public Component(int x, int y)
	{
		this(DirectionEnum.FRONT, x, y);
	}

	public Component(DirectionEnum direc, int x, int y)
	{
		mCurDirection = direc;
		mX = x;
		mY = y;
	}

	public Component(int x, int y, int w, int h)
	{
		mCurDirection = DirectionEnum.FRONT;
		mX = x;
		mY = y;
		mWidth = w;
		mHeight = h;
	}

	public int getX()
	{
		return mX;
	}

	public Component setX(int x)
	{
		mX = x;
		return this;
	}

	public int getY()
	{
		return mY;
	}

	public Component setY(int y)
	{
		mY = y;
		return this;
	}

	public Component setWidth(int width)
	{
		mWidth = width;
		return this;
	}

	public int getWidth()
	{
		return mWidth;
	}

	public int getHeight()
	{
		return mHeight;
	}

	public Component setHeight(int height)
	{
		mHeight = height;
		return this;
	}

	public DirectionEnum getDirection()
	{
		return mCurDirection;
	}

	public Component setDirection(DirectionEnum direc)
	{
		mCurDirection = direc;
		return this;
	}
}
