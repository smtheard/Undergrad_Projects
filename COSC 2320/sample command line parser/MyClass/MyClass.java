import java.io.*;
import java.util.Scanner;
import java.util.Hashtable;

/// Class example
public class MyClass
{
	//Example of public method in MyClass
	public void read(String filename) throws IOException {

		//Read entire file.
		Scanner scanner = new Scanner(new FileInputStream(filename));
		try {
			while (scanner.hasNextLine()){ //checks existence of next line
				System.out.println(scanner.nextLine()); //prints line.
			}
		}
		finally{
			scanner.close();
		}
	}

	//Main method
	public static void main(String[] args) {

		try{
			//managing input parameters.
			Hashtable hashParameters = new Hashtable();
			String[] strParameters = args[0].split(";");

			for( String s: strParameters) {
				String[] strSplit = s.split("=");
				hashParameters.put(strSplit[0], strSplit[1]);
			}
			//End of managing input parameters

			//Recover input parameter in hashtable
			if ( hashParameters.get("filename") != null )
			{
				//Instance of MyClass
				MyClass instance = new MyClass();
				//Call read method in instance.
				instance.read( hashParameters.get("filename").toString() );
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}
	}
}