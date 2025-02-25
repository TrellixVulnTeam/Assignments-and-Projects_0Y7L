import java.util.Scanner;

public class MethodPractice {
	
	public static int numberOfWords(String str1){
			return str1.split(" ").length;	
	}
	
	public static String longestTitle(String[] str_arr){
		int max_words_in_str = -1;
		int str_with_max_words = -1; //place holders
		
		for(int i = 0; i < str_arr.length; i++){
			
			if(str_arr[i].split(" ").length > max_words_in_str){
				max_words_in_str = numberOfWords(str_arr[i]);
				str_with_max_words = i;
			}
		}
		return str_arr[str_with_max_words];
		
	}
	
	
	public static void main(String[] args){
		int i = 0;
		String stringArray[] = new String[5];
		
		Scanner scan = new Scanner(System.in);
		
		while(i < 5){
			System.out.format("Please enter movie title %d: ", i + 1);
			if((stringArray[i] = scan.nextLine()) != null){
				i++;
			}
		}
		System.out.println(longestTitle(stringArray));
		
	}
}
