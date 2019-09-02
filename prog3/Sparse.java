//Sparse.java
//Aaron Hom
//awhom
//pa3
//Acts as a client for Matrix.java

import java.io.*;
import java.util.Scanner;

public class Sparse{
    public static void main(String[] args) throws IOException{
        Scanner in = null; //initialize 
        PrintWriter out = null;
        String lines = null;
        String[] words = null;

        if(args.length < 2){ //checks number of arguments is correct
            System.err.println("Sparse error: incorrect number of arguments (in file) (out file)");
            System.exit(1);
        }

        in = new Scanner(new File(args[0])); //takes in a file
        out = new PrintWriter(new FileWriter(args[1])); //opens file for output
        int mSize = 0; //initialize
        int one = 0;
        int two = 0;
        int row = 0;
        int col = 0;
        double val = 0.0;

        if(in.hasNextLine()){ //reads first line in file
            lines = in.nextLine()+"";
            words = lines.split("\\s+");
            mSize = Integer.parseInt(words[0]); //size of matrix
            one = Integer.parseInt(words[1]); //NNZ in matrix A
            two = Integer.parseInt(words[2]); //NNZ in matrix B
        }

        Matrix A = new Matrix(mSize); //initialize matricies
        Matrix B = new Matrix(mSize);

        for(int i = 0; i < one; i++){ //for NNZ in A
            if(in.hasNextLine()){ 
                lines = in.nextLine(); //goes to next line
                while(lines.isEmpty() && in.hasNextLine()){ //if blank, skip
                    lines = in.nextLine();    
                }
                lines += " "; //spaces to read between characters
                words = lines.split("\\s+"); 
                row = Integer.parseInt(words[0]); //combo of row, col. val for changeEntry 
                col = Integer.parseInt(words[1]); 
                val = Double.parseDouble(words[2]); 
	    }
            A.changeEntry(row, col, val); //insert one element at a time
        }

        for(int j = 0; j < two; j++){ //repeats with matrix B
            if(in.hasNextLine()){
	        lines = in.nextLine();
                while(lines.isEmpty() && in.hasNextLine()){
                    lines = in.nextLine();
                }
                lines += " ";
                words = lines.split("\\s+");
                row = Integer.parseInt(words[0]);
                col = Integer.parseInt(words[1]);
                val = Double.parseDouble(words[2]);
	    }
            B.changeEntry(row, col, val);
        }
	//all the print statements
        out.println("A has " +A.getNNZ()+ " non-zero entries:");
        out.println(A);

        out.println("B has " +B.getNNZ()+ "non-zero entries:");
        out.println(B);

        out.println("(1.5)*A =");
        out.println(A.scalarMult(1.5));

        out.println("A+B =");
        out.println(A.add(B));

        out.println("A+A =");
        out.println(A.add(A));

        out.println("B-A =");
        out.println(B.sub(A));

        out.println("A-A =");
        out.println(A.sub(A));

        out.println("Transpose(A) =");
        out.println(A.transpose());

        out.println("A*B =");
        out.println(A.mult(B));

        out.println("B*B =");
        out.println(B.mult(B));

        in.close();
        out.close();
    }
}
