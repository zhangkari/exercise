package com.org;

public class MapInformation
{
	private int[] mMapData;
	private int mRows;
	private int mCols;

	public MapInformation(int row, int col, int[] mapdata)
	{
		mRows = row;
		mCols = col;
		mMapData = mapdata;
	}

	public int getMapData(int row, int col)
	{
		if(row >= mRows || col >= mCols || row < 0 || col < 0)
		{
			Log.log("Invalid params");
				System.exit(-1);
		}
		return mMapData[row*mCols+col];
	}

	public boolean isConnectable(int row, int col)
	{
		int value = getMapData(row, col);
		if(Config.Barrier.CONNECTION == value|| Config.Barrier.GRASS ==  value)
		{
			return true;
		}
		return false;
	}

	public boolean isDestroyable(int row, int col)
	{
		int value = getMapData(row, col);
		if(Config.Barrier.WOOD == value|| Config.Barrier.ENEMY ==  value)
		{
			return true;
		}
		return false;
	}
}
