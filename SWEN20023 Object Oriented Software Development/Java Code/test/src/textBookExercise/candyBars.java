package textBookExercise;
import java.util.Scanner;

public class candyBars {
	public static void main(String[] args){
		int coupons;
		Scanner reader = new Scanner(System.in);
		System.out.println("Please enter number of coupons: ");
		coupons = reader.nextInt();
		System.out.println("Number of Candy Bars = " + coupons/10);
		coupons %= 10;
		System.out.println("Number of Gum Balls = " + coupons/3);
		reader.close();
	}
}
