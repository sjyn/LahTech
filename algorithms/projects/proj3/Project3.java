/**
Steven Rosendahl and Talia Hicks

You can use this program by passing in command line arguments which will test an array of that size.
If you don't pass in command line arguments, it defaults to an array of size 100.

With command line args:
java Project3 50

Without command line args:
java Project3
*/

import static java.lang.Math.*;
import static java.util.Arrays.*;
import static java.lang.Integer.*;

public class Project3 {

    public static void main(String[] args){
        int arraySize = (args.length > 0) ? parseInt(args[0]) : 100;
        double[] sizes = new double[arraySize];
        for(int i = 0; i < arraySize; i++){
            sizes[i] = (random());
        }
        firstFit(sizes);
        sortedFirstFit(sizes, false);
        sortedFirstFit(sizes, true);
    }

    public static void firstFit(double[] sizes){
        int n = sizes.length;
        double[] used = new double[sizes.length];
        for(int i = 0; i < n; i++)
            used[i] = 0.0;
        int binsUsed = 0;
        for(int i = 0; i < n; i++){
            int binLocation = 0;
            while(used[binLocation] + sizes[i] > 1)
                binLocation++;
            used[binLocation] += sizes[i];
            binsUsed = Math.max(binsUsed, binLocation);
        }
        System.out.printf("I used %d bins on an array of size %d\n", binsUsed, n);
    }

    public static void sortedFirstFit(double[] sizes, boolean ascending){
        sort(sizes);
        if(!ascending)
            reverseArray(sizes);
        firstFit(sizes);
    }

    private static void reverseArray(double[] array){
        for(int i = 0; i < array.length / 2; i++){
            double temp = array[i];
            array[i] = array[array.length - i - 1];
            array[array.length - i - 1] = temp;
        }
    }

    private static void printArray(double[] array){
        System.out.print("[");
        for(double i : array){
            System.out.print(" " + i + " ");
        }
        System.out.println("]");
    }

}
