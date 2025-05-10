import java.util.ArrayList;

public class Chaining {
    private ArrayList<SkipList> hashTable;
    private int hashTableSize;
    private double loadFactorThreshold;
    private int numberOfKeys;

    private int hashFunction(int value) {
        // Java's built-in hashCode for integers is the value itself
        int hashCode = Integer.hashCode(value); // Generate a unique hash code for the value
        int hindex = Math.abs(hashCode % hashTableSize); // Calculate the index using mod operation, ensure non-negative
        return hindex;
    }

    public Chaining(int size, double threshold) {
        hashTableSize = size;
        loadFactorThreshold = threshold;
        numberOfKeys = 0;
        hashTable = new ArrayList<>(size);
        for (int i = 0; i < size; i++) {
            hashTable.add(new SkipList(3));
        }
    }

    public void insert(int value) { // insert a value into the hash table
        if (value == 0) { // if user tries 0, give an error
            System.out.println("0 not allowed");
            return;
        }

        // Check if the load factor threshold is exceeded
        if ((numberOfKeys + 1) / (double)hashTableSize > loadFactorThreshold) { // rehash if needed
            reHash();
        }

        int index = hashFunction(value); // find where to place the int

        // Only insert if the value does not already exist at the calculated index
        if (!hashTable.get(index).search(value)) {
            hashTable.get(index).insertElement(value); // Insert into the correct index's skip list
            numberOfKeys++; // Increase.ConcurrentHashMap$Node@7f690630 the number of keys
        } else {
            System.out.println(value + " already exists in the hash table.");
        }
    }

    public void delete(int value) {
        int index = hashFunction(value); // tell you where to start looking for the item you want to delete
        if (hashTable.get(index).search(value)) {
            hashTable.get(index).delete(value);
            numberOfKeys--;
        }
    }

    public boolean search(int value) {
        int index = hashFunction(value);
        return hashTable.get(index).search(value);
    }

    private void reHash() {
        int newSize = hashTableSize * 2;
        ArrayList<SkipList> newHashTable = new ArrayList<>(newSize);
        for (int i = 0; i < newSize; i++) {
            newHashTable.add(new SkipList(3));
        }

        for (int i = 0; i < hashTableSize; i++) {
            Node current = hashTable.get(i).head.next.get(0); // add the old nodes back to
            while (current != null) {
                int newIndex = Math.abs(current.value % newSize);
                newHashTable.get(newIndex).insertElement(current.value);
                current = current.next.get(0);
            }
        }

        hashTable = newHashTable;
        hashTableSize = newSize;
    }

    public void display() {
        for (int i = 0; i < hashTableSize; i++) {
            System.out.println("Index " + i + ": ");
            hashTable.get(i).show();
        }
        System.out.println("Current Table Size: " + hashTableSize);
        System.out.println("Number of Keys: " + numberOfKeys);
        System.out.println("Current Load Factor: " + (double)numberOfKeys / hashTableSize);
        System.out.println("Load Factor Threshold: " + loadFactorThreshold);
    }
}