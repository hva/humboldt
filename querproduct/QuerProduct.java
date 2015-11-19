package querproduct;

public class QuerProduct {

	public static void main(String[] args) throws Exception {
		int kMin = 0;
		if (args.length < 1) {
			throw new Exception("Ungültige Anzahl an Parametern");
		}

		short kMax = Short.parseShort(args[0]);

		if (kMax < 0) {
			System.out.println("Fehler. Negative Zahl ist angegeben.");
			System.exit(-1);
		}

		if (kMax > 9) {
			System.out.println("Keine Zahl im Integerbereich hatt Querprodukt von mehr als 9 Schritten");
			System.exit(-1);
		}
		
		for (int i = 0; i < Integer.MAX_VALUE; i++) {
			int k = 0;
			int output = i;
			do {
				output = produkt(output);
				k++;
			} while (output > 9);
			if (k > kMin) {
				kMin = k;
				System.out.println(k + " Schritte:" + " " + i);
				if (k == kMax) {
					System.exit(-1);
				}
			}
		}
	}

	public static int produkt(int input) {
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