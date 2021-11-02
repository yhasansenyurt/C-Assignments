/* 150120531 & Hasan & Senyurt

 I acknowledge that I will not share my work (not even a part of it) with my friends; I will be responsible for what has been submitted. 
 In case of any form of copying and cheating on solutions, I know that I will get FF grade from the course!

*/ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fillArray(unsigned int size, char arr[]){
	int number;
	srand(time(NULL));
	
	
	
	int i;
	for(i=0;i<size;i++){
		number = rand() % 26;
		arr[i]= 97 + number;
	}
	
}

int findChar(unsigned int size,char arr[],char *most){
	int count[26]={0}; // alphabet indexes for example a = index 0 , b index 1 ,c index 2.
	
	int i,letter;
	for(letter=0;letter<26;letter++){
		for(i=0;i<size;i++){
			if(arr[i]==97+letter){
				++count[letter];
			}
		}
	}
	
	
	int max = count[0];
	int index=0;
	for(i=1;i<26;i++){
		if(count[i]>max){
			max = count[i];
			index = i;
		}
	}
	*most = 97 +index ;

	return max;
	
	
}

int main(void){
	
	char arr[50], most;

    int times=0;   

    fillArray(50, arr);

    times = findChar(50, arr, &most);

    printf("The character %c is appeared %d times\n", most, times);
    
	
	
	return 0;
}
