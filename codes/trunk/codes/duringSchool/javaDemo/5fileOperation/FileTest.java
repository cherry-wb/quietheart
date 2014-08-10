import java.io.*;
/*创建一个文件句柄可以查看文件的属性也可以操作文件（不是往里面写东西）*/
public class FileTest
{
	public static void main(String[] args)
	{
		File f = new File("1.txt");
		if(f.exists())
			f.delete();
		try
		{
				f.createNewFile();
		}
		catch(Exception e)
		{
				System.out.println(e.getMessage());
		}
				
		System.out.println("File Path:"+f.getAbsolutePath());
		System.out.println(f.canWrite()?"is writeable":"is not writeable");
	}
}