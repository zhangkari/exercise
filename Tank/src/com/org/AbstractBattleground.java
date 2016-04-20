package com.org;

import java.awt.*;
import java.awt.event.*;
import java.util.List;
import java.util.LinkedList;

public abstract class AbstractBattleground extends DrawableComponent
{
	protected AbstractLoader mMapLoader;
	protected TileLoader mTileLoader;
	protected int mIndex;
	protected Image[] tiles;
	protected MapInformation mMapInfo;
	protected List<AbstractTank> mTankList;
	protected SenderRadar mRadar;
	protected TankFactory tankFactory;
	protected AbstractTank mTank;

	public AbstractBattleground(int x, int y, int w, int h)
	{
		super(x, y, w, h);
		mTankList = new LinkedList<AbstractTank>();
		mMapLoader = new MapLoader();
		mMapLoader.setParams(Config.Map.ROWS, Config.Map.COLS, 0, 0);
		mTileLoader = new TileLoader();
		mTileLoader.setParams(Config.Tile.ROWS, Config.Tile.COLS, Config.Tile.WIDTH, Config.Tile.HEIGHT);
		mRadar = new SenderRadar();
		tankFactory = new PlayerTankFactory();
		mTank = tankFactory.createTank();	
		addTank(mTank);
	}

	public void addTank(AbstractTank tank)
	{
		mTankList.add(tank);
		mRadar.addReceiver(tank);
		sendRadarSignal();
	}

	public void removeTank(AbstractTank tank)
	{
		mTankList.remove(tank);
		mRadar.removeReceiver(tank);
	}

	public void setIndex(int index)
	{
		mIndex = index;
		mMapInfo = (MapInformation)mMapLoader.load("map/map"+mIndex+".txt");
		if(null == mMapInfo)
		{
		System.out.println("ERROR:mMapInfo is null in setIndex");
		System.exit(1);
		}
	}

	public void prepareLoad()
	{
		tiles = (Image[])mTileLoader.load("drawable/tile.png");
		if(null == tiles)
		{
			System.out.println("tiles is null in BattlegroundImpl constructor");
			System.exit(1);
		}

		tiles = (Image[])mTileLoader.addEmptyOne(tiles);
		mMapInfo = (MapInformation)mMapLoader.load("map/map"+mIndex+".txt");
		if(null == mMapInfo)
		{
			System.out.println("mpadata is null in BattlegroundImpl constructor");
			System.exit(1);
		}
	}

	public void sendRadarSignal()
	{
		mRadar.send(new MapRadarSignal(mMapInfo));
	}

	public void keyPressed(KeyEvent e)
	{
		if('q' == e.getKeyChar() || 'Q' == e.getKeyChar())
		{
			System.exit(0);
		}

		switch(e.getKeyCode())
		{
			case KeyEvent.VK_LEFT:
				Log.d("left");
				mTank.rotateLeft();
				break;

			case KeyEvent.VK_RIGHT:
				Log.d("right");
				mTank.rotateRight();
				break;

			case KeyEvent.VK_UP:
				Log.d("up");
				mTank.goBack();
				break;

			case KeyEvent.VK_DOWN:
				Log.d("down");
				mTank.goForward();
				break;

			case KeyEvent.VK_SPACE:
				Log.d("space");
				break;
		}

	}


}
