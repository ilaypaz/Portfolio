import java.util.Random;

public class TestSkip {
    public static void main(String[] args) {
        // Initialize random seed (equivalent to srand(time(0)))
        Random random = new Random(System.currentTimeMillis());

        // Set the random instance in SkipList (if needed, modify SkipList to accept Random)
        // For simplicity, SkipList already has its own Random instance

        SkipList lst = new SkipList(3); // skiplist with maximum allowed level index

        lst.insertElement(13);
        lst.insertElement(7);
        lst.insertElement(11);
        lst.insertElement(1);
        lst.insertElement(5);
        lst.insertElement(19);

        lst.insertElement(313);
        lst.insertElement(37);
        lst.insertElement(311);
        lst.insertElement(31);
        lst.insertElement(35);
        lst.insertElement(319);

        lst.show();
        lst.search(13);
        lst.delete(13);
        lst.show();
        lst.rescale(2);
        lst.show();
        lst.rescale(0);
        lst.show();
    }
}