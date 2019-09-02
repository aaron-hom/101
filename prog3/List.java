//List.java
//Aaron Hom
//awhom
//pa3
//List ADT that performs matrix operations

class List{

    private class Node{
        //Fields
        Object element;
        Node next;
        Node prev;

        //Constructor
        Node(Object element){
            this.element = element;
            next = null;
            prev = null;
        }

        //toString():  overrides Object's toString() method
        public String toString() {
            return element.toString();
        }

        //equals(): overrides Object's equals() method
        public boolean equals(Object x){
            boolean eq = false;
            Node that;
            if(x instanceof Node){
                that = (Node) x;
                eq = (this.element==that.element);
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
    Object front() throws RuntimeException {
        if(length <= 0){
            throw new RuntimeException("List Error: front() called on empty List");
        }else{
	    Node A = front;
	    return A.element;
        }
    }

    //back()
    //Returns back element
    //Pre: !this.isEmpty()
    Object back() throws RuntimeException {
        if(length <= 0){
            throw new RuntimeException("List Error: back() called on empty List"
				       );
        }else{
	    Node A = back;
	    return A.element;
        }
    }

    //get()
    //Returns cursor element
    //Pre: length > 0, cursorIndex != -1
    Object get() throws RuntimeException {
        if(cursorIndex > -1 && length() > 0){
            return cursor.element;
        }else if(length <= 0){
            throw new RuntimeException("List Error: get() called on empty list")
		;
        }else{
            throw new RuntimeException("List Error: get() called on undefined cursor");
        }
    }

    //equals(List L)
    //Returns true if this List and L are same object sequence, ignores cursor
    boolean equals (List L){
	if(L.length != length){
	    return false;
	}
        Node A = L.front;
        Node B = front;
            while(A != null && B != null){
                if(!A.equals(B)){
                    return false;
                }
                A = A.next;
                B = B.next;
            }
            return true;
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
    void prepend(Object element){
        Node first = new Node(element);
        if(length() <= 0){
            front = back = first;
            length++;
            cursorIndex++;

        }else{
            first.prev = null;
            first.next = front;
            front.prev = first;
            front = first;
            length++;
        }
    }

    //append()
    //Insert new element into this List. If List is non-empty,
    // insertion takes place after back element.
    void append(Object element){
        Node last = new Node(element);
        if(length <= 0){
            front = back = last;
            length++;
        }else{
            last.prev = back;
            last.next = null;
            back.next = last;
            back = last;
            length++;
        }
        cursorIndex++;
    }

    //insertBefore()
    //Insert new element before cursor.
    //Pre: length()>0, index()>=0
    void insertBefore(Object element){
        if(length <= 0 || cursorIndex < 0){
            throw new RuntimeException("List Error: insertBefore called on empty list");
        }
        Node preCursor = new Node(element);
        if(cursorIndex == 0){
            prepend(element);
        }else{
            preCursor.next = cursor;
            preCursor.prev = cursor.prev;
            cursor.prev.next = preCursor;
            cursor.prev = preCursor;
            length++;
            cursorIndex++;
        }
    }

    //insertAfter()
    //Inserts new element after cursor.
    //Pre: length()>0, index()>=0
    void insertAfter(Object element) throws RuntimeException {
        if(length <= 0 || cursorIndex < 0){
            throw new RuntimeException("List Error: insertAfter called on empty list");
        }else if(cursorIndex >= length){
            throw new RuntimeException("List Error: insertAfter called on cursor that is off the list");
        }
        Node postCursor = new Node(element);
        if(index() == length() - 1){
	    append(element);
	}else{
            postCursor.next = cursor.next;
            postCursor.prev = cursor;
            cursor.next = postCursor;
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
            L.append(tempList.element);
            tempList = tempList.next;
        }
        return L;
    }
}
