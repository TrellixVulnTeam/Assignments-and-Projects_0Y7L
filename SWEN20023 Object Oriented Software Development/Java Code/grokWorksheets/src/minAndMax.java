import java.util.Scanner;

public class minAndMax {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		int minNum, maxNum;
		minNum = maxNum = 0;
		
		String input;
		
		while((input = sc.nextLine()) != null){
			System.out.println("Input a number: ");
			
			
			if (input == null && minNum == 0 && maxNum == 0){
				System.out.println("No numbers were added");
				break;
			}
			if(input == null){
				System.out.format("Min number: %d\nMax number: %d", minNum, maxNum);
				break;
			}
			System.out.println(input.getClass().getName());

			Integer num = Integer.parseInt(input);
			
			if(num < minNum){
				minNum = num;
			}
			else if(num > maxNum){
				maxNum = num;
			}	
		}
		sc.close();	
	}
}
