package com.org;

public abstract class MovableComponent extends Component implements Movable
{
	public MovableComponent()
	{
		this(10);
		mSpeed = 10;
	}

	public MovableComponent(int speed)
	{
		super();	
		mSpeed = speed;
	}
	
	public MovableComponent(int x, int y)
	{
		super(x, y);
		mSpeed = 10;
	}

	public MovableComponent(int x, int y, int speed)
	{
		super(x, y);
		mSpeed = speed;
	}

	public int getSpeed()
	{
		return mSpeed;
	}

	public MovableComponent setSpeed(int speed)
	{
		mSpeed = speed;
		return this;
	}

	protected int mSpeed;
}
