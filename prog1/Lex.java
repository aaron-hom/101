//Lex.java
//Aaron Hom
//PA1 
//Takes input and output files
//Arranges contents of input file in alphabetical order
//Prints to output file

import java.io.*;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.PrintWriter;

class Lex{

    public static void main(String[] args) throws IOException{

	Scanner in = null;
	PrintWriter out = null;
	String lines = null;
	String[] inFile = null;
	int lineNum = 0;

	if(args.length != 2){ //checks if there are two arguments 
	    System.err.println("Wrong number of arguments");
	    System.exit(1);
	}

	in = new Scanner(new File(args[0])); //opens scanner

	int countLines = 0; //variable to count lines
	while(in.hasNextLine()){ //loop to count lines
	    countLines++; //add 1 to line total
	    in.nextLine(); //move to next line
	}
	in.close(); //close scanner
	in = null;

	in = new Scanner(new File(args[0])); //open another scanner
	out = new PrintWriter(new FileWriter(args[1])); //open output printer
	List A = new List(); //initializes arrays
	inFile = new String[countLines]; //string array to keep track of lines

	while(in.hasNextLine()){ //copies lines of file into string array
	    inFile[lineNum++] = in.nextLine(); //gives each line an index
	}

	//This is where it kind of gets like insertion sort
        A.append(0); //place first line from array in as first element
	for(int i = 1; i < inFile.length; i++){ 
	    String words = inFile[i]; 
	    int j = i-2;
	    A.moveBack();
	    while(j >= 0 && words.compareTo(inFile[A.get()]) <= 0){ //compares lines
		j--; 
		A.movePrev(); //moves farther back if not in alphabetical place
	    }
	    if(A.index() >= 0){
		A.insertAfter(i); //inserts line after it finds alphabetical place
 	    }else{
		A.prepend(i); //line gets inserted in back if outside of index
	    }
	}
	A.moveFront(); //moves cursor back to front
	while(A.index() >= 0){ //loop to print array in order
	    out.println(inFile[A.get()]);
	    A.moveNext();
	}
	in.close(); //end
	out.close();
	}
    }

