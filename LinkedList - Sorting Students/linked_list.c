/**
 * NAME: Hasan Senyurt
 * ID: 150120531
 *
 * Purpose of the Program: This program uses structure and pointers inside to create linked list. 3 self-struct pointer 'name_next',
 * 'surname_next' and 'id_next' holds alphabetical and numerical orders of students' names, surnames and ids. These 3 pointers all connected
 * in every students. In the beginning, there are some students in 'students.txt' and this program takes them to linked list. User can insert
 * new students and delete them. List can be printed at console or on output file according to the user's choice.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student{
	char name[15];
	char surname[15];
	long int id;
	
	struct student *name_next;
	struct student *surname_next;
	struct student *id_next;
};

typedef struct student student;
typedef student *studentPtr;

void instructions();
void insert(studentPtr *sPtr,studentPtr *sPtr1,studentPtr *sPtr2 ,char input_name[15],char input_surname[15],long int input_id);
void delete(studentPtr *sPtr, studentPtr *sPtr1,studentPtr *sPtr2 ,long int value);
void printList(studentPtr namePtr,studentPtr surnamePtr,studentPtr idPtr);

int main(int argc, char *argv[]){
	//Head pointers that will send to functions.
	studentPtr name_head = NULL;
	studentPtr surname_head = NULL;
	studentPtr id_head = NULL;
	
	FILE *input,*output;
	//it controls whether input file given as command line argument.
	if((input = fopen(argv[1],"r")) == NULL){
		printf("Input file could not be opened.");
	}
	else{
		//these are the students that taken in input file.
		char name[20],surname[20];
		long int id;
		fscanf(input,"%s %s\t%ld",name,surname,&id);
		//insertion of input file students.
		while(!feof(input)){
		insert(&name_head,&surname_head,&id_head,name,surname,id);
		fscanf(input,"%s %s\t%ld",name,surname,&id);	
		}
		printList(name_head,surname_head,id_head);
		
		instructions();
		printf("%s", "? ");
		// user's choice
   		unsigned int choice; 
   		scanf("%u", &choice);
   		
   		while(choice != 5){
   			switch(choice){
   				//insertion option
   				case 1:
   					printf("Enter a student name, surname and ID:\n");
   					char s_name[15],s_surname[15];
					long int s_id;
				  	scanf("%s %s %ld",s_name,s_surname,&s_id);
					insert(&name_head,&surname_head,&id_head,s_name,s_surname,s_id);
					break;
			   //deletion option
			   case 2:
			   		printf("Enter a student ID:\n");
			   		long int d_id;
			   		scanf("%ld",&d_id);
			   		delete(&name_head,&surname_head,&id_head,d_id);
			   		break;
			   // printing list on console.
			   case 3:
			   		printList(name_head,surname_head,id_head);
			   		break;
			   // printing list on output file. 		
			   case 4:
			   		puts("Enter a file name:");
			   		//user gives a file name.
			   		char out[20];
					scanf("%s",out);
					output = fopen(out,"w");
					
					fprintf(output,"The list in name-alphabetical order:\n");

			        // while not the end of the list for name alphabetical order.
			        int i =1;
			        
			        while (name_head != NULL) { 
			           fprintf(output,"\t%d. %s %s\t%ld\n",i,name_head ->name,name_head ->surname,name_head ->id);
			           name_head  = name_head ->name_next;
					   i++;   
			        } 
			        fprintf(output,"\n");
			        fprintf(output,"The list in surname-alphabetical order:\n");
					// while not the end of the list for surname alphabetical order.
			        int j = 1;
			        while (surname_head != NULL) { 
			           fprintf(output,"\t%d. %s %s\t%ld\n", j,surname_head->name,surname_head->surname,surname_head->id);
			           surname_head = surname_head->surname_next;
					   j++;   
			        } 
			      
			        fprintf(output,"\n");
			        fprintf(output,"The list in ID sorted order:\n");
			        // while not the end of the list for id numerical order.
				    int k = 1;
			        while (id_head != NULL) { 
			           fprintf(output,"\t%d. %s %s\t%ld\n", k,id_head->name,id_head->surname,id_head->id);
			           id_head = id_head->id_next;
					   k++;   
			        } 
				    fprintf(output,"\n");
					fclose(output);
					printf("Output is printed to the file %s\n",out);
					break;
							
			   default:
			   		printf("Invalid choice.\n");
			   		break;
			   	}
			instructions();   	
			printf("%s", "? ");
      		scanf("%u", &choice);
			   	    
		   }
	}
	fclose(input);
	return 0;
}


void instructions(){ 
   puts("Enter your choice:\n"
      "   1 to insert a student into the list.\n"
      "   2 to delete a student from the list.\n"
      "   3 to print the students in the list.\n"
	  "   4 to print the students to an output file.\n"
	  "   5 to end.");
}


void insert(studentPtr *sPtr,studentPtr *sPtr1,studentPtr *sPtr2 ,char input_name[15],char input_surname[15],long int input_id){
   //creating node with malloc.	 
   studentPtr newPtr = malloc(sizeof(student));
   //if there is space, takes the values which are sent in function.
   if (newPtr != NULL) {
      strcpy(newPtr->name,input_name);
      strcpy(newPtr->surname,input_surname);
      newPtr->id = input_id;
      // NULL at the beginning.
      newPtr->name_next = NULL;
      newPtr->surname_next = NULL;
      newPtr->id_next = NULL;  
      
      //FOR NAME.
      studentPtr previous_namePtr = NULL;
      studentPtr name_head = *sPtr;

      // loop to find the correct location in the list.  
      while (name_head != NULL && (strcmp(input_name,name_head->name))>=0) {
      	 previous_namePtr = name_head;               
         name_head = name_head->name_next;
      }                                          
      // insert new node at beginning of list
      if (previous_namePtr == NULL) { 
         newPtr->name_next = *sPtr;
         *sPtr = newPtr;
      }
      // insert new node between previousPtr and currentPtr
      else {
         previous_namePtr->name_next = newPtr;
         newPtr->name_next = name_head;
      }
      
      //FOR SURNAME
   	  studentPtr previous_surnamePtr = NULL; 
      studentPtr surname_head = *sPtr1;
      
      while (surname_head != NULL && (strcmp(input_surname,surname_head->surname))>=0) {
      	 previous_surnamePtr = surname_head;               
         surname_head = surname_head->surname_next;
      }                                          
      // insert new node at beginning of list
      if (previous_surnamePtr == NULL) { 
         newPtr->surname_next = *sPtr1;
         *sPtr1 = newPtr;
      }
      // insert new node between previousPtr and currentPtr
      else {
         previous_surnamePtr->surname_next = newPtr;
         newPtr->surname_next = surname_head;
      }
	  
	  //FOR ID
      studentPtr previous_idPtr = NULL;
      studentPtr id_head = *sPtr2;

      // loop to find the correct location in the list       
      while (id_head != NULL && input_id > id_head->id) {
         previous_idPtr = id_head;              
         id_head = id_head->id_next;
      }                                          

      // insert new node at beginning of list
      if (previous_idPtr == NULL) { 
         newPtr->id_next = *sPtr2;
         *sPtr2 = newPtr;
      }
	  // insert new node between previousPtr and currentPtr 
      else {
         previous_idPtr->id_next = newPtr;
         newPtr->id_next = id_head;
      }    
	}
	//Cannot insert if the memory is not available.
   	else {
    	printf("%s %s %d not inserted. No memory available.\n", input_name,input_surname,input_id);
   	}
}



void delete(studentPtr *sPtr,studentPtr *sPtr1,studentPtr *sPtr2 , long int value){
	//Name pointer deletion.(freeing memory location)
	void delete_name(studentPtr *sPtr,long int value){
		//deletion first node if the id matches.
		if (value == (*sPtr)->id) { 
	      studentPtr tempPtr = *sPtr;
		  *sPtr = (*sPtr)->name_next;
	      printf("The student '%s %s %d' is deleted from the list!\n",tempPtr->name,tempPtr->surname,tempPtr->id);
	      free(tempPtr); // freeing memory.
	   }
	   //finding nodes if it is not at beginning.
	   else { 
	      studentPtr previousPtr = *sPtr;
	      studentPtr currentPtr = (*sPtr)->name_next;
	
	      // loop to find the correct location in the list
	      while (currentPtr != NULL && currentPtr->id != value) { 
	         previousPtr = currentPtr; 
	         currentPtr = currentPtr->name_next; 
	      } 
	      // delete node at currentPtr
	      if (currentPtr != NULL) { 
	         studentPtr tempPtr = currentPtr;
	         previousPtr->name_next = currentPtr->name_next;
	         printf("The student '%s %s %d' is deleted from the list!\n",tempPtr->name,tempPtr->surname,tempPtr->id);
	         free(tempPtr);	         
	      } 
	   }
	}
	//surname pointer deletion.(freeing memory location)
	void delete_surname(studentPtr *sPtr1,long int value){
		//deletion first node if the id matches.
		if (value == (*sPtr1)->id) { 
	      studentPtr tempPtr1 = *sPtr1;
		  *sPtr1 = (*sPtr1)->surname_next;
	      free(tempPtr1); // freeing memory.    
	   }
	   //finding nodes if it is not at beginning.
	   else { 
	      studentPtr previousPtr1 = *sPtr1;
	      studentPtr currentPtr1 = (*sPtr1)->surname_next;
	      // loop to find the correct location in the list
	      while (currentPtr1 != NULL && currentPtr1->id != value) { 
	         previousPtr1 = currentPtr1;  
	         currentPtr1 = currentPtr1->surname_next;
	      } 
	      // delete node at currentPtr
	      if (currentPtr1 != NULL) { 
	         studentPtr tempPtr1 = currentPtr1;
	         previousPtr1->surname_next = currentPtr1->surname_next;
	         free(tempPtr1);
	        
	      } 
		}
	}
	//id pointer deletion.(freeing memory location.)
	void delete_id(studentPtr *sPtr2,long int value){
		//deletion first node if the id matches.
		if (value == (*sPtr2)->id) { 
	      studentPtr tempPtr2 = *sPtr2;
		  *sPtr2 = (*sPtr2)->id_next;
	      int i=0;
	      free(tempPtr2); // freeing memory.
	   }
	   //finding nodes if it is not at beginning.	   
	   else { 
	      studentPtr previousPtr2 = *sPtr2;
	      studentPtr currentPtr2 = (*sPtr2)->id_next;
	
	      // loop to find the correct location in the list
	      while (currentPtr2 != NULL && currentPtr2->id != value) { 
	         previousPtr2 = currentPtr2;  
	         currentPtr2 = currentPtr2->id_next; 
	      } 
	      // delete node at currentPtr
	      if (currentPtr2 != NULL) { 
	         studentPtr tempPtr2 = currentPtr2;
	         previousPtr2->id_next = currentPtr2->id_next;
	         free(tempPtr2);  
	      } 
	   }
	}
	//calling functions.
	delete_name(sPtr,value);
	delete_surname(sPtr1,value);
	delete_id(sPtr2,value);  
}

void printList(studentPtr namePtr,studentPtr surnamePtr,studentPtr idPtr){ 
   //checks whether list is empty or not.
   if (namePtr == NULL || surnamePtr == NULL || idPtr == NULL) {
      puts("List is empty.\n");
   } 
   else { 
      puts("The list in name-alphabetical order:");

      
      //name.
      int i =1;
      while (namePtr != NULL) { 
         printf("\t%d. %s %s\t%ld\n",i,namePtr->name,namePtr->surname,namePtr->id);
         namePtr = namePtr->name_next;
		 i++;   
      } 
      printf("\n");
      puts("The list in surname-alphabetical order:");
	  //surname
      int j = 1;
      while (surnamePtr != NULL) { 
         printf("\t%d. %s %s\t%ld\n", j,surnamePtr->name,surnamePtr->surname,surnamePtr->id);
         surnamePtr = surnamePtr->surname_next;
		 j++;   
      } 
      
      printf("\n");
      puts("The list in ID sorted order:");
      //id
	  int k = 1;
      while (idPtr != NULL) { 
         printf("\t%d. %s %s\t%ld\n", k,idPtr->name,idPtr->surname,idPtr->id);
         idPtr = idPtr->id_next;
		 k++;   
      } 
	  printf("\n");
}
   
}
