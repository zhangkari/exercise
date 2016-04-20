
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import com.org.*;

public class Main implements Runnable
{
	BattlegroundImpl ground;
	AbstractTank tank;

	public Main()
	{
		ground = new BattlegroundImpl(Config.Battleground.X, Config.Battleground.Y, Config.Battleground.WIDTH, Config.Battleground.HEIGHT);
		ground.setIndex(Config.Map.INDEX);
		ground.prepareLoad();

		SceneManager.getInstance().setBattleground(ground);

		new Thread(this).start();
	}

	public void run()
	{
		while(true)
		{
//			tank.goForward();
//			SceneManager.getInstance().invalidate();
			SceneManager.getInstance().repaint();
			try
			{
				Thread.sleep(100);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] arg)
	{
		Main app = new Main();
	}	
}
