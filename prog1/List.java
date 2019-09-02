//List.java
//Aaron Hom
//pa1
//A list ADT that will sort words in files alphabetically

class List{

    private class Node{
	//Fields
	int data;
	Node next;
	Node prev;
      
	//Constructor
	Node(int data){
            this.data = data;
            next = null;
            prev = null;
        }
      
	//toString():  overrides Object's toString() method
	public String toString() { 
	    return String.valueOf(data); 
	}
      
	//equals(): overrides Object's equals() method
	public boolean equals(Object x){
	    boolean eq = false;
	    Node that;
	    if(x instanceof Node){
		that = (Node) x;
		eq = (this.data==that.data);
	    }
	    return eq;
	}
    }

    //Fields
    private Node front;
    private Node back;
    private Node cursor;
    private int length;
    private int cursorIndex;

    //Constructor
    public List() { 
	front = null;
        back = null;   
        cursor = null; 
	length = 0; 
	cursorIndex = -1;
    }

    //Access Functions --------------------------------------------------------
    
    //length()
    //Returns length of this Queue.
    int length() { 
	return length; 
    }

    //index()
    //If cursor is defined, returns index of cursor element, otherwise returns -1
    int index() {
        return cursorIndex;
    }

    //front() 
    //Returns front element
    //Pre: !this.isEmpty()
    int front() throws RuntimeException {
	if(length <= 0){
	    throw new RuntimeException("List Error: front() called on empty List");
	}else{
	Node A = front;
	return A.data; 
	}
    }

    //back()
    //Returns back element
    //Pre: !this.isEmpty()
    int back() throws RuntimeException {
	if(length <= 0){
	    throw new RuntimeException("List Error: back() called on empty List");
        }else{
	Node A = back;
	return A.data; 
	}    
    }

    //get()
    //Returns cursor element
    //Pre: length > 0, cursorIndex != -1
    int get() throws RuntimeException {
	if(cursorIndex > -1 && length() > 0){
            return cursor.data; 
	}else if(length <= 0){
	    throw new RuntimeException("List Error: get() called on empty list");
	}else{
	    throw new RuntimeException("List Error: get() called on undefined cursor");
	}
    }

    //equals(List L)
    //Returns true if this List and L are same integer sequence, ignores cursor
    boolean equals (List L){
	boolean t = true;
	Node A = L.front; 
	Node B = front;
	if(this.length == L.length){ 
	    while(A.next != null && B.next != null){ 
		if(!A.equals(B)){
		    return false;
		}
 		A = A.next; 
		B = B.next;
	    }
	    return true; 
	}
	return false;
    }
	
    // Manipulation Procedures -------------------------------------------------

    //clear()
    //resets list to empty state
    void clear(){
	front = null;
        back = null;
        cursor = null; 
	length = 0; 
	cursorIndex = -1; 
    }

    //moveFront()
    //if list is not empty, places cursor under front element, otherwise does nothing
    void moveFront(){
        Node A = front;  
	if(A != null){
	    cursorIndex = 0;
	    cursor = front;
	}
    }
    //moveBack()
    //if list is not empty, places cursor under back element, otherwise does nothing 
    void moveBack(){
	Node A = back;
	if(A != null){
	    cursor = back;
	    for(int i = 0; i < length(); i++){
		cursorIndex= length() - 1;
		cursor = back;
	    }
	}
    }

    //movePrev()
    // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void movePrev(){
	if(cursor.prev != null){
	    cursor = cursor.prev;
	    cursorIndex--;
	}else{
	    cursorIndex = -1;
	    cursor = null;
	}
    }

    //moveNext
    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void moveNext(){
	if(cursor.next != null){
	    cursor = cursor.next;
	    cursorIndex++;
	}else{
	    cursorIndex = -1;
	    cursor = null;
	}
    }

    //prepend()
    // Insert new element into this List. If List is non-empty,
    // insertion takes place before front element.
    void prepend(int data){ 
        Node element = new Node(data);
	if(length() <= 0){
	    front = back = element;
	    length++;
	    cursorIndex++;

	}else{ 
	    element.prev = null;
	    element.next = front;
	    front.prev = element;
	    front = element;
	    length++;
	}
    }

    //append()
    //Insert new element into this List. If List is non-empty,
    // insertion takes place after back element.
    void append(int data){
	Node element = new Node(data);
        if(length <= 0){
            front = back = element;
            length++;
        }else{
	    element.prev = back;
            element.next = null;
	    back.next = element;
	    back = element;
            length++;
        }
	cursorIndex++;
    }

    //insertBefore()
    //Insert new element before cursor.
    //Pre: length()>0, index()>=0
    void insertBefore(int data){
	if(length <= 0 || cursorIndex < 0){
            throw new RuntimeException("List Error: insertBefore called on empty list");
        }
	Node element = new Node(data);
        if(cursorIndex == 0){
            prepend(data);
	}else{
	    element.next = cursor;
	    element.prev = cursor.prev;
	    cursor.prev.next = element;
	    cursor.prev = element;
	    length++;
	    cursorIndex++;
	}
    }

    //insertAfter()
    //Inserts new element after cursor.
    //Pre: length()>0, index()>=0
    void insertAfter(int data) throws RuntimeException {
	if(length <= 0 || cursorIndex < 0){
	    throw new RuntimeException("List Error: insertAfter called on empty list");
	}else if(cursorIndex >= length){
	    throw new RuntimeException("List Error: insertAfter called on cursor that is off the list");
	}
	Node element = new Node(data);
	if(index() == length() - 1){
		append(data);
	    }else{
            element.next = cursor.next;
	    element.prev = cursor;
	    cursor.next = element;
	    cursorIndex++;
            length++;
	}
    }

    //deleteFront()
    //Deletes the front element. Pre: length()>0
    void deleteFront() throws RuntimeException{
	if(length <= 0){
	    throw new RuntimeException("List Error: deleteFront() called on empty list");
	}else{
	    front = front.next;
	    length--;
	}
    }
    //deleteBack()
    //Deletes the back element. Pre: length()>0
    void deleteBack(){
	if(length <= 0){
            throw new RuntimeException("List Error: deleteBack() called on empty list");
        }else{
            cursor = back;
	    back = back.prev;
            length--;
	}
    }
    
    //delete()
    //Deletes cursor element, making cursor undefined.
    // Pre: length()>0, index()>=0
    void delete() throws RuntimeException{
	if(length() <= 0 || cursorIndex < 0){
	    throw new RuntimeException("List Error: delete() called on empty list");
	}else{
	    cursor.prev.next = cursor.next;
	    cursor.next = cursor.prev;
	    cursor = null;
	    cursorIndex = -1;
	    length--;
	}
    }
    //Other Functions ---------------------------------------------------------

    //toString()
    //Overides List's toString() method.
    public String toString(){
	Node A = front;
	String str ="";
	while(A != null){
	    str +=  A.toString() + " ";
	    A = A.next;
	}
	return str;
    }

    //List copy()
    // Returns a new List representing the same integer sequence as this
    // List. The cursor in the new list is undefined, regardless of the
    // state of the cursor in this List. This List is unchanged.
    List copy(){
	List L = new List();
	Node tempList = front;
	while(tempList != null){
	    L.append(tempList.data);
	    tempList = tempList.next;
	}
	return L;
    } 
}
