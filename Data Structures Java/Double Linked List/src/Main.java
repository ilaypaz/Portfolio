public class Main {
    public static void main(String[] args) {
        Chaining hashTable = new Chaining(10, 1.0);
        hashTable.insert(1);
        hashTable.insert(13);
        hashTable.insert(13);
        hashTable.insert(31);
        hashTable.insert(19);
        hashTable.insert(17);
        hashTable.insert(1);
        hashTable.insert(14);
        hashTable.insert(10);

        hashTable.display();
        hashTable.search(10);
        hashTable.delete(10);
        hashTable.display();
    }
}