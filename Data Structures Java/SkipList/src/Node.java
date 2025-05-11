import java.util.ArrayList;
import java.util.List;

// The Node class
public class Node {
    public int value;
    // List of references to the next nodes (which may be at various levels)
    // next.get(i) is the next link for level i
    // the size of this list determines the number of levels that the current node is part of
    public List<Node> next;

    public Node(int val, int level) {
        this.value = val;
        this.next = new ArrayList<>(level + 1);
        // Initialize list with nulls
        for (int i = 0; i <= level; i++) {
            this.next.add(null);
        }
    }
}