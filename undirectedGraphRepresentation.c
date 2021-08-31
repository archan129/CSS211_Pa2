#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Node{
	char name[20];
	struct Node* next;
};

struct Graph{
	//int size;
	struct Node* arr;
};
void freeNodes(struct Graph* g,int size);
struct Node* allocateNode(char str[20]);
struct Graph* allocateGraph(int n);
void addNewEdge(struct Graph* g, char s[20], char newEdge[20],int size);
void printG(struct Graph* g,char aord, char vert[20],int size);

struct Node* allocateNode(char str[20]){
	struct Node* temp = malloc(sizeof(struct Node));
	for(int i =0;i<20;i++){
		temp->name[i] = str[i];
	}
	temp->next = 0;
	return temp;
}

struct Graph* allocateGraph(int n){
	struct Graph* g = malloc(n*sizeof(struct Graph));
	// g->size = n;
	for(int i =0; i < n; i++){ 
		 g[i].arr = 0;
	}
	return g;
}

void addNewEdge(struct Graph* g, char s[20], char newEdge[20],int size){
	struct Node* newNode = allocateNode(newEdge);
	for(int i =0; i < size; i++){
		struct Node* ptr = g[i].arr;
		if(strcmp(ptr->name, s) == 0){
			while(ptr->next!=0 && strcmp(ptr->next->name, newEdge) == -1){
				ptr=ptr->next;
			}
			newNode->next = ptr->next;
			ptr->next = newNode;
			return;
		}
	
	}
	return;
}

void printG(struct Graph* g,char aord, char vert[20],int size){
	struct Node* ptr;
	int count =0;
	for(int i =0; i< size; ++i){
		if(strcmp(g[i].arr->name,vert) == 0){
			ptr = g[i].arr->next;
			while(ptr!=0){
				if(aord == 'a'){
					printf("%s ", ptr->name);
				}else if(aord == 'd'){
					count++;
				}
				ptr = ptr->next;
			}
		}
	}
	if(aord == 'd'){
		printf("%d",count);	
	}
	printf("\n");

	
}

void freeNodes(struct Graph* g,int size){
	for(int i =0;i<size;i++){
		struct Node* a = g[i].arr;
		while(a!=0){
			struct Node* pointer = a;
			a = a->next;
			free(pointer);
		}
	}
	free(g);
}


int main(int argc, char* argv[argc+1]){
	if(argc < 3){
		printf("insufficient arguements");
		return EXIT_SUCCESS;
	}

	FILE* fp1 = fopen(argv[1],"r");
	int s;
	fscanf(fp1,"%d\n", &s);

	struct Graph* g = allocateGraph(s);
	char vert[20];
	char edge[20];
	
	for(int i = 0; i< s;i++){
		fscanf(fp1, "%s\n", vert);	
		g[i].arr = allocateNode(vert);
	}
	while(fscanf(fp1,"%s %s\n", vert, edge)!=EOF){
		addNewEdge(g,vert,edge,s);
		addNewEdge(g,edge,vert,s);
	}
	fclose(fp1);

	FILE* fp2 = fopen(argv[2], "r");
	char aord;
	while(fscanf(fp2, "%c %s\n", &aord, vert)!=EOF){
		printG(g,aord,vert,s);
	}

	
	fclose(fp2);
	freeNodes(g,s);
	return EXIT_SUCCESS;
}
