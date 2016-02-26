package com.org;

public abstract class SignalProcessor extends Component implements Processor
{
	protected MapRadarSignal mSignal;

	public SignalProcessor(int x, int y)
	{
		super(x, y);
	}

	public void setSignal(RadarSignal signal)
	{
		mSignal = (MapRadarSignal)signal;
	}

	public int mappingX()
	{
		return (mX - Config.Battleground.X) / Config.Tile.WIDTH;
	}

	public int mappingY()
	{
		return (mY - Config.Battleground.Y) / Config.Tile.HEIGHT;
	}
}

