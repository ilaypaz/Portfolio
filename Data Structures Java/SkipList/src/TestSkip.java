import java.util.ArrayList;
import java.util.List;
import java.io.IOException;

public class TestSkip {
    public static void main(String[] args) {
        // Create two skip lists with maximum allowed level index 3
        SkipList lst1 = new SkipList(3);
        SkipList lst2 = new SkipList(3);

        // ==== Test insert with repeated values ====
        lst1.insertElement(13);
        lst1.insertElement(7);
        lst1.insertElement(7); // Insert repeated value
        lst1.insertElement(11);
        lst1.insertElement(1);
        lst1.insertElement(5);
        lst1.insertElement(19);
        System.out.println("List 1 after insertions:");
        lst1.show();

        // Insert into the second list
        lst2.insertElement(7);
        lst2.insertElement(11);
        lst2.insertElement(15);
        lst2.insertElement(19);
        System.out.println("List 2 after insertions:");
        lst2.show();

        // ==== Test search from right ====
        System.out.println("Search from right (7): " + lst1.searchFromRight(7));
        System.out.println("Search from right (100): " + lst1.searchFromRight(100));

        // ==== Test count odd in range ====
        System.out.println("Odd numbers between 5 and 13: " + lst1.countOddInRange(5, 13));

        // ==== Test save and load from file ====
        try {
            // Save lst1 to file
            lst1.saveToFile("skiplist.txt");

            // Load into a new skip list
            SkipList loadedList = new SkipList(3);
            loadedList.loadFromFile("skiplist.txt");

            System.out.println("Loaded list:");
            loadedList.show();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // ==== Test common and unique items ====
        List<Integer> common = new ArrayList<>();
        List<Integer> unique = new ArrayList<>();
        lst1.findCommonAndUnique(lst2, common, unique);

        System.out.println("Common items: " + common);
        System.out.println("Unique items: " + unique);

        // ==== Test merge operation ====
        lst1.merge(lst2);
        System.out.println("List 1 after merging with List 2:");
        lst1.show();

        // ==== Test delete operation ====
        lst1.delete(7);
        System.out.println("List 1 after deleting 7:");
        lst1.show();

        // ==== Test rescale operation ====
        lst1.rescale(2);
        System.out.println("List 1 after rescaling to max level 2:");
        lst1.show();
    }
}
