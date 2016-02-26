package com.org;

public abstract class AbstractLoader implements Loader
{
	protected boolean hasSetParams;
	protected int mRows;
	protected int mCols;
	protected int mWidth;
	protected int mHeight;
	
	public AbstractLoader()
	{
		hasSetParams = false;
	}

	public void setParams(int rows, int cols, int width, int height)
	{
		mRows = rows;
		mCols = cols;
		mWidth = width;
		mHeight = height;
		hasSetParams = true;
	}

	public int getRows()
	{
		return mRows;
	}

	public int getCols()
	{
		return mCols;
	}

	public int getWidth()
	{
		return mWidth;
	}

	public int getHeight()
	{
		return mHeight;
	}
}
