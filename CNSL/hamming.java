import java.util.*;

public class HammingCode {
	 static long countSetBits(long n)
	{
		if (n == 0) return 1;
	    long  count = 0;
	    while (n > 0) {
	        count += 1;
	        n /=10;
	    }
	    return count;
	}

	public static void main(String[] argc){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter Number");
		long number = sc.nextInt();
		long m = countSetBits(number);
		long r = 1;
		while (Math.pow(2, r) < m + r + 1)
		{
			r++;
		}

		// Generate Parity Bits
		long[] parityArrayPos = new long[(int)r];
		for(long i = 0; i < r; i++) {
			parityArrayPos[(int)i] = (long) Math.pow(2, i);
		}
		long[] parityArray = new long[(int)r];
		for(long i = 0; i < r; i++) {
			parityArray[(int)i] = -1;
		}

		// Initial Hamming Array Calculation
		long[] hammingArray = new long[(int) (r+m)];
		int j = 0;
		for (int i = 0; i<r+m; i++) {
			if (j < r && i == parityArrayPos[j]-1) {
				hammingArray[i] = parityArray[j];
				j++;
			}
			else {
				long x = number%10;
				hammingArray[i] = x;
				number = number/10;
			}
		}
		System.out.println(Arrays.toString(hammingArray));

		// Calculate R1, R2 ...
		// looping for each r
		for (int i = 0; i< r; i++) {
			String s1 = "";
			for (int k = (int) (parityArrayPos[i]-1); k < r+m; k = (int) (k+parityArrayPos[i]*2)) {
				for (int z = 0; z < parityArrayPos[i]; z++) {
					if (k+z < r+m && hammingArray[k+z] != -1) {
						s1 += String.valueOf(hammingArray[k+z]);
					}
				}
			}

			int oneCount = 0;
			for (int a = 0; a < s1.length(); a++) {
				if (s1.charAt(a) == '1') {
					oneCount++;
				}
			}
			parityArray[i] = oneCount %2;
		}
		j = 0;
		for (int i = 0; i<r+m; i++) {
			if (j < r && i == parityArrayPos[j]-1) {
				hammingArray[i] = parityArray[j];
				j++;
			}
		}
		System.out.println(Arrays.toString(hammingArray));
	}
}