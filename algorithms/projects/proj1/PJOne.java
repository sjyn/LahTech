// Test Review
//
// Big theta, O, Omega
// Logs, Exponents, n!
// Summations
// Master Theorem
// Sorting and Searching up to Count Sort
//      - Running times
//      - Pseudocode
//      - Recursion Trees
// Analyze an algorithm.


import static java.lang.System.out;

public class PJOne {

    public static void algoOne(int[] a){
        int INST_COUT = 0;
        //Begin counting instructions
        int n = a.length;
        int j = 1;
        int[] b = new int[n];
        while(j <= n - 1){
            INST_COUT++;
            int i = 1;
            while(i <= n - j){
                INST_COUT++;
                int m = i + j - 1;
                int r = min(m + j, n);
                int u = i;
                for(; u < r; u++){
                    INST_COUT++;
                    b[u - 1] = a[u - 1];
                }
                u = i;
                int v = m + 1;
                int w = i;
                for(; w < r; w++){
                    INST_COUT++;
                    if((u > m) || (v <= r && b[v - 1] < b[u - 1])){
                        INST_COUT++;
                        a[w - 1] = b[v - 1];
                        v++;
                    } else {
                        INST_COUT++;
                        a[w - 1] = b[u - 1];
                        u++;
                    }
                }
                i = i + (2 * j);
            }
            j *= 2;
        }
        out.println(INST_COUT);
    }

    public static void compute(int[] a, int[] b, int i){
        if(i > a.length - 1){
            for(int j = i; j < a.length - 1; j++){
                if(b[j] > 0){
                    out.println(b[j]);
                }
            }
            return;
        }
        b[i] = 0;
        compute(a,b,i + 1);
        b[i] = a[i];
        compute(a,b,i + 1);
        b[i] = 0;
    }

    private static int min(int a, int b){
        return a < b ? a : b;
    }

    public static void main(String[] args){
        int [] a = new int[]{-12,-12,-55,0,-16,-189, -42, -98};
        // for(int aa : a)
            // out.printf("%6d", aa);
        // out.println();
        algoOne(a);
        // for(int aa : a)
        //     out.printf("%6d",aa);
        // out.println();
    }
}
