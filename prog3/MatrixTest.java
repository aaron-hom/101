//MatrixTest.java
//Aaron Hom
//awhom
//pa3
//A test client for Matrix.java

public class MatrixTest{
    public static void main(String[] args){
	int i, j;
	int n = 10;
	Matrix X = new Matrix(n);
	Matrix Y = new Matrix(n);

	System.out.println(X.getNNZ());
	System.out.println(Y.getNNZ());

	X.changeEntry(1, 1, 9);
	Y.changeEntry(1, 1, 1);
	X.changeEntry(1, 2, 8);
        Y.changeEntry(1, 2, 2);
	X.changeEntry(1, 3, 7);
        Y.changeEntry(1, 3, 3);

	X.changeEntry(2, 1, 6);
        Y.changeEntry(2, 1, 4);
	X.changeEntry(2, 2, 5);
        Y.changeEntry(2, 2, 5);
	X.changeEntry(2, 3, 4);
        Y.changeEntry(2, 3, 6);

	X.changeEntry(3, 1, 3);
        Y.changeEntry(3, 1, 7);
	X.changeEntry(3, 2, 2);
        Y.changeEntry(3, 2, 8);
	X.changeEntry(3, 3, 1);
        Y.changeEntry(3, 3, 9);

	System.out.println("Matrix X has "+X.getNNZ()+" non zero elements.");
        System.out.println("Matrix Y has "+Y.getNNZ()+" non zero elements.");

	System.out.println(X);
        System.out.println(Y);

	Matrix Z = X.add(Y);
	System.out.println("Matrix Z has "+Z.getNNZ()+" non zero elements.");
	System.out.println(Z);

	Matrix S = Z.sub(Y);
	System.out.println(S);

	Matrix T = X.transpose();
	System.out.println(T);

	Matrix M = X.mult(Y);
	System.out.println(M);

	Matrix C = X.copy();
	System.out.println(C);

	Matrix SM = X.scalarMult(2.0);
	System.out.println(SM);

	System.out.println(X.equals(X));
	System.out.println(X.equals(Y));

	Matrix H = X.scalarMult(2.0).sub(X);
	System.out.println(H);

	X.makeZero();
        System.out.println(X.getNNZ());
    }
}

