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

    private static int COUNT_TWO = 0;

    public static void algoOne(int[] a){
        int INST_COUT = 0;
        //Begin counting instructions
        int n = a.length;
        int j = 1;
        int[] b = new int[n];
        while(j <= n){
            INST_COUT++;
            int i = 1;
            while(i <= n - j){
                INST_COUT++;
                int m = i + j - 1;
                int r = min(m + j, n);
                int u = i;
                for(; u < r; u++){
                    INST_COUT++;
                    b[u] = a[u];
                }
                u = i;
                int v = m + 1;
                int w = i;
                for(; w < r; w++){
                    INST_COUT++;
                    if((u > m) || (v <= r && b[v-1] < b[u-1])){
                        INST_COUT++;
                        a[w] = b[v];
                        v++;
                    } else {
                        INST_COUT++;
                        a[w] = b[u];
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
        COUNT_TWO++;
        if(i > a.length - 1){
            for(int j = i; j < a.length - 1; j++){
                COUNT_TWO++;
                if(b[j] > 0){
                    out.println(b[j]);
                    COUNT_TWO++;
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
        int [] a = new int[]{1,2,3,4};
        int [] b = new int[]{1,2,3,4,5,6,7,8};
        int [] c = new int[]{-1,-2,-3,0,1,2,3,4,5,6,7,8};
        algoOne(a);
        algoOne(b);
        algoOne(c);

        // int [] e = new int[]{1,2,3,4};
        // int [] d = new int[]{-1,2,-3,4,-5,6,-7,8};
        // int [] f = new int[]{-1,2,-3,4,-5,6,-7,8,0,99,123,45634,1234234,7465745};
        compute(a,new int[]{0,0,0,0},1);
        compute(b,new int[]{0,0,0,0,0,0,0,0},1);
        compute(c,new int[]{0,0,0,0,0,0,0,0,0,0,0,0},1);
    }
}
