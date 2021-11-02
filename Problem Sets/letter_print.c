/**
 * NAME: Hasan Senyurt
 * ID: 150120531
 *
 * Purpose of the Program: This program takes one number and one character from user to write the 'X,Y,W,Z' letters
 * with given size. It controls the values from user whether they are invalid or not in while loop until it takes
 * correct value from user. Size must be odd number and equal or greater than 5. It can only prints 4 letters 'X','Y',
 * 'W','Z'.
 */


#include<stdio.h>

void drawLetter(char ch,int size);

int main(){
	
	int size,a=1,b=1,c=1;
	
	char letter;
	char answer;
	
	printf("Welcome to the letter printer.\n");
	
	while(a==1){
		// this _true values are for controlling the inputs to decide print or not.
		int size_true=0;
		int letter_true=0;
		
		printf("Enter the size: ");
		scanf("%d",&size);
		
		while(b=1){
			
		
			if(size%2==1 && size>=5){
				size_true =1;
				break;
			}
			else{
				printf("Invalid size. Enter the size again: ");
				scanf("%d",&size);
				size_true =0;
			}
		}
		
		printf("Enter the letter: ");
		scanf(" %c",&letter);
		
		while(b=1){
			if(letter=='W'|| letter=='Z'|| letter=='Y'|| letter=='X'){
				letter_true=1;
				break;
			}
			else{
				printf("Invalid letter: Enter the letter again: ");
				scanf(" %c",&letter);
				letter_true=0;
			}
		}
		//control mechanisim check.
		if(size_true==1 && letter_true==1){
			drawLetter(letter,size);
		}
		printf("Would you like to continue (Y or N): ");
		while(c==1){
			
			scanf(" %c",&answer);
			if(answer=='Y'){
				break;
				continue;
			}
			else if(answer == 'N'){
				printf("Goodbye :)");
				a=0;
				break;
			}
			else{
				printf("Please enter valid answer (Y or N): ");
				
			}
		}
		
	}
	
	return 0;
}

void drawLetter(char ch, int size){
	// DRAWING X (Algorithm is about printing 'X' with dividing 2 parts. First it prints upper and then it prints bottom part of X.)
	if(ch == 'X'){
		int i,j,k;
		int temp = size;
		//this part is for printing upper part of 'X'.
		for(i=0;i<size/2+1;i++){
			printf("*");
			
			for(j=0;j<temp-2;j++){
				printf(" ");
			}
			
			if(temp>1){
				printf("*");
				printf("\n");
				
			for(k=0;k<i+1;k++){
				printf(" ");
			}
			}
			temp -=2;
			
		}
		printf("\n");
		
		//this part is for printing bottom part of 'X'.
		int a,b,c;
		int temp1 = size;
		for(a=0;a<size-(size/2+1);a++){
			
			for(b=0;b<(temp1/2-1);b++){
				printf(" ");
			}
			printf("*");
			
			for(c=0;c<2*a+1;c++){
				printf(" ");
			}
			
			printf("*");
			temp1 -=2;
			printf("\n");	
		}
	}
	//DRAWING Z(Algorithm of printing Z is about dividing Z 3 parts. First upper,secondly middle and then bottom parts are printed.)
	
	// Note: Sanem teacher said that if you wrote the code for Z letter like the homework pdf, then it is okay, you dont need to change it.
	//		 Only change W if you did like homework pdf. (harflerin bazi yildizlari kaymis, Sanem Hoca Z icin sorun degil ama W yi duzgun yapin demisti.
	//		 Haberiniz yoktur belki diye not dusmek istedim varsa kusuruma bakmayin.)
	else if(ch == 'Z'){
		int i,j;
		int temp3 = size;
		//printing upper side.
		for(i=0;i<size;i++){
			printf("*");
		}
		
		printf("\n");
		
		//printing middle side.
		for(i=0;i<size;i++){
		
			for(j=0;j<temp3-1;j++){
				printf(" ");
			}
			printf("*");
			
			if(i !=size-1){
				printf("\n");
			}
			
			temp3--;
		}
		//printing bottom side.
		for(i=0;i<size-1;i++){
			printf("*");
		}
		printf("\n");
		
	}
	//DRAWING W(Algorithm of printing W is about dividing W 3 parts. Upper side is first row of W. middle part  
	// 			goes until it reaches end of the row. Bottom side is undermost row of W.)
	else if(ch == 'W'){
		
		int i,j,k;
		int space = 2*size-5;
		int space1= 1;
		//printing first row of W.
		for(i=0;i<4*size-3;i++){
			if(i==0 || i==2*size-2 || i==4*size-4){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
		
		//printing middle rows of W.
		for(i=0;i<size-2;i++){
			
			for(j=0;j<i+1;j++){
				printf(" ");
			}
			printf("*");
			
			for(j=0;j<space;j++){
				printf(" ");
			}
			printf("*");
			
			for(j=0;j<space1;j++){
				printf(" ");
			}
			printf("*");
			
			for(j=0;j<space;j++){
				printf(" ");
			}
			printf("*");
			
			space1 +=2;
			space -=2;
			printf("\n");
			
		}
		//printing bottom row.
		for(i=0;i<3*size-2;i++){
			if(i==size-1|| i==3*size-3){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
		
	}
	//DRAWING Y(Algorithm of drawing Y is dividing Y 2 parts. First upper 'V' side after that bottom '|' side. 
	else if(ch == 'Y'){
		int i,j,k;
		int temp = size;
		//printing upper side.
		for(i=0;i<size/2+1;i++){
			
			printf("*");
			
			for(j=0;j<temp-2;j++){
				printf(" ");
			}
			if(temp>1){
				printf("*");
				printf("\n");
				
			for(k=0;k<i+1;k++){
				printf(" ");
			}
			
			}
			
			temp -=2;
			
		}
		printf("\n");
		//printing bottom side.
		for(j=0;j<size/2;j++){
		
			for(i=0;i<size/2;i++){
				printf(" ");
			}
			printf("*");
			printf("\n");
		}
		
	}
}
