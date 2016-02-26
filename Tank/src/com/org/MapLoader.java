package com.org;

import java.io.*;
import com.org.Config;

public class MapLoader extends AbstractLoader
{
	public int getMapCount()
	{
		File f;
		try
		{
			f = new File("map");
		}
		catch(Exception e)
		{
			return -1;		
		}

		if(!f.isDirectory())
		{
			return -1;
		}
	
		return f.list().length;	
	}

	public String getMapFileName(int i)
	{
		if(i < Config.Map.INDEX)
			return null;

		if(i > getMapCount())
			return null;
		
		return "map/"+Config.Map.NAME+i+".txt";
	}

	public MapLoader()
	{

	}

	private Object newMapInfo(int[] mapdata)
	{
		if(null == mapdata)
		{
			Log.log("NULL pointer exception");
			System.exit(-1);
		}
		return new MapInformation(mRows, mCols, mapdata);
	}

	public Object load(String fileName)
	{
		if(!hasSetParams)
		{
			System.out.println("ERROR:params not set, call setParams() before");
			System.exit(1);
		}

		FileReader fr = null;
		BufferedReader br = null;

		try
		{
			fr = new FileReader(fileName);
			br = new BufferedReader(fr);
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}

		int[] data = new int[mCols * mRows];
		int intValue;
		int counter = 0;

		try
		{
			while( (intValue = br.read()) != -1)
			{
				if(intValue >= '0' && intValue <= '9')
				{
					data[counter++] = intValue - '0';
				}
			}

			return newMapInfo(data);
		}
		catch(Exception e)
		{
			return null;
		}

		finally
		{
			try
			{
				br.close();
				fr.close();
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}

	}
}
