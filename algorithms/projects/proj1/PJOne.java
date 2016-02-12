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

    public static void algoOne(int size, int[] a){
        int j = 1;
        int[] b = new int[size];
        int n = size;
        while(j <= n - 1){
            int i = 1;
            while(i <= n - j){
                int m = i + j - 1;
                int r = min(m + j, n);
                int u = i;
                for(; u < r; u++){
                    b[u] = a[u];
                }
                u = i;
                int v = m + 1;
                int w = i;
                for(; w < r; w++){
                    if(u > m || (v <= r && b[v] < b[u])){
                        a[w] = b[v];
                        v++;
                    } else {
                        a[w] = b[u];
                        u++;
                    }
                }
                i += 2 * j;
            }
            j *= 2;
        }
    }

    public static void compute(int[] a, int[] b, int i){
        if(i > a.length){
            for(int j = i; j < a.length; j++){
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
        int[] a = {1,2,3,4};
        int[] b = {0,0,0,0};
        compute(a,b,0);
    }
}
