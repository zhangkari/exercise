package com.org;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.LinkedList;
import com.org.*;

public class SceneManager extends JFrame implements KeyListener
{
	private AbstractBattleground mBattleground;

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
	}

	public static SceneManager getInstance()
	{
		return SceneManagerHolder.instance;
	}

	@Override
	public void paint(Graphics g)
	{
		//		super.paint(g);
		if (mBattleground != null) {
			mBattleground.draw(g);
		}
	}

	public void setBattleground(AbstractBattleground battleground)
	{
		mBattleground = battleground;
	}

	public void  clearBattleground()
	{
		mBattleground = null;
	}

	public void keyPressed(KeyEvent e)
	{
		mBattleground.keyPressed(e);
	}

	public void keyReleased(KeyEvent e)
	{

	}

	public void keyTyped(KeyEvent e)
	{

	}
}

