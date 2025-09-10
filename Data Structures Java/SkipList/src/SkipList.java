import java.util.*;
import java.io.*;

// The SkipList class
public class SkipList {
    // Maximum allowed level index (the tallest level the skip list is allowed to grow to)
    private int MAXIMUM_ALLOWED_LEVEL_INDEX;

    // Current maximum level index actually in use among the inserted nodes
    private int currentHighestLevelIndex;

    // Sentinel nodes: head starts with -∞ value and tail with +∞ value
    // Each level is bounded by these head/tail nodes
    private Node head;
    private Node tail;

    // Random number generator for deciding levels when inserting
    private Random random;

    // Constructor: build an empty skip list with given max levels
    public SkipList(int maxLevels) {
        MAXIMUM_ALLOWED_LEVEL_INDEX = maxLevels;
        currentHighestLevelIndex = 0;

        // Create bottom-most sentinel nodes
        head = new Node(Integer.MIN_VALUE);
        tail = new Node(Integer.MAX_VALUE);

        // Link head and tail horizontally
        head.next = tail;
        tail.previous = head;

        random = new Random();
    }

    // Generate a random level by "flipping a coin" until tails
    private int randomLevel() {
        int lvl = 0;
        while (random.nextDouble() < 0.5 && lvl < MAXIMUM_ALLOWED_LEVEL_INDEX) {
            lvl++;
        }
        return lvl;
    }

    // Insert a new value into the skip list
    public void insertElement(int value) {
        Node[] update = new Node[MAXIMUM_ALLOWED_LEVEL_INDEX + 1];
        Node current = head;

        // Traverse from the top level down, finding insertion points
        for (int i = currentHighestLevelIndex; i >= 0; i--) {
            while (current.next != tail && current.next.value < value) {
                current = current.next;
            }
            update[i] = current;
        }

        // Choose a random level for the new node tower
        int ranLevel = randomLevel();
        if (ranLevel > currentHighestLevelIndex) {
            // If new node is taller than current skip list, extend levels
            for (int i = currentHighestLevelIndex + 1; i <= ranLevel; i++) {
                update[i] = head;

                // If head is not yet promoted, create new sentinel level
                if (head.next == tail) {
                    Node newLevelHead = new Node(Integer.MIN_VALUE);
                    Node newLevelTail = new Node(Integer.MAX_VALUE);

                    // Link new sentinels horizontally
                    newLevelHead.next = newLevelTail;
                    newLevelTail.previous = newLevelHead;

                    // Link vertically with existing head/tail
                    head.up = newLevelHead;
                    newLevelHead.down = head;
                    tail.up = newLevelTail;
                    newLevelTail.down = tail;

                    // Move head/tail pointers up
                    head = newLevelHead;
                    tail = newLevelTail;
                }
                currentHighestLevelIndex = ranLevel;
            }
        }

        // Insert the new node tower
        Node prevNode = null;
        for (int i = 0; i <= ranLevel; i++) {
            // Create the node for this level
            Node newNode = new Node(value);

            // Link horizontally
            newNode.next = update[i].next;
            newNode.previous = update[i];
            update[i].next.previous = newNode;
            update[i].next = newNode;

            // Link vertically to previous level of the tower
            if (prevNode != null) {
                newNode.down = prevNode;
                prevNode.up = newNode;
            }
            prevNode = newNode;
        }
    }

    // Delete a value from the skip list
    public void delete(int value) {
        Node current = head;
        Node[] update = new Node[MAXIMUM_ALLOWED_LEVEL_INDEX + 1];

        // Find nodes that need to update their links
        for (int i = currentHighestLevelIndex; i >= 0; i--) {
            while (current.next != tail && current.next.value < value) {
                current = current.next;
            }
            update[i] = current;
        }

        // Move to candidate node
        current = current.next;

        if (current != tail && current.value == value) {
            // Remove links on each level
            for (int i = 0; i <= currentHighestLevelIndex; i++) {
                if (update[i].next != current) break;
                update[i].next = current.next;
                current.next.previous = update[i];
            }

            // Clear vertical connections for garbage collection
            while (current != null) {
                Node temp = current;
                current = current.up;
                temp.next = null;
                temp.previous = null;
                temp.up = null;
                temp.down = null;
            }

            // Adjust currentHighestLevelIndex if upper levels are empty
            while (currentHighestLevelIndex > 0 && head.next == tail) {
                head = head.down;
                tail = tail.down;
                head.up = null;
                tail.up = null;
                currentHighestLevelIndex--;
            }
        } else {
            System.out.println(value + " is not found in the skip list.");
        }
    }

    // Search for a value in the skip list from the left side
    public boolean search(int value) {
        Node current = head;
        for (int i = currentHighestLevelIndex; i >= 0; i--) {
            while (current.next != tail && current.next.value < value) {
                current = current.next;
            }
        }
        current = current.next;
        return current != tail && current.value == value;
    }

    // Search for a value in the skip list from the right side
    public boolean searchFromRight(int value) {
        Node current = tail;
        for (int i = currentHighestLevelIndex; i >= 0; i--) {
            while (current.previous != head && current.previous.value > value) {
                current = current.previous;
            }
        }
        current = current.previous;
        return current != head && current.value == value;
    }

    // Count odd numbers between x and y (inclusive)
    public int countOddInRange(int x, int y) {
        if (x > y) {
            int temp = x;
            x = y;
            y = temp;
        }
        int count = 0;
        Node current = head.next;
        while (current != tail && current.value < x) {
            current = current.next;
        }
        while (current != tail && current.value <= y) {
            if (current.value % 2 != 0) count++;
            current = current.next;
        }
        return count;
    }

    // Save the skip list to a file
    public void saveToFile(String filename) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            writer.write(String.valueOf(currentHighestLevelIndex));
            writer.newLine();
            Node current = head.next;
            while (current != tail) {
                int level = 0;
                Node temp = current;
                while (temp != null) {
                    level++;
                    temp = temp.up;
                }
                writer.write(current.value + "," + (level - 1));
                writer.newLine();
                current = current.next;
            }
        }
    }

    // Load a skip list from a file
    public void loadFromFile(String filename) throws IOException {
        // Clear existing skip list
        for (int i = 0; i <= currentHighestLevelIndex; i++) {
            head.next = tail;
            tail.previous = head;
        }
        currentHighestLevelIndex = 0;

        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line = reader.readLine();
            if (line != null) {
                MAXIMUM_ALLOWED_LEVEL_INDEX = Integer.parseInt(line);
                head = new Node(Integer.MIN_VALUE);
                tail = new Node(Integer.MAX_VALUE);
                head.next = tail;
                tail.previous = head;
            }
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                int value = Integer.parseInt(parts[0]);
                int level = Integer.parseInt(parts[1]);
                for (int i = 0; i <= level; i++) {
                    insertElement(value);
                }
            }
        }
    }

    // Find common and unique elements between two skip lists
    public void findCommonAndUnique(SkipList other, List<Integer> common, List<Integer> unique) {
        Node current1 = this.head.next;
        Node current2 = other.head.next;
        while (current1 != this.tail && current2 != other.tail) {
            if (current1.value == current2.value) {
                common.add(current1.value);
                current1 = current1.next;
                current2 = current2.next;
            } else if (current1.value < current2.value) {
                unique.add(current1.value);
                current1 = current1.next;
            } else {
                unique.add(current2.value);
                current2 = current2.next;
            }
        }
        while (current1 != this.tail) {
            unique.add(current1.value);
            current1 = current1.next;
        }
        while (current2 != other.tail) {
            unique.add(current2.value);
            current2 = current2.next;
        }
    }

    // Merge another skip list into this one
    public void merge(SkipList other) {
        Node current = other.head.next;
        while (current != other.tail) {
            insertElement(current.value);
            current = current.next;
        }
    }

    // Rescale the skip list to a new maximum level index
    public void rescale(int newMaxLevelIndex) {
        if (newMaxLevelIndex < 0) {
            System.out.println("Invalid new maximum level index.");
            return;
        }
        if (newMaxLevelIndex < currentHighestLevelIndex) {
            // Shrink levels
            while (currentHighestLevelIndex > newMaxLevelIndex) {
                head = head.down;
                tail = tail.down;
                head.up = null;
                tail.up = null;
                currentHighestLevelIndex--;
            }
        } else if (newMaxLevelIndex > currentHighestLevelIndex) {
            // Grow levels
            for (int i = currentHighestLevelIndex + 1; i <= newMaxLevelIndex; i++) {
                Node newLevelHead = new Node(Integer.MIN_VALUE);
                Node newLevelTail = new Node(Integer.MAX_VALUE);
                newLevelHead.next = newLevelTail;
                newLevelTail.previous = newLevelHead;
                head.up = newLevelHead;
                newLevelHead.down = head;
                tail.up = newLevelTail;
                newLevelTail.down = tail;
                head = newLevelHead;
                tail = newLevelTail;
            }
            currentHighestLevelIndex = newMaxLevelIndex;
        }
        MAXIMUM_ALLOWED_LEVEL_INDEX = newMaxLevelIndex;
    }

    // Display skip list level by level
    public void show() {
        Node levelHead = head;
        for (int i = currentHighestLevelIndex; i >= 0; i--) {
            System.out.print("Level " + i + ": ");
            Node node = levelHead.next;
            while (node != tail) {
                System.out.print(node.value + " -> ");
                node = node.next;
            }
            System.out.println(".");
            levelHead = levelHead.down;
        }
    }
}
