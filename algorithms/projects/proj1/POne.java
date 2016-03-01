/**
 * 420 - Project One
 * 
 * @author Taliahicks
 * @author StevenR
 * 
 * @version 2/24/16
 *
 */


public class POne {
	
	private static int alg2operations = 0;

	public static void algOne(int[] A) {
		int i;
		int m;
		int r;
		int u;
		int v;

		// added to count operations
		int operations = 0;

		int j = 1;
		int n = A.length - 1;
		int[] B = new int[n];

		operations += 3; // operation count

		while (j <= (n - 1)) {
			i = 1;
			operations++; // operation count
			while (i < (n - j)) {
				m = i + j - 1;

				operations++; // operation count

				r = min(m + j, n);
				operations++; // operation count
				for (u = i; u < r; u++) {
					B[u] = A[u];
					operations++; // operation count
				}

				u = i;
				v = m + 1;
				operations+=2; // operation count

				for (int w = i; w < r; w++) {
					if ((u > m) || ((v < r) && B[v] < B[u])) {
						A[w] = B[v];
						v++;
						operations++; // operation count
					} 
					else {
						A[w] = B[u];
						u++;
						operations++; // operation count
					}
					operations++; // operation count
				}
				i += (2 * j);
				operations++; // operation count
			}
			j = 2 * j;
			operations++; // operation count
		}

		System.out.println("Approximate Operations: " + operations);
	}

	public static int min(int a, int b) {
		return a < b ? a : b;
	}

	public static void compute(int[] A, int[] B, int i) {
		int N = A.length - 1;
		alg2operations++; //operation count
		
		if (i > N) {
			for (int j = 1; j < N; j++) {
				alg2operations++; //operation count
				if (B[j] > 0) {
					System.out.println(B[j]);
					alg2operations++; //operation count
				} // end if
			} // end for
			alg2operations++; //operation count
			return;
		} // end if

		B[i] = 0;
		compute(A, B, i + 1);

		B[i] = A[i];
		compute(A, B, i + 1);
		alg2operations+=2; //operation count

		B[i] = 0;
		
		
	}

	public static void main(String args[]) {
		
		int[] a = new int[20];
		int[] b = new int[a.length];
		
		for(int i = 0; i < a.length; i ++)
		{
			a[i] = (int) (Math.random()*50);
		}
		
		for(int i = 0; i < a.length; i ++)
		{
			b[i] = 0;
		}
		
		
		
		compute(a,b,1);
		
		System.out.println("Approximate Operations: " + alg2operations);

	}
}
