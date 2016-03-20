import java.io.File;
import java.io.IOException;
import java.util.Scanner;

/**
 * This algorithm finds the optimal solution to a string breaking problem
 *
 * @author Talia Hicks
 * @author Steven Rosendahl
 * @version 03.15.2016
 *
 */
public class StringBreaking {

	public static int findBreakPoint(int n, int[] breakpoints) {
		if (breakpoints.length == 1)
			return 0;

		else {
			int median = 0;
			int minDiff = n / 2 - breakpoints[0];
			for (int i = 1; i < breakpoints.length; i++) {
				if ((n / 2 - breakpoints[i]) < minDiff) {
					minDiff = n / 2 - breakpoints[i];
					median = i;
				} // end if
			} // end for
			return median;
		}
	}

	public static int stringBreakingAlg(String s, int[] breakpoints) {
		int optsolution = 0;
		int n = s.length(); // size of string
		int breaks = breakpoints.length; // number of breakpoints

		int x = 0;

		int breakpoint = findBreakPoint(n, breakpoints);
		System.out.println("Breakpoint: " + breakpoints[breakpoint]);
		System.out.println("Cost of break: " + n);
		optsolution += n;
		System.out.println("Current total optimal cost: " + optsolution);
		breaks--;

		int breakpoint1 = breakpoint;
		int breakpoint2 = breakpoint;

		while (x <= breaks)
		{

			int[] brokenArray1 = new int[breakpoint1 + 1];
			for (int i = 0; i < brokenArray1.length; i++) {
				brokenArray1[i] = breakpoints[i];
			}//end for

			breakpoint1 = findBreakPoint(brokenArray1.length, brokenArray1);

			System.out.println("Breakpoint: " + brokenArray1[breakpoint]);
			System.out.println("Cost of break: " + brokenArray1.length);

			optsolution += brokenArray1.length;
			System.out.println("Current total optimal cost: " + optsolution);

			breaks--;

			int[] brokenArray2 = new int[n - (breakpoint2 + 1)];
            // System.out.printf("SIZE OF ARRAY: %d\n", brokenArray2.length);
			for (int i = 0; i < brokenArray2.length; i++) {
                // System.out.printf("i: %d\n", i);
				brokenArray2[i] = breakpoints[i + breakpoint - 1];
			}

			breakpoint2 = findBreakPoint(brokenArray2.length, brokenArray1);

			System.out.println("Breakpoint: " + brokenArray2[breakpoint]);
			System.out.println("Cost of break: " + n);

			optsolution += brokenArray2.length;
			System.out.println("Current total optimal cost: " + optsolution);

			breaks--;

		}

		return optsolution;

	}

	public static void main(String [] args) {
        int [] tp = {7,13,28,41,45};
        String test = "kasdklfaslhkjfhkljasdlhkfjkladfkjkjashdfjklasdhfjk";
		System.out.print("Optimal Solution: " + stringBreakingAlg(test, tp));
	}
}
