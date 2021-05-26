/* NAME-SURNAME: Hasan Þenyurt - Hasan Mert Yalçýn - Melis Çýrpan
   ID:			 150120531     - 150119647         - 150119669
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product{
	int id;
	char name[50];
	char category[50];
	int price;
	struct product *next;
};
struct basket{
	int id;
	struct product *productlist;
	int amount;
	struct basket *next;
};
struct customer{
	int id;
	char name[50];
	char surname[50];
	struct basket *basketlist;
	struct customer *next;
};

typedef struct customer customer;
typedef customer *customerPtr;

typedef struct product product;
typedef product *productPtr;

typedef struct basket basket;
typedef basket *basketPtr;

//functions for customers
void insertCustomer(customerPtr *cPtr, int id, char name[50], char surname[50]);
void deleteCustomer(customerPtr *cPtr, char name[50],char surname[50]);
void printCustomers(customerPtr cPtr);
int controlCustomer(customerPtr cPtr,char name[],char surname[]);
int checkID(customerPtr cPtr);

//functions for baskets
int checkBasketID(customerPtr cPtr,int customerID);
basketPtr AddProducts(int id, int list[],int size,productPtr pPtr,int control);
void addBasket(customerPtr cPtr,basketPtr *bPtr,int customer_id);
void listAmount(customerPtr cPtr);

//functions for products
void spesificProduct(customerPtr cPtr,int id);
void insertProduct(productPtr *pPtr, int id, char name[50],char category[50],int price);
void printProducts(productPtr pPtr);

//main menu function
void instructions(){
	printf("\nAdd a customer : 1\nAdd basket: 2\nRemove Customer: 3\nList the customers who bought a specific product: 4\nList the total shopping amounts of each customer: 5\nExit: 6\n");
}

int main(){
	
	customerPtr customer_head = NULL;
	productPtr product_head = NULL;

	//taking products from the input file.
	FILE *products = fopen("product.txt","r");
	int id;
	char name[50];
	char category[50];
	int price;
	
	while(!feof(products)){
		fscanf(products,"%d\t%s\t%s\t%d ",&id,name,category,&price);
		insertProduct(&product_head,id,name,category,price);
		
	}
	fclose(products);
	
	//taking customers from the input file.
	FILE *customers = fopen("customer.txt","r");
	char surname[50];
	while(!feof(customers)){
		fscanf(customers,"%d\t%s\t%s ",&id,name,surname);
		insertCustomer(&customer_head,id,name,surname);
	}
	fclose(customers);
	
	//taking basket records from the input file.	
	FILE *baskets = fopen("basket.txt","r");
	int customer_id;
	int product_id;
	
	//products are listed in arrays. after that they are sent into function about adding products. (AddProducts).
	int control;
	int control2;
	fscanf(baskets,"%d\t%d\t%d ",&customer_id,&id,&product_id);
	//these control variables are for file i/o processes.
	control = customer_id;
	control2 = id;

	while(!feof(baskets)){
		int productarray[50]; //product array
		int a = 0;
		//every basket will be seperated with this algorithm.
		while(customer_id == control && id == control2 && !feof(baskets)){
			productarray[a] = product_id;
			a++;
			fscanf(baskets,"%d\t%d\t%d",&customer_id,&id,&product_id);
			
		}
		//adding baskets to customers.
		basketPtr bask = AddProducts(control2,productarray,a,product_head,0);
		addBasket(customer_head,&bask,control);
		
		control = customer_id;
		control2 = id;
	}
	fclose(baskets);
		
	instructions();
	int choice;
	
	//main menu.
	while(choice != 6){
		scanf("%d",&choice);
		
		//adding customers.
		if(choice == 1){
			puts("");
			printCustomers(customer_head);
			puts("");
			printf("Name Surname: ");
			
			char name1[50];
			char surname1[50];
			scanf("%s %s",name1,surname1);
			
			if(!controlCustomer(customer_head,name1,surname1))
				insertCustomer(&customer_head,checkID(customer_head),name1,surname1);
			else
				printf("%s %s is already inserted.\n",name1,surname1);
			puts("");
			
			printCustomers(customer_head);
			instructions();
		}
		
		//adding baskets.
		else if(choice == 2){
			puts("");
			printCustomers(customer_head);
			puts("");
			printf("Select one customer (id): ");
			
			int c_id;
			scanf("%d",&c_id);
			puts("");
			
			printProducts(product_head);
			
			int p_id;
			int listproduct[50];
			puts("");
			int size = 0;
			
			while(p_id != -1){
				printf("Select one product (id), for exit enter -1: ");
				scanf("%d",&p_id);
				
				if(p_id != -1){
					listproduct[size] = p_id;
					size++;	
				}
			}
			
			basketPtr addbasket = AddProducts(checkBasketID(customer_head,c_id),listproduct,size,product_head,1);
			addBasket(customer_head,&addbasket,c_id);
			puts(" ");
			instructions();
			
		}
		
		//removing customers.
		else if(choice == 3){
			puts("");
			printCustomers(customer_head);
			puts("");
			
			char delete_name[50];
			char delete_surname[50];
			printf("Name Surname: ");
			scanf("%s %s",delete_name,delete_surname);
			puts("");
			
			if(controlCustomer(customer_head,delete_name,delete_surname))
				deleteCustomer(&customer_head,delete_name,delete_surname);
			else
				printf("%s %s is not in the list.\n",delete_name,delete_surname);
			
			puts("");
			printCustomers(customer_head);
			instructions();
		}
		
		//printing spesific product that was bought by customers.
		else if(choice == 4){
			puts("");
			printProducts(product_head);
			puts("");
			
			printf("Please enter product id: ");
			int p_id;
			scanf("%d",&p_id);
			puts("");
			spesificProduct(customer_head,p_id);
			instructions();
		}
		
		//every customers' amount of shopping.
		else if(choice == 5){
			puts("");
			listAmount(customer_head);
			instructions();
		}
	}
		
	return 0;
}

//this function insert new customer to list by taking name and surname as an input.
void insertCustomer(customerPtr *cPtr, int id, char name[50], char surname[50]){
	customerPtr newPtr = malloc(sizeof(customer));
	
	if (newPtr != NULL) {
		
		newPtr->id = id;
		strcpy(newPtr->name,name);
		strcpy(newPtr->surname,surname);
		newPtr->next = NULL;
		newPtr->basketlist = NULL;
		
		customerPtr previousPtr = NULL;
      	customerPtr customer_head = *cPtr;
      	
      	while (customer_head != NULL && id > customer_head->id) {
         previousPtr = customer_head;              
         customer_head = customer_head->next;
      	}                                          

	    if (previousPtr == NULL) { 
	        newPtr->next = *cPtr;
	        *cPtr = newPtr;
	    }	
	    else {
	        previousPtr->next = newPtr;
	        newPtr->next = customer_head;
	    }
	}
	else{
		printf("%d %s %snot inserted. No memory available.\n",id, name,surname);
	}
	
}

//this function deletes spesific customers by taking name and surname as an input.
void deleteCustomer(customerPtr *cPtr, char name[50],char surname[50]){
		
		if (!strcmp(name,(*cPtr)->name)) { 
	      customerPtr tempPtr = *cPtr;
		  *cPtr = (*cPtr)->next;
	      printf("The customer '%d %s %s' is deleted from the list!\n",tempPtr->id,tempPtr->name,tempPtr->surname);
	      free(tempPtr);
	      
	   }
	  
	   else { 
	      customerPtr previousPtr = *cPtr;
	      customerPtr currentPtr = (*cPtr)->next;
	
	      
	      while (currentPtr != NULL && !strcmp(currentPtr->name,name) == 0) { 
	         previousPtr = currentPtr; 
	         currentPtr = currentPtr->next; 
	      } 
	      
	      if (currentPtr != NULL) { 
	         customerPtr tempPtr = currentPtr;
	         previousPtr->next = currentPtr->next;
	         printf("The student '%d %s %s' is deleted from the list!\n",tempPtr->id,tempPtr->name,tempPtr->surname);
	         free(tempPtr);	         
	         
	      } 
	   }	
}

//this function prints customers.
void printCustomers(customerPtr cPtr){
	if(cPtr == NULL){
		puts("List is empty.");
	}
	else{
		while (cPtr != NULL) { 
         printf("%d\t%s\t%s \n", cPtr->id,cPtr->name,cPtr->surname);
         cPtr = cPtr->next;   
      }   
	}
}

//this function checks whether inputs that is given by user is in the customer list or not.
int controlCustomer(customerPtr cPtr,char name[],char surname[]){
	
	customerPtr current = cPtr;
	int control = 0;
	
	while(current != NULL){
		
		if(!strcmp(name,current->name) && !strcmp(surname,current->surname)){
			control = 1;
			break;
		}
		else{
			control = 0;
		}
		
		current = current->next;
	}
	return control;
}

//this function finds the last customer's id to finding new id that is used when new customer is inserted.
int checkID(customerPtr cPtr){
	
	int customerNumber = 0;
	customerPtr current = cPtr;
	
	while(current != NULL){
		customerNumber = current->id + 1;
		current = current->next;
	}
	return customerNumber;
}

//this function finds the last basket's id that is inserted to customer to finding id that is used when new basket is inserted.
int checkBasketID(customerPtr cPtr,int customerID){
	
	int id;
	customerPtr current = cPtr;
	
	while(current != NULL){
		basketPtr bcurrent = current->basketlist;
		
		if(customerID == current->id){
			
			if(bcurrent == NULL){
				id = 1;
			}
			
			else{
				while(bcurrent != NULL){
					id = bcurrent->id + 1;
					bcurrent = bcurrent->next;
				}	
			}	
		}
		current = current->next;
	}
	return id;
}

//this function creates basket and inserts products to it.
basketPtr AddProducts(int id, int list[],int size,productPtr pPtr,int control){
	
	basketPtr newPtr = malloc(sizeof(basket));
	int amount = 0;
	newPtr->id = id;
	newPtr->productlist = NULL;
	
	int i;
	//adding products one by one to basket.
	for(i=0;i<size;i++){
		//finding product from product list.
		if(pPtr->id == list[i]){
			
			productPtr proPtr = malloc(sizeof(product));
			
			proPtr->id = pPtr->id;
			proPtr->next = NULL;
			strcpy(proPtr->name,pPtr->name);
			strcpy(proPtr->category,pPtr->category);
			proPtr->price = pPtr->price;
			amount += proPtr->price;
			
			productPtr previousPtr = NULL;
	      	productPtr currentPtr = newPtr->productlist;
	      	//adding product to basket.
	      	while (currentPtr != NULL && proPtr->id > currentPtr->id) {
	         previousPtr = currentPtr;              
	         currentPtr = currentPtr->next;
	      	}                                          
	
		    
		    if (previousPtr == NULL) { 
		        proPtr->next = newPtr->productlist;
		        newPtr->productlist = proPtr;
		        
		    }
			
		    else {
		        previousPtr->next = proPtr;
		        proPtr->next = currentPtr;
		        
		    }
					
			 
		}
		else{
			//finding product from product list.
			productPtr previousPtr = pPtr;
			productPtr currentPtr = pPtr->next;
			
			
			while (currentPtr != NULL && currentPtr->id != list[i]) { 
			    previousPtr = currentPtr;  
			    currentPtr = currentPtr->next;  
			}
			
			productPtr proPtr = malloc(sizeof(product));
			
			proPtr->id = currentPtr->id;
			proPtr->next = NULL;
			strcpy(proPtr->name,currentPtr->name);
			strcpy(proPtr->category,currentPtr->category);
			proPtr->price = currentPtr->price;
			
			amount += proPtr->price;
		
			productPtr previousPtr1 = NULL;
	      	productPtr currentPtr1 = newPtr->productlist;
	      	
	      	//adding product to a basket.
	      	while (currentPtr1 != NULL && proPtr->id > currentPtr1->id) {
	         previousPtr1 = currentPtr1;              
	         currentPtr1 = currentPtr1->next;
	      	}                                          
		    
		    if (previousPtr1 == NULL) { 
		        proPtr->next = newPtr->productlist;
		        newPtr->productlist = proPtr;   
		    }
		    else {
		        previousPtr1->next = proPtr;
		        proPtr->next = currentPtr1;
		        
		    }
		
		}
	}
	newPtr->amount = amount;
	//control mechanism for printing amount after function does its job. (if this function is used for taking inputs from file,
	//then it will not print amount, but if it is used by user then it will print the amount.
	if(control == 1){
		printf("\nTotal amount = %d",amount);
	}
	else{
		//
	}
	return newPtr;	
}

//this function adds baskets to customers.
void addBasket(customerPtr cPtr,basketPtr *bPtr,int customer_id){
	
	//finding customer
	if(customer_id == cPtr->id){
		
		basketPtr previousPtr = NULL;
      	basketPtr basket_head = cPtr->basketlist;
      	
      	//adding basket according to id. (ascending)
      	while (basket_head != NULL && (*bPtr)->id > basket_head->id) {
         previousPtr = basket_head;              
         basket_head = basket_head->next;
      	}                                          

	    if (previousPtr == NULL) { 
	        (*bPtr)->next = cPtr->basketlist;
	        cPtr->basketlist = (*bPtr);
	        
	    }
		
	    else {
	        previousPtr->next = (*bPtr);
	        (*bPtr)->next = basket_head;
	        
	    }
	    
	}
	else{
		//finding customer
		customerPtr previousPtr = NULL;
	    customerPtr customer_head = cPtr;
	      	
	    while (customer_head != NULL && customer_id != customer_head->id) {
	        previousPtr = customer_head;              
	        customer_head = customer_head->next;
	    }
	    
	    basketPtr previousPtr1 = NULL;
      	basketPtr basket_head1 = customer_head->basketlist;
      	
      	//adding basket according to id. (ascending)
      	while (basket_head1 != NULL && (*bPtr)->id > basket_head1->id) {
         previousPtr1 = basket_head1;              
         basket_head1 = basket_head1->next;
      	}                                          

	    
	    if (previousPtr1 == NULL) { 
	        (*bPtr)->next = customer_head->basketlist;
	        customer_head->basketlist = (*bPtr);
	        
	    }
		
	    else {
	        previousPtr1->next = (*bPtr);
	        (*bPtr)->next = basket_head1; 
	    }	
	}	
}

//this function prints all shoppings amount of all of customers.
void listAmount(customerPtr cPtr){
	customerPtr current = cPtr;
	
	while(current != NULL){
		basketPtr bcurrent = current->basketlist;
		int amount = 0;
		
		while(bcurrent != NULL){
			amount += bcurrent->amount;
			bcurrent = bcurrent->next;
		}
		
		if(amount != 0)
			printf("%d %s %s's total amount is = %d\n",current->id,current->name,current->surname,amount);
		else
			printf("%d %s %s has no shopping!\n",current->id,current->name,current->surname);
			
		current = current->next;
	}
	
}

//this function prints customer that have bought spesific product.
void spesificProduct(customerPtr cPtr,int id){
	
	customerPtr current = cPtr;
	
	while(current != NULL){
		basketPtr bcurrent = current->basketlist;
		
		while(bcurrent != NULL){
			productPtr pcurrent = bcurrent->productlist;
			
			while(pcurrent != NULL){
				
				if(pcurrent->id == id){
					printf("%d %s %s bought that item!\n",current->id,current->name,current->surname);
					break;
				}
				else{
					
					pcurrent = pcurrent->next;
				}
			}
			bcurrent = bcurrent->next;
		}
		current = current->next;
	}
	
}

//this function inserts products to product list.
void insertProduct(productPtr *pPtr, int id, char name[50],char category[50],int price){
	productPtr newPtr = malloc(sizeof(product));
	
	if (newPtr != NULL) {
		
		newPtr->id = id;
		strcpy(newPtr->name,name);
		strcpy(newPtr->category,category);
		newPtr->price = price;
		
		newPtr->next = NULL;
		
		productPtr previousPtr = NULL;
      	productPtr product_head = *pPtr;
      	
      	while (product_head != NULL && (strcmp(name,product_head->name))>=0) {
         previousPtr = product_head;              
         product_head = product_head->next;
      	}                                          

	    if (previousPtr == NULL) { 
	        newPtr->next = *pPtr;
	        *pPtr = newPtr;
	    }

	    else {
	        previousPtr->next = newPtr;
	        newPtr->next = product_head;
	    }
	}
	else{
		printf("%d %s %s %d not inserted. No memory available.\n",id, name,category,price);
	}
	
}

//this function prints products.
void printProducts(productPtr pPtr){
	if(pPtr == NULL){
		puts("List is empty.");
	}
	else{
		while (pPtr != NULL) { 
         printf("%d\t%s\t%s\t%d \n", pPtr->id,pPtr->name,pPtr->category,pPtr->price);
         pPtr = pPtr->next;   
      } 
	}
}
