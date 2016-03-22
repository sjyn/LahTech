/**
* Talia Hicks and Steven Rosendahl
*
*/

import java.util.Arrays;
import java.io.File;
import java.io.IOException;
import java.util.Collections;
import java.util.Scanner;

public class StringSplit {

    static int stringlength;
	static int[] optcuts;
	static int[] breakpoints;
    static int optCutsCount;

    public static void readFile(File input) {
		try {
			Scanner scanner = new Scanner(input); // read in file
			stringlength = scanner.nextInt(); // set string size
			int breaks = scanner.nextInt(); // set number of breakpoints
			breakpoints = new int[breaks]; // Initialize size of array
			for (int i = 0; i < breakpoints.length; i++) {
				breakpoints[i] = scanner.nextInt(); // set break points
			} // end while
			scanner.close();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}

    public static int splitString(int n, int[] cuts){
        Arrays.sort(cuts);
        optcuts = new int[cuts.length];
        optCutsCount = 0;
        int cost = n * cuts.length;
        // int prevcost = 0;
        int nval = 0;
        for(int i = 0; i < cuts.length; i++){
            cost = Math.min(nval = splitStringRec(cuts, n, i), cost);
        }
        return cost;
    }

    public static int splitStringRec(int[] cuts, int stringlen, int init){
        if(cuts.length == 1){
            return stringlen;
        }
        int cutlen = 0;
        int cutr = 0;
        if (init > 0){
            //run as normal
            cutlen = Integer.MAX_VALUE;
            int[] cpy = Arrays.copyOfRange(cuts, 0, init);
            int first = cuts[init];
            int pcl;
            for(int j = 0; j < cpy.length; j++){
                // System.out.println("Trying to make a cut " + cutlen);
                cutlen = Math.min(pcl = splitStringRec(cpy, first, j), cutlen);
                // System.out.println("Making a cut of cost " + cutlen);
                if(cutlen <= stringlen){
                    System.out.println("Making a cut on the left side of cost " + cutlen);
                }
            }
        }
        if (init < cuts.length - 1){
            cutr = Integer.MAX_VALUE;
            int[] cpy = Arrays.copyOfRange(cuts, init + 1, cuts.length);
            int newcost = stringlen - cuts[init];
            for(int i = 0; i < cpy.length; i++){
                cpy[i] = cpy[i] - cuts[init];
            }
            for(int i = 0; i < cpy.length; i++){
                cutr = Math.min(splitStringRec(cpy, newcost, i), cutr);
                if(cutr < stringlen){
                    System.out.println("Making a cut on the right side of cost " + cutr);
                }
            }
        }
        return stringlen + cutlen + cutr;
    }

    public static void main(String[] args){
        // File myfile = new File("/Users/taliahicks/Desktop/CPSC420/StringBreaking/bin/sol.txt");
        File myfile = new File("sol.txt");
        readFile(myfile);
        int res = splitString(stringlength, breakpoints);
        // Should get that the cost is 122
        System.out.println("The cost of splitting the string of length " + stringlength + " is " + res);
    }

}
