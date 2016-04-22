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

    private static double usAvg, sAvg;
    private static final int TRIALS = 800;
    // Change this to false if you want to see it sort the other way
    private static final boolean ASCENDING = false;

    public static void main(String[] args){
        usAvg = sAvg = 0.0;
        int cSortedBetter = 0;
        int arraySize = (args.length > 0) ? (parseInt(args[0]) > 0 ? parseInt(args[0]) : 100) : 100;
        for(int k = 0; k < TRIALS; k++){
            double aa = 0;
            double bb = 0;
            double[] sizes = new double[arraySize];
            for(int i = 0; i < arraySize; i++)
                sizes[i] = (random() * random());
            aa = bestFit(sizes);
            usAvg += aa;
            bb = sortedBestFit(sizes,ASCENDING);
            sAvg += bb;
            if(aa > bb)
                cSortedBetter++;
        }
        System.out.printf("On average, unsorted best fit used %.2f bins, sorted average used %.2f bins,\nand sorted was better than unsorted %d times out of %d runs\n", usAvg / TRIALS, sAvg / TRIALS, cSortedBetter, TRIALS);
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

    public static int bestFit(double[] sizes){
        int n = sizes.length;
        double[] used = new double[sizes.length];
        for(int i = 0; i < n; i++)
            used[i] = 0.0;
        int binsUsed = 0;
        for(int i = 0; i < n; i++){
            //loop through the array of sizes
            double leftoverSpace = 1;
            int bestBin = 0;
            for(int j = 0; j < n; j++){
                // determine the leftoever space if you put
                // that element into the bin. If you find a bin with a smaller
                // leftover space, use that bin instead
                if(used[j] + sizes[i] < 1){
                    double oldLS = leftoverSpace;
                    leftoverSpace = Math.min(leftoverSpace, 1 - sizes[i]);
                    if(oldLS != leftoverSpace){
                        bestBin = j;
                    }
                }
            }
            used[bestBin] += sizes[i];
        }
        //calculate bins used
        for(int k = 0; k < n; k++){
            if(used[k] != 0)
                binsUsed++;
        }
        return binsUsed;
    }

    public static void sortedFirstFit(double[] sizes, boolean ascending){
        sort(sizes);
        if(!ascending)
            reverseArray(sizes);
        firstFit(sizes);
    }

    public static int sortedBestFit(double[] sizes, boolean ascending){
        sort(sizes);
        if(!ascending)
            reverseArray(sizes);
        return bestFit(sizes);
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
