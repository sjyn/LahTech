/*
 Compute maximum revenue using dynamic programming
 */

public class CutRod {
	//array of prices
	static int [] p = {0,1,5,8,9,10,17,17,20,24,30};
    //cost per cut
    static int cost = 1;

	static int cut_rod(int n){
        //initially, there are no cuts
        int numCuts = 0;
		//r[i] is maximum possible revenue from rod of length i
		int [] r = new int[n+1];
		r[0] = 0; //trivial initial condition
		int q;
		//use r[0] to get r[1]; use r[0..1] to get r[2], use r[0..2] to get r[3] ......
		for (int j = 1; j <= n; j++){
            q = p[j];
			for(int i = 1; i <= j; i++){
				q = Math.max(q, p[i] + r[j - i] - cost); //maximize p[i] + r[j-i]
			}
			r[j] = q;
		}
        return r[n];
	}

	public static void main(String[] args){
		int n = (args.length > 0) ? Integer.parseInt(args[0]) : 3;
        //For n = 3, we expect the max revenue to be $8
        //For n = 4, we expect the max revenue to be $9
		System.out.println("Maximum revenue: " + cut_rod( n ));
	}


}
