import java.util.*;
import java.io.*;
public class RecordCount
{
	public static void main(String[] args)
	{
		Properties settings = new Properties();
		try
		{
			settings.load(new FileInputStream("e:\\experiment\\count.txt"));
		}
		catch(Exception e)
		{
			settings.setProperty("count",new Integer(0).toString());
		}
		int c = Integer.parseInt(settings.getProperty("count"))+1;
		System.out.println("第"+c+"次使用");
		settings.put("Count",new Integer(c).toString());
		try
		{
			settings.store(new FileOutputStream("e:\\experiment\\count.txt"),"This Program is used:");
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}	
	}
}