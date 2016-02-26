import java.awt.*;
import java.awt.Image;
import java.awt.image.*;
import javax.swing.*;
import java.lang.Math; 
import java.io.*;
import javax.imageio.ImageIO;
import sun.audio.AudioPlayer;

import com.org.*;

public class Test extends JFrame implements Runnable
{
	private boolean mFlag = true;
	private Image[] tiles;
	private MapLoader loader;
	private Integer[] map;
	private AbstractBattleground battleground;	
	
	public Test()
	{
		super();
		setSize(800, 600);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		//		setVisible(true);
		TileLoader tileLoader = new TileLoader();
		tileLoader.setParams(Config.Tile.ROWS, Config.Tile.COLS, Config.Tile.WIDTH, Config.Tile.HEIGHT);


		loader = new MapLoader();
		loader.setParams(Config.Map.ROWS, Config.Map.COLS, 0, 0);

		battleground = new BattlegroundImpl(250, 120, 260, 260);
		battleground.setIndex(Config.Map.INDEX);
		battleground.prepareLoad();

//		battleground.setColor(Color.white);
	}

	public void paint(Graphics g)
	{
//		super.paint(g);
		Graphics2D g2d = (Graphics2D)g;
		
		battleground.draw(g);

	}

	public void run()
	{
		while(mFlag)
		{
			try
			{
				Thread.sleep(20);
			}
			catch(Exception e)
			{
			}	
			this.repaint();
		}
	}

	public static void main(String []arg) throws Exception
	{
		Test hello = new Test();
		hello.setVisible(true);
		new Thread(hello).start();

		InputStream instream = new FileInputStream(new File("sound/tank_run.wav"));
		AudioPlayer.player.start(instream);

		for(int i=1; i<=hello.loader.getMapCount(); ++i)
		{
		hello.battleground.setIndex(i);
		Thread.sleep(5000);	
		}
	}

}
