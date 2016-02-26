package com.org;

import java.io.*;
import java.awt.Image;
import java.awt.image.*;
import javax.imageio.ImageIO;

public class TileLoader extends SpriteLoader
{
	public Object[] addEmptyOne(Object[] obj)
	{
		Object[] tiles = new BufferedImage[obj.length+1];
		for(int i=0; i<obj.length; ++i)
		{
			tiles[i+1] = obj[i];
		}

		obj[0] = null;
		return tiles;
	}
}
