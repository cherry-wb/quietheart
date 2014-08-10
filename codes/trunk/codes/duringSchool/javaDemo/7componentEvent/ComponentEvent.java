import java.awt.*;
import java.awt.event.*;
/*本程序可以响应侦听器的事件，也可以响应组件上激活的事件*/
class MyButton extends Button
{
	private MyButton friend;
	public void setFriend(MyButton friend)
	{
		this.friend = friend;
	}
	public MyButton(String name)
	{
		super(name);
		enableEvents(AWTEvent.MOUSE_MOTION_EVENT_MASK);//激活按钮组件响应事件鼠标移动
	}
	protected void processMouseMotionEvent(MouseEvent e)
	{
		setVisible(false);
		friend.setVisible(true);
	}
}

public class ComponentEvent
{
	public static void main(String []args)
	{
		MyButton btn1 = new MyButton("你来抓我呀！");
		MyButton btn2 = new MyButton("你来抓我呀！");
		btn1.setFriend(btn2);
		btn2.setFriend(btn1);
		btn2.setVisible(true);
		Frame f = new Frame("响应事件");
		f.add(btn1,"North");
		f.add(btn2,"South");
		f.addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{
				e.getWindow().setVisible(false);
				((Window)e.getComponent()).dispose();
				System.exit(0);
			}
		});//添加侦听器来侦听窗口的事件，并用内部类实现
		f.setSize(300,300);
		f.setVisible(true);
		btn1.setVisible(false);
	}
}