import java.awt.*;
import java.awt.event.*;
public class DrawLine extends Frame
{
	public static void main(String []args)
	{
		DrawLine f = new DrawLine();
		//题目不能加到构造函数里面，因为没有继承那个构造函数
		//DrawLine f = new DrawLine("绘制直线图形");
		f.setTitle("绘制直线");
		f.doit();
	}
	public void paint(Graphics g)
	{//重新绘制窗口的图形
		g.setColor(Color.RED);
		g.setFont(new Font("隶书",Font.ITALIC|Font.BOLD,30));
		g.drawString(new String(orgX+","+orgY),orgX,orgY);
		g.drawString(new String(endX+","+endY),endX,endY);
		g.drawLine(orgX,orgY,endX,endY);
	}
	public void doit()
	{
		setSize(500,500);
		setVisible(true);
		addMouseListener(new MouseAdapter()
		{
			public void mousePressed(MouseEvent e)
			{
				down = true;
				orgX = e.getX();
				orgY = e.getY();
			}
			public void mouseReleased(MouseEvent e)
			{
				down = false;
				endX = e.getX();
				endY = e.getY();
				Graphics g = getGraphics();
				//设置图形的显示颜色
				g.setColor(Color.RED);
				//设置文本的字体
				g.setFont(new Font("隶书",Font.ITALIC|Font.BOLD,30));
				g.drawString(new String(orgX+","+orgY),orgX,orgY);
				g.drawString(new String(endX+","+endY),endX,endY);
				g.drawLine(orgX,orgY,endX,endY);
			}
		});
		addMouseMotionListener(new MouseMotionAdapter()
		{
			public void mouseMoved(MouseEvent e)
			{//添加鼠标移动的函数
				if(down)//为什么不管用??是不是多线程的问题？
				{
				Graphics g = getGraphics();
				//设置图形的显示颜色
				g.setColor(Color.RED);
				endX = e.getX();
				endY = e.getY();
				g.drawLine(orgX,orgY,endX,endY);
				orgX = endX;
				orgY = endY;
				}
			}
		});
		addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{//关闭窗口的响应函数
				((Window)e.getSource()).dispose();//没有这句话也可以退出程序
				System.exit(0);
			}
		});
	}
	//Graphics g = getGraphics();//不能只放这里??
	int orgX;
	int orgY;
	int endX;
	int endY;
	boolean down = false;
}