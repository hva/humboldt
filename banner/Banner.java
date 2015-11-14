package banner;

public class Banner {

	public static int[][][] digits = new int[][][] {
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
			{ 0, 1, 1, 1 },
		},
	};
	
	public static void main(String[] args) {
		
		int[] text = new int[] { 0, 1 }; 
		
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < text.length; t++) {
				
				for (int j = 0; j < 4; j++) {
					int value = digits[t][i][j];
					String out = (value == 0) ? " " : "#";
					System.out.print(out);
				}
			}
			System.out.println();
		}
	}
}
