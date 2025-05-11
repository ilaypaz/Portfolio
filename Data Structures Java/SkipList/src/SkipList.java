import java.util.ArrayList;
import java.util.List;
import java.util.Random;

// The SkipList class
public class SkipList {
    // Maximum allowed level index
    private int MAXIMUM_ALLOWED_LEVEL_INDEX; // maximum you will allow the skip list to grow to

    // current maximum level amongst the inserted nodes
    private int currentHighestLevelIndex; // traces how many levels you have created and what within the skip list is the highest level

    // the head node's next links are connected to the first node at every level
    private Node head;

    // Random number generator for level selection
    private Random random;

    public SkipList(int maxLevels) {
        MAXIMUM_ALLOWED_LEVEL_INDEX = maxLevels; // how high up can you tolerate the coin flipping

        // initially we have the bottom-most level only
        currentHighestLevelIndex = 0;

        // create the header node, value is irrelevant (as long as it doesn't match an inserted value - NO REPEATS)
        head = new Node(Integer.MIN_VALUE, MAXIMUM_ALLOWED_LEVEL_INDEX);

        // Initialize random number generator
        random = new Random();
    }

    private int randomLevel() {
        float probability = random.nextFloat(); // flip a coin
        int lvl = 0;
        while (probability < 0.5 && lvl < MAXIMUM_ALLOWED_LEVEL_INDEX) {
            lvl++; // landed heads so increase level by 1
            probability = random.nextFloat(); // flip a coin again
        }
        return lvl;
    }

    private Node createNode(int value, int level) {
        // create a new node with next links for every level that this node will be part of
        return new Node(value, level);
    }

    public void insertElement(int value) { // this is the insert method
        Node current = head; // start at head node
        List<Node> update = new ArrayList<>(MAXIMUM_ALLOWED_LEVEL_INDEX + 1);
        // Initialize update list with nulls
        for (int i = 0; i <= MAXIMUM_ALLOWED_LEVEL_INDEX; i++) {
            update.add(null);
        }

        /*O(log n)*/ for (int i = currentHighestLevelIndex; i >= 0; i--) {
            // for level i, if value is to be inserted here then find out where (i.e. after which node)
            while (current.next.get(i) != null && current.next.get(i).value < value) {
                current = current.next.get(i);
            }
            // found the node after which the value is to be placed at level i
            update.set(i, current);
        }

        // at level 0, move over one node to where the value is to be inserted
        current = current.next.get(0);

        if (current == null || current.value != value) { // eliminate duplicates
            int ranLevel = randomLevel(); // choose a random level

            if (ranLevel > currentHighestLevelIndex) {
                // set head as the node after which the new value is to be inserted for new levels
                for (int i = currentHighestLevelIndex + 1; i <= ranLevel; i++) {
                    update.set(i, head);
                }
                // update the current maximum level
                currentHighestLevelIndex = ranLevel;
            }

            // create new node with next links for every level from ranLevel to zero
            Node n = createNode(value, ranLevel);

            // placing new node in the correct place at every level
            for (int i = 0; i <= ranLevel; i++) {
                n.next.set(i, update.get(i).next.get(i)); // node's next is set
                update.get(i).next.set(i, n); // previous node points to new node
            }
        }
    }

    public void delete(int value) {
        Node current = head; // start at head node
        List<Node> update = new ArrayList<>(MAXIMUM_ALLOWED_LEVEL_INDEX + 1);
        // Initialize update list with nulls
        for (int i = 0; i <= MAXIMUM_ALLOWED_LEVEL_INDEX; i++) {
            update.add(null);
        }

        /*O(log n)*/ for (int i = currentHighestLevelIndex; i >= 0; i--) {
            // find the node before the one to delete
            while (current.next.get(i) != null && current.next.get(i).value < value) {
                current = current.next.get(i);
            }
            update.set(i, current);
        }

        // at level 0, move to the node to be deleted
        current = current.next.get(0);

        if (current != null && current.value == value) {
            for (int i = 0; i <= currentHighestLevelIndex; i++) {
                if (update.get(i).next.get(i) != current) {
                    break; // stop if node doesn't exist on this level
                }
                update.get(i).next.set(i, current.next.get(i)); // bypass the node
            }

            // reduce levels if necessary
            while (currentHighestLevelIndex > 0 && head.next.get(currentHighestLevelIndex) == null) {
                currentHighestLevelIndex--;
            }
        } else {
            System.out.println(value + " is not found in the skip list.");
        }
    }

    public boolean search(int value) {
        Node current = head;

        for (int i = currentHighestLevelIndex; i >= 0; i--) {
            // for level i, search for the value
            while (current.next.get(i) != null && current.next.get(i).value < value) {
                current = current.next.get(i);
            }
        }

        // at level 0, move to the candidate node
        current = current.next.get(0);

        // check if the value exists
        return current != null && current.value == value;
    }

    public void rescale(int newMaxLevelIndex) {
        if (newMaxLevelIndex < 0) {
            System.out.println("Invalid new maximum level index.");
            return;
        }

        List<Integer> skipListValues = new ArrayList<>();
        Node current = head.next.get(0); // start from the first node
        while (current != null) {
            skipListValues.add(current.value); // collect all values
            current = current.next.get(0);
        }

        // clear the current skip list
        for (int i = 0; i <= currentHighestLevelIndex; i++) {
            head.next.set(i, null);
        }

        currentHighestLevelIndex = 0;
        MAXIMUM_ALLOWED_LEVEL_INDEX = newMaxLevelIndex;

        // reinsert all values
        for (int value : skipListValues) {
            insertElement(value);
        }
    }

    public void show() {
        for (int i = 0; i <= currentHighestLevelIndex; i++) {
            Node node = head.next.get(i);
            System.out.print("Level " + i + ": ");
            while (node != null && node.next.get(i) != null) {
                System.out.print(node.value + " -> ");
                node = node.next.get(i);
            }
            if (node != null) {
                System.out.println(node.value + " .");
            } else {
                System.out.println(".");
            }
        }
    }
}