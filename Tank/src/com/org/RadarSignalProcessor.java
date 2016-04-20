package com.org;

public class RadarSignalProcessor extends SignalProcessor
{
	public RadarSignalProcessor()
	{
		super();
	}

	public RadarSignalProcessor(int x, int y)
	{
		super(x, y);
	}

	public void updatePosition(int x, int y) {
		setX(x);
		setY(y);
	}

	public boolean isLeftConnected()
	{
		if(null == mSignal)
		{
			Log.d("Null pointer exception in RadarSignalProcessor.isLeftConnected()");
			System.exit(-1);	
		}

		int x = mappingX();
		int y = mappingY();
		MapInformation info = mSignal.getMapInfo();	

		if(x-1 >= 0)
		{
			if(info.isConnectable(y, x-1))
				return true;
		}

		return false;
	}

	public boolean isRightConnected()
	{
		if(null == mSignal)
		{
			Log.d("Null pointer exception in RadarSignalProcessor.isRightConnected()");
			System.exit(-1);	
		}

		int x = mappingX();
		int y = mappingY();
		MapInformation info = mSignal.getMapInfo();	

		if(x+1 < Config.Map.COLS)
		{
			if(info.isConnectable(y, x+1))
				return true;
		}

		return false;
	}

	public boolean isFrontConnected()
	{
		if(null == mSignal)
		{
			Log.d("Null pointer exception in RadarSignalProcessor.isFrontConnected()");
			System.exit(-1);	
		}
		return false;
	}

	public boolean isBackConnected()
	{
		if(null == mSignal)
		{
			Log.d("Null pointer exception in RadarSignalProcessor.isBackConnected()");
			System.exit(-1);	
		}
		return false;
	}
}
