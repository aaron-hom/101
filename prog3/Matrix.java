//Matrix.java
//Aaron Hom
//awhom
//pa3
//Acts as a client for List.java

public class Matrix{

    private class Element{
	int col;
	double val;
	Element(int col, double val){
	    this.col = col;
	    this.val = val;
	}
        
	public String toString(){
	    return "(" +col +", " +val +")";
	}

	public boolean equals(Object x){
	    Element e;
	    if(getClass() != x.getClass()){
		return false;
	    }else if(x == null){
		return false;
	    }else{
		e = (Element) x;
		return(this.col == e.col && this.val == e.val);
	    }
	}
    }
    private List row[]; //list of rows
    private int mSize; //size of matrix
    private int nnz; //number of non zero elements

// Constructor
// Makes a new n x n zero Matrix. pre: n>=1
    Matrix(int n){
	if(n < 1){
            throw new RuntimeException("Invalid size for matrix");
	} 
        row = new List[n+1]; //since we don't use List[0]
        mSize = n+1;
        nnz = 0;
        for(int i = 1; i < (n+1); i++){
	    row[i] = new List();
        }
    }

// Access functions ------------------------------------------------------
//getSize()
//Returns n, the number of rows and columns of this Matrix
    int getSize(){ 
	return row.length - 1;
    }
//getNNZ()
//Returns the number of non-zero entries in this Matrix
    int getNNZ(){
	for(int i = 1; i <= getSize(); i++){
	    nnz += row[i].length();
	}
	return nnz;
    }

//equals()
// overrides Object's equals() method
    public boolean equals(Object x){
	Matrix m;
	if(x instanceof Matrix){
	    m = (Matrix) x;
	    if(getSize() != m.getSize()){
		return false;
	    }
	    for(int i = 1; i < getSize(); i++){
		if(!(row[i].equals(m.row[i]))){
		    return false;
		}
	    }
	}
	return true;
    }

// Manipulation procedures -----------------------------------------------

//makeZero() // sets this Matrix to the zero state
    void makeZero(){
	for(int i = 1; i <= getSize(); i++){
	    row[i].clear();
	}
	nnz = 0;
    }

//copy() // returns a new Matrix having the same entries as this Matrix
    Matrix copy(){
	Matrix dupe = new Matrix(getSize());
	for(int i = 1; i <= getSize(); i++){
	    row[i].moveFront();
	    while(row[i].index() >= 0){
		Element e = (Element) row[i].get();
		dupe.changeEntry(i, e.col, e.val);
		row[i].moveNext();
	    }
	}
	return dupe; 
    }

//changeEntry()
//changes ith row, jth column of this Matrix to x
//pre: 1<=i<=getSize(), 1<=j<=getSize()
    void changeEntry(int i, int j, double x){
	if(i < 1 || i > getSize()){ //checks if i exists
		throw new RuntimeException("Matrix error: changeEntry() called on matrix with invalid i-th position");
	}
	if(j < 1 || j > getSize()){ //checks if j exists
		throw new RuntimeException("Matrix error: changeEntry() called on matrix with invalid j-th position");
	}
	row[i].moveFront(); //move to the front of List at row[i]
	boolean isThere = false;
        while(row[i].index() >= 0){ //search through the whole row
	    Element e = (Element) row[i].get(); //gets element associated with index
	    if(e.col == j){ //if search finds a col equal to j
		isThere = true;
	    }else{
		isThere = false;
	    }
	    if(isThere){
		if(x == 0.0){ //if x is 0
		    row[i].delete(); //delete the element
		    return;
		}else{ //if x is not 0
		    e.val = x; //replace value
		    return;
		}
	    }
	    row[i].moveNext(); //move cursor to the next element
	}
	if(!isThere && x != 0.0){ //if search does not find col equal to j and x is not 0
	    row[i].moveFront(); //move to front of list
	    if(row[i].index() == -1){ //if cursor index in row does not exist
	        row[i].append(new Element(j, x)); //inserts element into back
                return;
	    }else{
	        while(row[i].index() > -1 && ((Element)row[i].get()).col < j){
		    row[i].moveNext();
		}
		if(row[i].index() > -1){ //if cursor exists 
		    row[i].insertBefore(new Element(j, x)); //insert element before cursor
		    return;
		}else{
		    row[i].append(new Element(j, x)); //insert element into back
		    return;
		}
	    }
	}
    }
	   
//scalarMult()
//returns a new Matrix that is the scalar product of this Matrix with x
    Matrix scalarMult(double x){
	Matrix dupe = this.copy(); //copies matrix
	for(int i = 1; i <= dupe.getSize(); i++){
	    dupe.row[i].moveFront();
	    while(dupe.row[i].index() >= 0){
		Element e = (Element)dupe.row[i].get();
		dupe.changeEntry(i, e.col, (x * e.val)); //multiplies each element by scalar
		dupe.row[i].moveNext(); //next element
	    }
	}
	return dupe;
    }

//add()
//returns a new Matrix that is the sum of this Matrix with M
//pre: getSize()==M.getSize()
    Matrix add(Matrix M){
	if(getSize() != M.getSize()){
	    throw new RuntimeException("Matrix error: add() called on different sized matricies");
	}
	if(M == this){ //if both matricies are the same
	    return this.copy().scalarMult(2); //multiply by 2
	}
	Matrix result = new Matrix(getSize()); //otherwise add together  
	    for(int i = 1; i <= getSize(); i++){
		result.row[i] = addHelp(row[i], M.row[i]);
	    }
	return result;
    }

//sub()
//returns a new Matrix that is the difference of this Matrix with M
//pre: getSize()==M.getSize()
    Matrix sub(Matrix M){
        if(getSize() != M.getSize()){
	    throw new RuntimeException("Matrix error: sub() called on different sized matricies");
	}
	if(M == this){ //if both matricies are the same           
	    return new Matrix(getSize()); //it becomes a matrix with nothing in it
	}
	Matrix result = new Matrix(getSize()); //otherwise subtract
        for(int i = 1; i <= getSize(); i++){
	    result.row[i] = subHelp(row[i], M.row[i]);
	}
	return result;
    }

//transpose()
//returns a new Matrix that is the transpose of this Matrix
    Matrix transpose(){
	Matrix tran = new Matrix(getSize());
	for(int i = 1; i <= getSize(); i++){
	    row[i].moveFront();
	    while(row[i].index() >= 0){
		tran.changeEntry(((Element)row[i].get()).col, i, ((Element)row[i].get()).val);
		row[i].moveNext();
	    }
	}
	return tran;
    }

//mult()
//returns a new Matrix that is the product of this Matrix with M
//pre: getSize()==M.getSize()
    Matrix mult(Matrix M){
       if(getSize() != M.getSize()){
           throw new RuntimeException("Matrix error: mult() called on matricies of 2 different sizes");
       }
	   Matrix prod = new Matrix(getSize());
	   Matrix t = M.transpose();
	   for(int i = 1; i <= getSize(); i++){
	       if(row[i].length() == 0){
		   continue;
	       }
	       for(int j = 1; j <= getSize(); j++){
	           if(t.row[j].length() == 0){
		   continue;
         	   }
	           prod.changeEntry(i, j, dotProd(row[i], t.row[j]));
	       }
	   }
	   return prod;
       }

// Other functions ---------------------------------------------------

//toString()
//overrides Object's toString() method
    public String toString(){
	String str = "";
	for(int i = 1; i <= getSize(); i++){
	    if(row[i].length() > 0){
		str += (i + ": " + row[i] + "\n");
	    }
	}
	return str;
    }

// Helper functions ----------------------------------------------------

//addHelp()
//helper function for add function
    private List addHelp(List A, List B){
	List C = new List();
	A.moveFront();
	B.moveFront();
	while(A.index() >= 0 || B.index() >= 0){
	    if(A.index() >= 0 && B.index() >= 0){
		Element e = (Element) A.get();
		Element f = (Element) B.get();
		if(e.col > f.col){
		    C.append(new Element(f.col, f.val));
		    B.moveNext();
		}else if(e.col == f.col){
		    if(e.val + f.val != 0){
			C.append(new Element(e.col, e.val + f.val));
			A.moveNext();
			B.moveNext();
		    }
		}else if(A.index() >= 0){
		    C.append(new Element(e.col, e.val));
		    A.moveNext();
		}else{
		    C.append(new Element(f.col, f.val));
		    B.moveNext();
		}
	    }
	}
	return C;
    }

    //subHelp()
    //helper function for subtract function
    private List subHelp(List A, List B){ 
        List C = new List(); 
        A.moveFront();
        B.moveFront();
        while(A.index() >= 0 || B.index() >= 0){
            if(A.index() >= 0 && B.index() >= 0){
                Element e = (Element) A.get(); 
                Element f = (Element) B.get();
                if(e.col > f.col){
                    C.append(new Element(f.col, f.val));
                    B.moveNext();
                }else if(e.col == f.col){
                    if(e.val + f.val != 0){
                        C.append(new Element(e.col, e.val - f.val));
                        A.moveNext();
                        B.moveNext();
                    }
                }else if(A.index() >= 0){
                    C.append(new Element(e.col, e.val));
                    A.moveNext();
                }else{
                    C.append(new Element(f.col, f.val));
                    B.moveNext();
                }
            }
        }
	return C;
    }
		    
    private static double dotProd(List A, List B){
	double prod = 0.0;
	A.moveFront();
	B.moveFront();
	while(A.index() >= 0 && B.index() >= 0){
	    Element e = (Element) A.get();
	    Element f = (Element) B.get();
	    if(e.col < f.col){
		A.moveNext();
	    }else if(e.col > f.col){
		B.moveNext();
	    }else{
		prod += (e.val * f.val);
		A.moveNext();
		B.moveNext();
	    }
	}
	return prod;
    }
}
