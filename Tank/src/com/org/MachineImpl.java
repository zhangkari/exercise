package com.org;

import java.awt.*;

public class MachineImpl extends AbstractMachine 
{
	public MachineImpl(int x, int y, int width, int height)
	{
		super(x, y, width, height);
	}

	public void draw(Graphics g)
	{
		super.draw(g);
	}

	public void goForward()
	{
		if(mCurDirection == DirectionEnum.LEFT)
			--mX;
		else if(mCurDirection == DirectionEnum.RIGHT)
			++mX;
		else if(mCurDirection == DirectionEnum.FRONT)
			--mY;
		else 
			++mY;
	}


	public void goBack()
	{
		if(mCurDirection == DirectionEnum.LEFT)
			++mX;
		else if(mCurDirection == DirectionEnum.RIGHT)
			--mX;
		else if(mCurDirection == DirectionEnum.FRONT)
			++mY;
		else 
			--mY;
	}


	public void rotateLeft()
	{
		if(mCurDirection == DirectionEnum.LEFT)
			mCurDirection = DirectionEnum.BACK;
		else if(mCurDirection == DirectionEnum.RIGHT)
			mCurDirection = DirectionEnum.FRONT;
		else if(mCurDirection == DirectionEnum.FRONT)
			mCurDirection = DirectionEnum.LEFT;
		else 
			mCurDirection = DirectionEnum.RIGHT;
	}

	public void rotateRight()
	{
		if(mCurDirection == DirectionEnum.LEFT)
			mCurDirection = DirectionEnum.FRONT;
		else if(mCurDirection == DirectionEnum.RIGHT)
			mCurDirection = DirectionEnum.BACK;
		else if(mCurDirection == DirectionEnum.FRONT)
			mCurDirection = DirectionEnum.RIGHT;
		else 
			mCurDirection = DirectionEnum.LEFT;
	}

	public void rotateBack()
	{
		if(mCurDirection == DirectionEnum.LEFT)
			mCurDirection = DirectionEnum.RIGHT;
		else if(mCurDirection == DirectionEnum.RIGHT)
			mCurDirection = DirectionEnum.LEFT;
		else if(mCurDirection == DirectionEnum.FRONT)
			mCurDirection = DirectionEnum.BACK;
		else 
			mCurDirection = DirectionEnum.FRONT;
	}
}
