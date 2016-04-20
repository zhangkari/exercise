package com.org;

import java.util.List;
import java.util.ArrayList;

public final class TankCommander
{
	private RadarSignalProcessor mProcessor;
	private  List<AbstractTank> mTankList;

	public TankCommander() {
		mProcessor = new RadarSignalProcessor();
		mTankList = new ArrayList<AbstractTank>();
	}

	public void addTank(AbstractTank tank) {
		mTankList.add(tank);
	}

	public void goForward()
	{
		for (AbstractTank tank : mTankList) {
			tank.goForward();
		}
	}

	public void goBack()
	{
		for (AbstractTank tank : mTankList) {
			tank.goBack();
		}
	}

	public void rotateLeft()
	{
		for (AbstractTank tank : mTankList) {
			tank.rotateLeft();
		}
	}

	public void rotateRight()
	{
		for (AbstractTank tank : mTankList) {
			tank.rotateRight();
		}
	}
}
