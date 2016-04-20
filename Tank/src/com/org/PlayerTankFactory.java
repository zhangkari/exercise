package com.org;

import java.awt.*;

public class PlayerTankFactory extends TankFactory
{
	private SpriteLoader spriteLoader;
	private Image[] spriteFrames;

	public PlayerTankFactory()
	{
		spriteLoader = new SpriteLoader();
		spriteLoader.setParams(Config.Tank.ROWS, Config.Tank.COLS, Config.Tank.WIDTH, Config.Tank.HEIGHT);
		spriteFrames = (Image[])spriteLoader.load(Config.Tank.PATH);	
	}

	public AbstractTank createTank()
	{
		AbstractTank tank = new TankImpl(Config.Battleground.X, Config.Battleground.Y, 0);
		tank.setFrames(spriteFrames);
		tank.setCurrentFrame(Config.Tank.RIGHT);
		return tank;
	}
}
