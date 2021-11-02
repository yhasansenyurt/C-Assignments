/**
 * NAME: Hasan Senyurt
 * ID: 150120531
 *
 * Purpose of the Program: This program takes a two integers (one of them is pointer) from user. Pointer one is actual number and
 * other one is the number that determines how many numbers will be reversed. reverseN function takes
 * two parameters which are integer pointer and integer from main function and it reverses N digits from end of the number to 
 * beginning of the number. Number will be changed permanently because the value that is send in main is pointer value. The
 * value will be changed from its address directly.
 */

#include <stdio.h>

int print = 1; //this is for controlling whether N is bigger than digit count of number or not.
void reverseN(int *number, int N);
int main(){
	
	int number;
	int N;
	printf("Please give the numbers: ");
	scanf("%d %d",&number,&N);
	reverseN(&number,N);
	if(print==1){
		printf("%d",number);
	}
	
	
	
	return 0;
}

void reverseN(int *number, int N){
	
	int digit,count=0;
	int temp =*number,temp3=*number; //this temporary variables are for operations in the number(like seperating digits).
	int temp2 = N;
	int i;
	//counting digits.
	while(temp){
		temp /=10;
		count++;
	}
	temp = *number;
	// controlling whether n value is bigger than count or not.
	if(N>count || N<0){
		printf("N must be less than %d!",count+1);
		print = 0;
	}
	else{
		// extracting reverse digits.
		while(temp2>0){
			*number /=10;
			temp2--;
		}
		// multiplying number over and over for adding reverse numbers after.
		for(i=0;i<N;i++){
			*number *=10;
		}
		// adding reverse parts to number.
		while(N>0){
			digit = temp3%10;
			temp3 /=10;
			for(i=0;i<N-1;i++){
				digit *=10;
			}
			*number +=digit;
			N--;
		}
		
	}
	
	
	
	
}

