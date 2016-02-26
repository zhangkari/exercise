package com.org;

import java.awt.*;

public class EnemyTankFactory extends TankFactory
{
	private SpriteLoader spriteLoader;
	private Image[] spriteFrames;

	public EnemyTankFactory()
	{
		spriteLoader = new SpriteLoader();
		spriteLoader.setParams(Config.Tank.ROWS, Config.Tank.COLS, Config.Tank.WIDTH, Config.Tank.HEIGHT);
		spriteFrames = (Image[])spriteLoader.load(Config.Tank.PATH);	
	}

	public AbstractTank createTank()
	{
		AbstractTank tank = new TankImpl(Config.Battleground.X, Config.Battleground.Y);
		tank.setFrames(spriteFrames);
		tank.setCurrentFrame(Config.Tank.RIGHT);
		return tank;
	}
}
