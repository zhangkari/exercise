package com.org;

import java.awt.Color;

public abstract class DrawableComponent extends Component implements Drawable
{
	public DrawableComponent(int x, int y)
	{
		super(x, y);
	}

	public DrawableComponent(int x, int y, int w, int h)
	{
		super(x, y, w, h);
	}

	protected Color mColor = Color.black;
	public void setColor(Color color)
	{
		mColor = color;
	}
}
