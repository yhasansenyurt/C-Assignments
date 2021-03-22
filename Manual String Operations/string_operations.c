/**
 * NAME: Hasan Senyurt
 * ID: 150120531
 *
 * Purpose of the Program: This program uses structure, file i/o and some function properties to 
 * take input from .txt input file and turn into inputs to different outputs. These outputs includes
 * finding character with given index, concatenation of two strings, search given string in another string
 * (only initial statements) and finding score of letters. 
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct String{
	int length;
	char characters[50];
}String;

String s3; //this string is used for concat function inside.


int charAt(String *s,int index);
String *concat(String *s1, String *s2);
unsigned int strSearch(String *s1, String *s2);
unsigned int findScore(String *s1);

int main(int argc, char *argv[]){
	
	FILE *input,*output;
	//it controls whether command line argument is given by user or not.(input.txt output.txt or different name files.)
	if((input = fopen(argv[1],"r")) == NULL || (output = fopen(argv[2],"w")) == NULL ){
		printf("Input or output file could not be opened.");
		
	}
	else{
		
		char exit[5] = "exit"; // these exit and stat is for controlling input.
		char stat[5] = "stat";
		
		int i =0; //for while loop.
		int j,control=0,control2=0; //these controls are for determining whether given input is exit or stat.
		int char_count = 0; // character count variable
		int word_count = 0,word_count2 = 0; // word count variables. (one of them is for left part of input (before ':') another
											// one is for right part. (after ',').
		
		while(i != 10){
			char line[50];
			fgets(line,50,input);
			
			//controlling exit.
			for(j=0;j<strlen(line)-1;j++){
				if(line[j]==exit[j]){
					control = 1;
				}
				else{
					control = 0;
					break;
				}
			}
			//controlling stat.
			for(j=0;j<strlen(line)-1;j++){
				if(line[j]==stat[j]){
					control2 = 1;
				}
				else{
					control2 = 0;
					break;
				}
			}
			//counting alphabetic characters before 'stat' keyword.
			if(control2 !=1){
				int a;
				for(a=0;a<strlen(line);a++){
					if(isalpha(line[a])){
						char_count++;
					}
				}
			}
			
			//exit.
			if(control == 1){
				//printf("Program ends. Bye");
				fprintf(output,"Program ends. Bye");
				break;
			}
			
			//stat.	
			else if(control2 == 1){
				fprintf(output,"The number of words: %d\n",word_count+word_count2);
				fprintf(output,"The number of alphabetic letters: %d\n",char_count);
				
				
			}
			//if given input line is not stat or exit, program takes the line as valid input and operation begins.
			else{
				/* This part is for tokenizing given input. For example 'heLLo world:1,6' will be
				 * function[0] = "heLLo world", function[1] = 1 (operation number), function[2] = 6 (given index).
				 * with this formula, I can control left part of ':' and right part of ':' and ','. (welcome to marmara:3,mar). ->
				 * function[0] = "welcome to marmara", function[1] = "3", function [2] = "mar".
				*/
				char function[3][50];
				String string;
				char line_temp[50];
				
				strcpy(line_temp,line);
				char *token = strtok(line_temp,":");
				strcpy(string.characters,line_temp);
				string.length = strlen(line_temp);
				int i =0;
				
				
				while(token != NULL){
					strcpy(function[i],token);
					
					token = strtok(NULL,",");
					i++;
					
				}
				
				
				//controlling alphabetic characters in given lines for counting words and characters. (stat part).
				int k,alpha = 0,alpha2=0;
				for(k=0;k<strlen(function[0]);k++){
					if(isalpha(function[0][k])){
						alpha = 1;
					}
				}
				
				for(k=0;k<strlen(function[2]);k++){
					if(isalpha(function[2][k])){
						alpha2 = 1;
					}
				}
				int control_space = 0; // this control_space is for counting words. if program sees one character as space it counts it word.
									  // if it includes alphabetic character (alpha,alpha2 variables controls it.)
				
				//counting words (left side of input (before ':')).
				if(alpha == 1){
					for(k=0;k<strlen(function[0]);k++){
						if(function[0][k] == ' ' || function[0][k] == '\n' || function[0][k] == '\t'){
							control_space = 0;
						}
						else if(control_space == 0){
							control_space = 1;
							word_count++;
						}
					}
				}
				
				control_space = 0;
				
				//counting words (right side of input (after ',')).
				if(alpha2 == 1 && function[1][0] != '4'){
					for(k=0;k<strlen(function[2]);k++){
						if(function[2][k] == ' ' || function[2][k] == '\n' || function[2][k] == '\t'){
							control_space = 0;
						}
						else if(control_space == 0){
							control_space = 1;
							word_count2++;
						}
					}
				}
				
				// if operation number 1, charAt operation begins.
				if(function[1][0]=='1'){
					// function[2] gives index.
					int index = atoi(function[2]);
					string.length = strlen(function[0]);
					
					//it checks whether given index has problem or not.
					if(charAt(&string,index) == -1){
						fprintf(output,"%d\n",-1);
					}
					else{
						fprintf(output,"%c\n",toupper(charAt(&string,index)));
					}
					
				}
				// if operation number 2, concat operation begins.
				else if(function[1][0]=='2'){
					String s_concat;
					
					//some sets on given inputs (string copy, removing last character /n.)
					strcpy(s_concat.characters,function[2]);
					s_concat.length = strlen(function[2])-1;
					s_concat.characters[s_concat.length] = 0;
					String *s4;
					s4 = concat(&string,&s_concat);
					
					fprintf(output,"%s\n",s4->characters);
					
					//resetting s4 string for another concat operation.
					int o;
					for(o=0;o<strlen(s4->characters);o++){
						s4->characters[o] = ' ';
					}
					
				}
				
				// if operation number 3, strSearch operation begins.
				else if(function[1][0] == '3'){
					
					//setting correct form of input.
					function[2][strlen(function[2])-1] = 0;
					String s_search;
					strcpy(s_search.characters,function[2]);
					s_search.length = strlen(s_search.characters);
					fprintf(output,"%u\n",strSearch(&string,&s_search));
					
				}
				
				// if operation number 4, findScore operation begins.
				else if(function[1][0] == '4'){
					
					fprintf(output,"%u\n",findScore(&string));
				}	
			}
			
		}
		fclose(input);
	}
	
	return 0;
}
//finding character of s string with given index.
int charAt(String *s,int index){
	//checking if index value is valid or not.
	if(index < (*s).length && !(index <0)){
		return (*s).characters[index];
		
	}
	else{
		return -1;
	}
}
//concatenation of two strings. it uses s3 string to return its address. (s3 declared in the beginning of the code.)
String *concat(String *s1, String *s2){
	
	String s1_temp = *s1,s2_temp = *s2;
	int i,j = 0;
	
	for(i=0;i<=s1_temp.length+s2_temp.length;i++){
		if(i<s1_temp.length){
			s3.characters[i]=s1_temp.characters[i];
			
		}
		else{
			if(i==s1_temp.length){
				s3.characters[i] =' ';
			}
			else{
				s3.characters[i]=s2_temp.characters[j];
				j++;
			}
			
		}
	}
	return &s3; 
	
}
//searching string in another string (only initial statements.)
unsigned int strSearch(String *s1, String *s2){
	
	String s_temp = *s1;
	String s_temp2 = *s1;
	//counting words in first string.
	char *token = strtok(s_temp.characters," ");
	int count =0;
	while(token != NULL){	
		count++;
		token = strtok(NULL," ");
	}
	//creating array which includes words in first string.
	String s3[count];
	
	char *token2 = strtok(s_temp2.characters," ");
	int i=0;
	while(token2 != NULL){
		strcpy(s3[i].characters,token2);
		i++;
		token2 = strtok(NULL," ");
	}
	
	int j,index=0,index_real = 0;
	int control = 0,control2 = 0;
	
	//controlling words in array whether one of them begins with second given string or not.
	for(i=0;i<count;i++){
		for(j=0;j<strlen((*s2).characters);j++){
			if((*s2).characters[j]==s3[i].characters[index]){
				control = 1;
			}
			else{
				control = 0;
				break;
			}
			index++;
		}
		index = 0;
		
		if(control == 1){
			index_real = i;
			control2 = 1;
			break;
		}
	}
	if(control2 == 1){
		return strlen(s3[i].characters);
	}
	else{
		return 0;
	}
	
}
//finding scores of letters.
unsigned int findScore(String *s1){
	String s1_temp = *s1;
	int i;
	int result = 0;
	//it turns all characters to uppercase (it makes easier to count scores in the code.)
	for(i=0;i<(*s1).length;i++){
		s1_temp.characters[i] = toupper(s1_temp.characters[i]);
	}
	
	for(i=0;i<(*s1).length;i++){
		if(s1_temp.characters[i] == 'A' || s1_temp.characters[i] == 'E' || s1_temp.characters[i] == 'I' || s1_temp.characters[i] == 'O' || s1_temp.characters[i] == 'U' 
		|| s1_temp.characters[i] == 'L' || s1_temp.characters[i] == 'N' || s1_temp.characters[i] == 'R' || s1_temp.characters[i] == 'S' || s1_temp.characters[i] == 'T' ){
			
			result += 1;
		}
		else if(s1_temp.characters[i] == 'D' || s1_temp.characters[i] == 'G'){
			result +=2;
			
		}
		else if(s1_temp.characters[i] == 'B' || s1_temp.characters[i] == 'C' || s1_temp.characters[i] == 'M' || s1_temp.characters[i] == 'P' ){
			result += 3;
		}
		else if(s1_temp.characters[i] == 'F' || s1_temp.characters[i] == 'H' || s1_temp.characters[i] == 'V' || s1_temp.characters[i] == 'W' || s1_temp.characters[i] == 'Y' ){
			result += 4;
		}
		else if(s1_temp.characters[i] == 'K'){
			result += 5;
		}
		else if(s1_temp.characters[i] == 'X' || s1_temp.characters[i] == 'J'){
			result += 8;
		}
		else if(s1_temp.characters[i] == 'Q' || s1_temp.characters[i] == 'Z'){
			result += 10;
		}
		else{
			result +=0;
		}
	}
	return result;
}

