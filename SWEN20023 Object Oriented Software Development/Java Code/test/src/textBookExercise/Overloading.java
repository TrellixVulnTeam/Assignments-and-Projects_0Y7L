package textBookExercise;

public class Overloading {
	
	public static int max(int n1, int n2){
		if(n1 > n2){
			return n1;
		}
		else{
			return n2;
		}
		
	}
	public static String max(String str1, String str2){
		
		if(str1.length()> str2.length()){
			return str1;
		}
		else{
			return str2;
		}
	}
	
	public static String max(String str1, String str2, String str3, String str4){
		
		return max(max(str1,str2), max(str3,str4));
		
	}
	
	public static String max(String[] arr){
		int str_max_length = 0;
		int str_with_max = -1;// place holder value for index
		
		for(int i = 0; i < arr.length; i++){
			if(arr[i].length() > str_max_length){
				str_max_length = arr[i].length();
				str_with_max = i;
			}
		}
		return arr[str_with_max];
		
	}
	public static void main(String[] args){
		String str_arr[] = {"there was a chicken", "there was once a chicken", "there is a chicken"};
		
		System.out.println(max(3, 4));
		System.out.println(max("this is chicken", "this is fish"));
		System.out.println(max("this is chicken", "this is elephant", "this is fish", "this is beef"));
		System.out.println(max(str_arr));
	}
}