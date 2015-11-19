package banner;

public class Banner {

	public static int[][][] masks = new int[][][] {
		{ // 0			
			{ 0, 1, 1, 0 },
			{ 1, 0, 0, 1 },
			{ 1, 0, 0, 1 },
			{ 0, 1, 1, 0 },
		},
		{ // 1
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
		},
		{ // 2
			{ 0, 1, 1, 0 },
			{ 1, 0, 0, 1 },
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 1 },
		}
	};
	
	public static void main(String[] args) {
		if (args.length < 1) {
			System.out.println("Ungültige Anzahl an Parametern");
			System.exit(-1);
		}

		String text = args[0];

		if (text.length() > 10) {
			text = text.substring(0, 10);
		}

		for (int i = 0; i < text.length(); i++) {
			char c = text.charAt(i);
			if (!Character.isDigit(c)) {
				System.out.println("Error, only numbers are allowed");
				System.exit(-1);
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < text.length(); t++) {
				String s = text.substring(t, t + 1);
				int digit = Integer.parseInt(s);
				for (int j = 0; j < 4; j++) {
					int value = masks[digit][i][j];
					String out = (value == 0) ? " " : "#";
					System.out.print(out);
				}
			}
			System.out.println();
		}
	}
}
