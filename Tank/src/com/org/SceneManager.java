package com.org;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.LinkedList;
import com.org.*;

public class SceneManager extends JFrame implements KeyListener
{
	private LinkedList<Drawable> mDrawableList;
	private static class SceneManagerHolder
	{
		private static SceneManager instance = new SceneManager();
	}

	private SceneManager()
	{
		super();
		setSize(Config.Screen.WIDTH, Config.Screen.HEIGHT);
		setVisible(true);
		setResizable(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		addKeyListener(this);

		mDrawableList = new LinkedList<Drawable>();
	}

	public static SceneManager getInstance()
	{
		return SceneManagerHolder.instance;
	}

	public void paint(Graphics g)
	{
		//		super.paint(g);
		for(Drawable d : mDrawableList)
		{
			d.draw(g);
		}
	}

	public void addDrawable(Drawable drawable)
	{
		mDrawableList.add(drawable);
	}

	public void removeDrawable(Drawable drawable)
	{
		mDrawableList.remove(drawable);
	}

	public void keyPressed(KeyEvent e)
	{
		if('q' == e.getKeyChar() || 'Q' == e.getKeyChar())
		{
			System.exit(0);
		}

		switch(e.getKeyCode())
		{
			case KeyEvent.VK_LEFT:
				Log.d("left");
				break;

			case KeyEvent.VK_RIGHT:
				Log.d("right");
				break;

			case KeyEvent.VK_UP:
				Log.d("up");
				break;

			case KeyEvent.VK_DOWN:
				Log.d("down");
				break;
		}

	}

	public void keyReleased(KeyEvent e)
	{

	}

	public void keyTyped(KeyEvent e)
	{

	}
}

