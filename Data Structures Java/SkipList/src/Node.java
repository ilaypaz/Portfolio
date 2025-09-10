public class Node {
    // The value stored at this node
    public int value;

    // Horizontal links for the doubly-linked list at a given level
    public Node next;     // Reference to the next node on the same level
    public Node previous; // Reference to the previous node on the same level

    // Vertical links that connect the same value across levels in the skip list
    public Node up;       // Reference to the node above (higher level)
    public Node down;     // Reference to the node below (lower level)

    // Constructor: create a node with the given value
    // All references start as null
    public Node(int val) {
        this.value = val;
        this.next = null;
        this.previous = null;
        this.up = null;
        this.down = null;
    }
}
