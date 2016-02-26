package com.org;

import com.org.AbstractMachine;
import java.awt.Graphics;
import com.org.Bullet;

public abstract class AbstractTank extends MachineImpl implements IReceiver
{
	protected Bullet mBullet;
	protected SignalProcessor mProcessor;

	public AbstractTank(int x, int y)
	{
		super(x, y, Config.Tank.WIDTH, Config.Tank.HEIGHT);
		mBullet = new Bullet(x, y, Config.Bullet.WIDTH, Config.Bullet.HEIGHT);
		mProcessor = new RadarSignalProcessor(x, y);
	}

	public Bullet getBullet()
	{
		return mBullet;
	}

	public void draw(Graphics g)
	{
		super.draw(g);
		if(null != mBullet)
			mBullet.draw(g);
	}

	public void onReceive(RadarSignal signal)
	{
		mProcessor.setSignal(signal);
	}
}
