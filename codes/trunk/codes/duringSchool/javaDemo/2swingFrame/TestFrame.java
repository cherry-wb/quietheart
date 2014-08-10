import javax.swing.*;
public class TestFrame
{
	public static void main(String []args)
	{
		JFrame f = new JFrame("myProject");
		f.getContentPane().add(new JButton("good"));
		f.setSize(300,300);
		f.setVisible(true);
	}
}