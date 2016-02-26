package com.org;

public final class Config
{
	// define thte params of screen
	public final static class Screen 
	{ 
		public final static int WIDTH = 800;
		public final static int HEIGHT = 600;
	}

	// define the params of map tile
	public final static class Tile
	{
		public final static int WIDTH = 20;
		public final static int HEIGHT= 20;
		public final static int ROWS = 1;
		public final static int COLS = 7;
		public final static String PATH = "drawable/tile.png";
	}

	// define the params of map in battleground
	public final static class Map
	{
		public final static String NAME = "map";
		public final static int ROWS = 13;
		public final static int COLS = 13;
		public final static int CELL = 20;
		public final static int INDEX = 1; 
		public final static int[] BARRIER = {1, 2, 4, 5};
		public final static String PATH = "map/";
	}

	// define the params of the battleground
	public final static class Battleground
	{
		public final static int X = 250;
		public final static int Y = 120;
		public final static int WIDTH = 260;
		public final static int HEIGHT = 260;
	}

	// define the params of players' tank
	public final static class Tank 
	{
		public final static int WIDTH = 20;
		public final static int HEIGHT = 20;
		public final static int COLS = 8;
		public final static int ROWS = 4;
		public final static int LEFT = 31;
		public final static int RIGHT = 15;
		public final static int FRONT = 7;
		public final static int BACK = 23;
		public final static String PATH = "drawable/player1.png";
	}

	// define the params of enemy tank
	public final static class Enemy
	{	
		public final static int COLS = 8;
		public final static int ROWS = 8;
		public final static int LEFT = 3;
		public final static int RIGHT = 1;
		public final static int FRONT = 0;
		public final static int BACK = 2;
		public final static String PATH = "drawable/enemy.png";
	}

	// define the params of explosion animatation
	public final static class Explosion
	{
		public final static int WIDTH = 25;
		public final static int HEIGHT = 75;
		public final static int ROWS = 1;
		public final static int COLS = 3;
		public final static String PATH = "drawable/explode2.png";
	}

	// define the params of bullet
	public final static class Bullet
	{
		public final static int WIDTH = 24;
		public final static int HEIGHT = 6;
		public final static int ROWS = 1;
		public final static int COLS = 4;
		public final static int FRONT = 0;
		public final static int RIGHT = 1;
		public final static int BACK = 2;
		public final static int LEFT = 3;
		public final static String PATH = "drawable/bullet.png";
	}

	// define the params of Birth animatation
	public final static class Birth
	{
		public final static int WIDTH = 80;
		public final static int HEIGHT = 20;
		public final static int ROWS = 1;
		public final static int COLS = 4;
		public final static String PATH = "drawable/bore.png";
	}
	
	// define the params of welecome animatation
	public final static class Welcome
	{
		public final static int WIDTH = 320;
		public final static int HEIGHT = 480;
		public final static int ROWS = 1;
		public final static int COLS = 1;
		public final static String PATH = "drawable/main_bg.png";
	}

	// define the params of barier in battleground
	public final static class Barrier
	{
		public final static int CONNECTION = 0;
		public final static int WOOD = 1;
		public final static int IRON = 2;
		public final static int GRASS = 3;
		public final static int RIVER = 4;
		public final static int LAKE = 5;
		public final static int BASE = 6;
		public final static int ENEMY = 7;
	}
}
