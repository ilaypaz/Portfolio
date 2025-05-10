import java.util.ArrayList;
import java.util.Collections;

// the node
public class Node {
    public int value;
    // ArrayList of references to the next nodes (which may be located at various levels)
    // next.get(i) is the next link for level i
    // the size of this ArrayList determines the number of levels that the current node is part of
    public ArrayList<Node> next; // think of this as an array of sorts, the ArrayList must have a minimum size of 1, maximum size can be MAXIMUM_ALLOWED_LEVEL_INDEX+1

    public Node(int val, int level) {
        value = val;
        next = new ArrayList<>(Collections.nCopies(level + 1, null)); // initialize ArrayList with nulls
    }
}