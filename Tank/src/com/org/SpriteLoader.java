package com.org;

import java.io.*;
import java.awt.Image;
import java.awt.image.*;
import javax.imageio.ImageIO;

public class SpriteLoader extends AbstractLoader
{
	public Object load(String fileName)
	{
		if(!hasSetParams)
		{
			Log.d("ERROR: params not set, call setParams before");
			System.exit(1);
		}

		try
		{
			BufferedImage image = ImageIO.read(new File(fileName));
			int TOTAL = mRows * mCols;
			Image[] tiles = new Image[TOTAL];

			for(int i=0; i<TOTAL; ++i)
			{
				tiles[i] = image.getSubimage((i%mCols)*mWidth, i/mCols, mWidth, mHeight);
			}

			return tiles;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
}
