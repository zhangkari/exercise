package com.org;

import java.util.List;
import java.util.LinkedList;

public class TankRadarSignal extends RadarSignal
{
	private List<AbstractTank> mTankList;
	
	public TankRadarSignal()
	{
		mTankList = new LinkedList();
	}	

	public void addTank(AbstractTank tank)
	{
		mTankList.add(tank);
	}
}
