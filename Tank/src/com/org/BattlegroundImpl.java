package com.org;

import java.awt.*;

public final class BattlegroundImpl extends AbstractBattleground
{
	
	public BattlegroundImpl(int x, int y, int w, int h)
	{
		super(x, y, w, h);
	}	

	private void drawMap(Graphics g)
	{
		Color color = g.getColor();
		g.setColor(Color.black);
		g.drawLine(mX-1, mY-1, mX+mWidth+1, mY-1);
		g.drawLine(mX-1, mY-1, mX-1, mY+mHeight+1);
		g.drawLine(mX+mWidth+1, mY-1, mX+mWidth+1, mY+mHeight+1);
		g.drawLine(mX-1, mY+mHeight+1, mX+mWidth+1, mY+mHeight+1);
		g.setColor(color);
	
		if(null == tiles)
		{
			System.out.println("tiles is null in draw");
			return;
		}
		if(null == mMapInfo)
		{
			System.out.println("mMapInfo is null in draw");
			return;
		}

		Image img;
		for(int i=0; i<mMapLoader.getRows(); ++i)
		{
			for(int j=0; j<mMapLoader.getCols(); ++j)
			{
				img = tiles[mMapInfo.getMapData(i,j)];
				if(null != img) // stands for no tile
				{
					g.drawImage(img, mX+j*mTileLoader.getWidth(), mY+i*mTileLoader.getHeight(), mTileLoader.getWidth(), mTileLoader.getHeight(), null);
				}
			}
		}
	}

	private void drawTank(Graphics g)
	{
		for(AbstractTank tank : mTankList)
		{
			if(null != tank)
			{
				tank.draw(g);
			}
		}
	}

	public void draw(Graphics g)
	{
		drawMap(g);
		drawTank(g);
	}
}
