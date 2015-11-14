package querproduct;

public class QueryProduct {

	public static void main(String[] args) {
		int kMin = 0;
		for(int i = 10; i < Integer.MAX_VALUE; i++) {
			int k = 0;
			int output = i;
			do {
				output = produkt(output);
				k++;
			}
			while (output > 9);
			if (k > kMin) {
				kMin = k;
				System.out.println(k + " " + i);
			}
		}
	System.out.println("Beendet");
	
	}
	
	private static int produkt(int input) {
	  int output = 1;
	  int last;
	  do {
		  last = input % 10;
		  input = input / 10;
		  output *= last;
	  } while (input != 0);
	  return output;
	}
}
