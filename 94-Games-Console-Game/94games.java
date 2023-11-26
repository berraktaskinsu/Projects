import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.io.*;
public class 94games {


// ERROR 1: 2-D ArrayList 'pass' (what if 2-D??)
//    ERROR: even on 1-D does not work!!
//    (CAUSE OF ERROR: input is pixar, found is pencil, pass is pixar( 2nd error: pixar is deleted )  ****  pencil(pixar,...) is found )
//          (IDEA: ArrayList class: 'contains' method array[index].contains)  CAN LEAD TO AN ERROR !! TRY
// ERROR 2: It should be 'pencil found' not 'pencils found'!!
//          (IDEA: a new method for finding the similar of 'input' in words2??)
//          (IDEA: or words??)
//          (IDEA: or something entirely different??)
// ERROR 3: FOR A GAME, YOU SHOULD DISPLAY THINGS :)
//
// lalala: you can improve this by writing a script to initialize faster :))))) SOOO HARD THO.. ^^'


    public static void main(String[] args) throws IOException {
        // initializing QUESTION and ANSWERS

        String question = "Things you find in a pencil case";

        ArrayList<String> words = new ArrayList();
        words.add("pencil");
        words.add("pen");
        words.add("marker");
        words.add("crayon");
        words.add("sharpener");
        words.add("eraser");
        final int numberOfWords = words.size();
        // final ArrayList<String> words2 = words;

        ArrayList<String> pass = new ArrayList<String>();
        pass.add("not found");
        pass.add("not found");
        pass.add("not found");
        pass.add("not found");
        pass.add("not found");
        pass.add("not found");

        ArrayList<Integer> percentages=  new ArrayList<Integer>(Arrays.asList(32,22,5,7,6,22));
        // percentages.add(32);
        // percentages.add(22);
        // percentages.add(5);
        // percentages.add(7);
        // percentages.add(6);
        // percentages.add(22);

        int completed = 0;
        boolean out;
        boolean out2;
        String input;
        ArrayList<String> found = new ArrayList<String>();

        Scanner scan = new Scanner(System.in);

        do {
            System.out.print(question + "\nType: ");
            input = scan.nextLine();
            out = false;
            out2 = false;

            for (int index = 0; index < words.size(); index++) {
                if ((input.equalsIgnoreCase(words.get(index))) || ((!(pass.get(index)).equals("not found")) && checkEquality(pass.get(index), input)) || checkEquality(words.get(index), input)) {
                    found.add(words.get(index));
                    completed += percentages.get(index);
                    System.out.printf("Congrats! %d completed. %d words found:\n", completed, found.size());
                    displayArrayList(found);
                    System.out.println();
                    /* removing indices: */
                    words.remove(index);
                    pass.remove(index);
                    percentages.remove(index);
                    out = true;
                    out2 = true;
                    break;
                }
            }
            if (out == false) {
                for (int i = 0; i < found.size(); i++) {
                    if (checkEquality(input, found.get(i))) {
                        System.out.printf("'%s' was already found. Try again. %d completed. %d words found:\n", input, completed, found.size());
                        displayArrayList(found);
                        System.out.println();
                        out2 = true;
                        break;
                    }
                }
            }
            if (out2 == false) {
                System.out.printf("Sorry. Try again. %d completed. %d words found:\n", completed, found.size());
                if (found.size()!=0) {
                    displayArrayList(found);
                    System.out.println();
                }
            }
        } while (found.size()!= numberOfWords);
        System.out.printf("\nCongradulations! You found all the words.\n%s: ",question);
        displayArrayList(found);
    }
    // displayArrayList method:
    public static void displayArrayList(ArrayList<String> array) {
        int index;
        for (index = 0 ; index < array.size()-1 ; index ++) {
            System.out.print(array.get(index)+", ");
        }
        System.out.print(array.get(index)+" ");
    }
    // checkEquality method:
    public static boolean checkEquality(String a,String b) {
        int similarity = 0;
        int len;
        if (a.length() == b.length()) {
            similarity += 2;
            len = a.length();
        } else {
            len = Math.min(a.length(),b.length());
        }
        for (int index = 0 ; index < len ; index ++) {
            for (int j = 0 ; j < b.length() ; j ++) {
                if (a.charAt(index)==b.charAt(j)) {
                    if (index == j)
                        similarity ++;
                    similarity ++;
                    break;
                }
            }
        }
        if (similarity > Math.max(a.length(),b.length()))
            return true;
        else
            return false;
    }
}
