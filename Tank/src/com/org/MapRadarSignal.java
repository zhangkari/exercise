package com.org;

public class MapRadarSignal extends RadarSignal
{
	private MapInformation mMapInfo;

	public MapRadarSignal(MapInformation info)
	{
		mMapInfo = info;
	}	

	public MapInformation getMapInfo()
	{
		return mMapInfo;
	}
}
