/* NAME-SURNAME: Hasan Senyurt - Hasan Mert Yalcin - Melis Cirpan
   ID:			 150120531     - 150119647         - 150119669
   
   Our algortihm is based on indices of vertices. Every letter converted to indices to create adjacency matrix easily. First, vertices are
   sorted ascedantly. Then they are converted to integers (indices). After that, all operations will be based on indices.
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
#define INFINITY 9999


char vertices[SIZE]; //list of vertices. for example: [A,B,C,D...]
char vertex[SIZE][2]; //list of taken input of two vertices. for example {{AB},{AC}....}
int vertex_index[SIZE][2]; //list of indices of taken input of two vertices. for example {{01},{02}....} 0 = A, 1 = B... for creating adjacency matrix.
int adjacency_matrix[SIZE][SIZE]; //adjacency matrix of taken all inputs.
int lengths[SIZE]; //lengths of given inputs. for example {1,12,15,...} 1 is length of {01}. {01} means {AB}.

//to generalize, all taken inputs are converted to indices. A is 0, B is 1, C is 2. It makes creating adjacency matrix easier.

int size = 0; //row size of taken inputs from user. 
int vertex_size = 0; //size of number of vertices. (A,B,C) -> vertex_size = 3.
int length_size= 0; //size of taken length inputs (2,12,5) -> length_size = 3. 

//function for reading input file.
void read_input(char file[SIZE]);
//function for sorting vertices as ascendant. like A,B,C,D,E.
void selectionSort(char list[], int list_size);
//function for printing matrix.
void print_matrix(int matrix[SIZE][2],int matrix_size,char vertices[SIZE],int vertex_size,int length[SIZE],int length_size,int choice);
//function for applying dijkstra algorithm.
void dijkstra(int adj_matrix[SIZE][SIZE], int graph_size, int source, int dest);
//main menu function.
void instructions();


int main(){

	char file[SIZE];
	int choice;
	instructions();
	
	//main menu
	while(choice != 4){
		printf("Please enter the number: ");
		scanf("%d",&choice);
		
		//reading input
		if(choice == 1){
			
			printf("Name of the input file: ");
			scanf("%s",file);
			read_input(file);
			print_matrix(vertex_index,size,vertices,vertex_size,lengths,length_size,0);
			instructions();
			
		}
		//printing matrix
		else if(choice == 2){
			
			print_matrix(vertex_index,size,vertices,vertex_size,lengths,length_size,1);
			instructions();
			
		}
		//finding shortest path
		else if(choice == 3){
			
			char source,dest;
			printf("Enter the source vertex: ");
			scanf(" %c",&source);
			
			printf("Enter the destination vertex: ");
			scanf(" %c",&dest);
			int sourceI,destI;
			
			//converting char source and destination inputs to indices. (A -> 0, E ->4 ...)
			int row;
			for(row=0;row<vertex_size;row++){
				if(source == vertices[row]){
					sourceI = row;
					break;
				}
			}
			
			for(row=0;row<vertex_size;row++){
				if(vertices[row] == dest){
					destI = row;
					break;
				}
			}
			
			//applying dijkstra algortihm.
			dijkstra(adjacency_matrix,vertex_size,sourceI,destI);
			instructions();
			
		}
		//quiting the program.
		else{
			
			if(choice != 4){
				printf("Please enter valid number!\n");
				instructions();
			}
		}
	}
	
	return 0;
}

//main menu function.
void instructions(){
	printf("\nRead File : 1\nShow adjacency matrix: 2\nFind shortest path: 3\nExit: 4\n");
}

//this function takes an input as string and uses it to open a file.
void read_input(char file[SIZE]){
	
	FILE *input;
	
	if((input = fopen(file,"r")) == NULL){
		printf("\nInput file could not be opened!\n");
	}
	
	else{
		printf("\n%s is successfully opened!\n",file);
		int length;
		char first,second;
		
		while(!feof(input)){
			
			//taking vertices and lengths.
			fscanf(input,"%c,%c,%d ",&first,&second,&length);
			
			//adding vertices to a list.
			vertex[size][0] = first;
			vertex[size][1] = second;
			size++;
			
			//adding lengths to a list.
			lengths[length_size] = length;
			length_size++;
			
			//controlling vertices whether is in list or not. If it is in list then it cannot be inserted to a list. For example vertices list is {A,B,C},
			//when B is input then it cannot be inserted. If D is an input, it can be inserted. Vertices list takes inputs from input file that entered by user.
			int frst = 0;
			int scnd = 0;
			int j;
			
			for(j=0;j<vertex_size;j++){
				if(vertices[j] == first){
					frst = 1;
					break;
				}
			}
			
			for(j=0;j<vertex_size;j++){
				if(vertices[j] == second){
					scnd = 1;
					break;
				}
			}
			
			//adding vertices to vertices list.
			if(!frst){
				vertices[vertex_size] = first;
				vertex_size++;
			}
			
			if(!scnd){
				vertices[vertex_size] = second;
				vertex_size++;
			}
		}
		
		//sorting vertices as ascendant.
		selectionSort(vertices,vertex_size-1);
		
		//converting char vertices (A,B,C..) to integer indices.(0,1,2...)
		int row,column;
		int vert_ind;
		
		for(row=0;row<size;row++){
			
			for(column = 0;column<2;column++){
				
				for(vert_ind=0;vert_ind<vertex_size;vert_ind++){
					
					if(vertex[row][column] == vertices[vert_ind]){
						
						vertex_index[row][column] = vert_ind;
					}
				}
			}
		}
	}
	
}

//this function takes inputs as list and size to sort list as ascendant.
void selectionSort(char list[], int list_size)
{
    int x, y;
 	int minimum_index;
    
    for (x = 0; x < list_size - 1; x++) {
    	
        // Finding minimum element in unsorted vertices list.
        minimum_index = x;
        
        for (y = x + 1; y < list_size; y++)
            if (list[y] < list[minimum_index])
                minimum_index = y;
        
 		//swaping vertices.
        char *a = &list[minimum_index];
        char *b = &list[x];
        
        char temp = *a;
        *a = *b;
        *b = temp;
        
    }
}

/*this function takes inputs as matrix which contains indices of vertices {{01},{03}...}, size of that matrix, list of vertices {A,B,C...}, size of that vertices list
  list of lengths between two vertices {1,2,5,12...} and size of that length list.
*/
void print_matrix(int matrix[SIZE][2],int matrix_size,char vertices[SIZE],int vertex_size,int length[SIZE],int length_size,int choice){
	
	//creating adjacency matrix with all zero values.
	int i =0,j=0;
	
	for(;i<vertex_size;i++){
		for(;j<vertex_size;j++){
			adjacency_matrix[i][j] = 0;
			
		}
	}
	
	//inserting lengths between vertices to adjacency matrix.
	int length_index = 0;
	
	for(i=0;i<matrix_size;i++){
		//matrix list has information about indices of vertices. algortihm is all about that. turning letters to indices and creating adjacency matrix according to them.
		adjacency_matrix[matrix[i][0]][matrix[i][1]] = length[length_index];
		
		adjacency_matrix[matrix[i][1]][matrix[i][0]] = length[length_index];
		
		length_index++;
	}
	
	//adjusting printing adjacency matrix. when user enters 2 at main menu, then it prints.
	if(choice == 1){
	
		for(i=0;i<vertex_size;i++){
			
			printf("\t%c",vertices[i]);
			
		}
		printf("\n");
		
		for(i=0;i<vertex_size;i++){
			
			printf("%c\t",vertices[i]);
			
			for(j= 0;j<vertex_size;j++){
				
				//chancing zero values to '-'.
				if(adjacency_matrix[i][j] == 0){
					printf("-\t");
				}
				
				else{
					printf("%d\t",adjacency_matrix[i][j]);
				}	
			}
			printf("\n");
		}
	}
}

//this function takes inputs as adjacency matrix, length of it, source vertex and destination vertex. It uses dijkstra algortihm to calculate shortest 
//distance between source vertex and destination vertex.
void dijkstra(int adj_matrix[SIZE][SIZE], int graph_size, int source, int dest){
	
	int graph[graph_size][graph_size]; //2d matrix that contains values of distances between all edges.(infinity,2,3....)
	int row,column;
	
	//inserting infinity to neighbours that is not connected with source vertex and inserting lengths to neighbours that is connected with source vertex.
	for(row=0;row < graph_size;row++)
	
		for(column=0;column < graph_size;column++)
		
			if(adj_matrix[row][column]==0)
				graph[row][column]=INFINITY;
			else
				graph[row][column]=adj_matrix[row][column];
	
				
	int length_edges[graph_size]; //list that represents length between source and other vertices. (that can be infinity,1,2,..)
	int distance_to_all[graph_size]; //list that represents shortest length between source and other vertices. (final distance. cannot be an infinity if there is a path.)
	int visited_vertices[graph_size]; //list that represents visited vertices. (1 if it is visited, 0 if it is not visited.)
	
	int i = 0,j;
	//adjusting lists that is above.
	
	while(i<graph_size){
		
		visited_vertices[i] = 0;
		length_edges[i] = graph[source][i];
		distance_to_all[i]=source;
		i++;
		
	}
	
	int count, minimumdistance, next_vertex;
	count=1;
	
	visited_vertices[source]=1; //source cannot be visited.
	length_edges[source]=0; //length between source and source is not valid.
	
	while(count < graph_size-1){
		
		minimumdistance=INFINITY;
		//control and assign mechanism for visited edges.
		i = 0;
		
		while(i<graph_size){
			
			if((length_edges[i] < minimumdistance) && !visited_vertices[i])
			{
				minimumdistance=length_edges[i];
				next_vertex=i;
			}
			i++;
		}
		
		//assinging 1 if the vertex is visited.
		visited_vertices[next_vertex]=1;
		i=0;
		
		while(i<graph_size){
			
			if(!visited_vertices[i])
				//checking distances. 
				if(minimumdistance+graph[next_vertex][i] < length_edges[i])
				{
					length_edges[i]=minimumdistance+graph[next_vertex][i]; //finding shortest distances.
					distance_to_all[i]=next_vertex;
				}
			i++;
			
		}
			count++;
	}
	
	printf("\nDistance between %c and %c = %d", vertices[source],vertices[dest], length_edges[dest]);
	printf("\n");
	printf("\nShortest path between %c and %c =\n", vertices[source],vertices[dest]);
	
	char path[SIZE];
	int path_size = 1;
	path[0] = vertices[dest];
	i = 1;
	// Creating the path.
	do{
		
		dest=distance_to_all[dest];
		path[i] = vertices[dest];
		i++;
		path_size++;
		
	}
	while(dest!=source);
	
	printf("\n");
	
	//printing path reversed.
	for(i=path_size-1;i>=0;i--){
		
		if(i != 0)
			printf("%c ---> ",path[i]);
		else if(i == 0)
			printf("%c\n",path[i]);
			
	}
	
}
