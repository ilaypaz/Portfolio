import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class SkipList {
    // Maximum allowed level index
    private int MAXIMUM_ALLOWED_LEVEL_INDEX; // maximum you will allow the skip list to grow to

    // current maximum level amongst the inserted nodes
    private int currentHighestLevelIndex; // traces how many levels you have created and what within the skip list is the highest level

    // the head node's next links are connected to the first node at every level
    Node head;

    private Random random;

    public SkipList(int maxLevels) {
        MAXIMUM_ALLOWED_LEVEL_INDEX = maxLevels; // how high up can you tolerate the coin flipping

        // initially we have the bottom-most level only
        currentHighestLevelIndex = 0;

        // create the header node, value is irrelevant (as long as it doesn't match an inserted value - NO REPEATS)
        head = new Node(Integer.MIN_VALUE, MAXIMUM_ALLOWED_LEVEL_INDEX);

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
        ArrayList<Node> update = new ArrayList<>(Collections.nCopies(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, null)); // this will hold the nodes that need updating at every level after the insert takes place
        /*O(log n)*/ for (int i = currentHighestLevelIndex; i >= 0; i--) {
            // for level i, if value is to be inserted here then find out where (i.e. after which node)
            while (current.next.get(i) != null && current.next.get(i).value < value) {
                current = current.next.get(i);
            }
            // found the node after which the value is to be placed at level i, move down a level, if possible
            update.set(i, current);
        }

        // at level 0, move over one node to where the value is to be inserted to see if the value already exists
        current = current.next.get(0);

        if (current == null || current.value != value) { // eliminate duplicate or check if it is empty
            int ranLevel = randomLevel(); // choose a random level up to where the new node will be placed

            if (ranLevel > currentHighestLevelIndex) {
                // if random level for current node is higher than the current maximum level
                for (int i = currentHighestLevelIndex + 1; i <= ranLevel; i++) {
                    update.set(i, head); // put head on existing current levels
                }
                // also change the current maximum level for the existing nodes
                currentHighestLevelIndex = ranLevel;
            }

            // create new node with next links for every level from ranLevel to zero
            Node n = createNode(value, ranLevel);

            // placing new node in the correct place at every level
            for (int i = 0; i <= ranLevel; i++) {
                n.next.set(i, update.get(i).next.get(i)); // nodes next is null
                update.get(i).next.set(i, n); // previous will point to the thing we are adding
            }
        }
    }

    public void delete(int value) {
        Node current = head; // start at head node
        ArrayList<Node> update = new ArrayList<>(Collections.nCopies(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, null)); // this will hold the nodes that need updating at every level
        /*O(log n)*/ for (int i = currentHighestLevelIndex; i >= 0; i--) {
            // for level i, if value is to be deleted here then find out where (the node before the node we want)
            while (current.next.get(i) != null && current.next.get(i).value < value) {
                current = current.next.get(i);
            }
            // found the node after which the value is to be placed at level i, move down a level, if possible
            update.set(i, current);
        }
        // at level 0, move over one node to where the value is to be deleted
        current = current.next.get(0);
        if (current != null && current.value == value) { // check if the value exists
            for (int i = 0; i <= currentHighestLevelIndex; i++) {
                if (update.get(i).next.get(i) != current) { // iterate through the level for node you want to delete
                    break; // Stop if node doesn't exist on this level
                }
                update.get(i).next.set(i, current.next.get(i)); // iterate by changing the pointer
            }

            while (currentHighestLevelIndex > 0 && head.next.get(currentHighestLevelIndex) == null) { // checking the higher levels
                currentHighestLevelIndex--;
            }

            current = null; // Java garbage collection handles memory deallocation
        } else {
            System.out.println(value + " is not found in the skip list.");
        }
    }

    public boolean search(int value) {
        Node current = head;

        for (int i = currentHighestLevelIndex; i >= 0; i--) { // start at the highest level and move down
            // for level i, if value is to be searched here then find out where
            while (current.next.get(i) != null && current.next.get(i).value < value) {
                current = current.next.get(i);
            }
        }
        // at level 0, move over one node to where the value is to be searched
        current = current.next.get(0); // eliminate duplicate or check if it is empty

        // Check if the value exists
        return current != null && current.value == value; // return true if current has a value and the value in current is equal to the one you inputted
    }

    public void rescale(int newMaxLevelIndex) {
        if (newMaxLevelIndex < 0) {
            System.out.println("Invalid new maximum level index.");
            return;
        }

        ArrayList<Integer> skipListValues = new ArrayList<>(); // creating a list
        Node current = head.next.get(0); // Start from the start of the list
        while (current != null) {
            skipListValues.add(current.value); // add the node value to the list
            current = current.next.get(0); // iterating through skiplist
        }
        for (int i = 0; i <= currentHighestLevelIndex; i++) { // clear the current skip list
            head.next.set(i, null); // by setting everything to null
        }
        currentHighestLevelIndex = 0; // because the list doesn't exist
        MAXIMUM_ALLOWED_LEVEL_INDEX = newMaxLevelIndex; // pretty self-explanatory
        for (int value : skipListValues) { // for loop iterating through the list of all the elements of the skip list
            insertElement(value); // inserting the items from the list using the insert method
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