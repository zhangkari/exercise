package com.org;

import java.awt.*;

public final class TankImpl extends AbstractTank
{
	public TankImpl(int x, int y)
	{
		super(x, y);
	}

	public TankImpl(int x, int y, int role) {
		super(x, y, role);
	}

	public void goForward()
	{
		super.setCurrentFrame(Config.Tank.FRONT);

		if(DirectionEnum.FRONT == mCurDirection)
		{
			while(mProcessor.isRightConnected())
			{
				super.goForward();
			}
		}
	}

	public void goBack()
	{
		super.setCurrentFrame(Config.Tank.BACK);
		super.goBack();
	}
}
