#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Node{
	char name[20];
	struct Node* next;
	int weight;
	int index;
};

struct Graph{
	int size;
	struct Node* arr;
	int visited;
};
void dfs(struct Graph* g, int iv);
struct Node* allocateNode(char str[20],int w,int index);
struct Graph* allocateGraph(int n);
void addNewEdge(struct Graph* g, char str[20], char nNode[20],int weight);
void swap(struct Node* a, struct Node* b);
void bubbleSort(struct Graph* g);
void freeGraph(struct Graph* g);


void dfs(struct Graph* g, int iv){
	struct Node* list = g[iv].arr;
	struct Node* ptr = list;
	g[iv].visited = 1;
	printf("%s ", list->name);
	while(ptr!=0){
		if(g[ptr->index].visited == 0){
			dfs(g,ptr->index);
		}
		ptr = ptr->next;
	}	
}

struct Node* allocateNode(char str[20],int w,int index){
	struct Node* temp = malloc(sizeof(struct Node));
	for(int i =0;i<20;i++){
		temp->name[i] = str[i];
	}
	temp->next = 0;
	temp-> weight = w;
	temp->index = index;
	return temp;
}

struct Graph* allocateGraph(int n){
	struct Graph* g = malloc(n*sizeof(struct Graph));
	 g->size = n;
	for(int i =0; i < n; i++){ 
		g[i].arr = 0;
		g[i].visited = 0;
	}
	return g;
}

void addNewEdge(struct Graph* g, char str[20], char nNode[20],int weight) {
        int index;
        for(int i = 0; i < g->size; i++){
                if(strcmp(g[i].arr->name, nNode) == 0){
                        index = i;
                        break;
                }
        }
        struct Node* newNode = allocateNode(nNode,weight, index);
        for(int i = 0; i < g->size; i++){
                if(strcmp(g[i].arr->name, str) == 0){
                        struct Node* ptr = g[i].arr;
                        while(ptr->next!=0){
                                if(strcmp(ptr->next->name, nNode) < 0){
                                        ptr = ptr->next;
                                } else {
                                        break;
                                }
                        }
                        newNode -> next = ptr->next;
                        ptr->next = newNode;
                        break;
                }
        }
}

void swap(struct Node* a, struct Node* b){
	char temp[20];
	strcpy(temp,a->name);
	strcpy(a->name,b->name);
	strcpy(b->name,temp);
}

void bubbleSort(struct Graph* g){
	
	struct Node* ptr1;
	struct Node* ptr2;
	for(int i = 0; i < g->size-1; i++){
		for(int j = 0; j< g->size - i+1; j++){
			ptr1 = g[i].arr;
			ptr2 = g[i+1].arr;

			if(strcmp(ptr1->name,ptr2->name) > 0){
				swap(ptr1,ptr2);
			}
		}
	}
}

void freeGraph(struct Graph* g){
        for(int i = 0; i < g->size; i++){
                struct Node* temp = g[i].arr;
                while(temp != 0){
                        struct Node* ptr = temp;
                        temp = temp->next;
                        free(ptr);
                }
        }
        free(g);
}

int main(int argc, char* argv[argc+1]){
	if(argc < 2){
		printf("insufficient arguements");
		return EXIT_SUCCESS;
	}
	FILE* fp1 = fopen(argv[1],"r");
	int w;
	int s;
	fscanf(fp1,"%d\n", &s);

	struct Graph* g = allocateGraph(s);
	char vert[20];
	char edge[20];
	
	for(int i = 0; i< s;i++){
		fscanf(fp1, "%s\n", vert);	
		g[i].arr = allocateNode(vert,0,i);
	}
	for(int i = 0; i< s/5;i++){
	bubbleSort(g);
	}
	while(fscanf(fp1,"%s %s %d\n", vert, edge, &w)!=EOF){
		addNewEdge(g,vert,edge,w);

	}
	fclose(fp1);
	for(int i = 0; i< g-> size;i++){
		if(g[i].visited == 0){
			dfs(g,i);
		}
	}
	printf("\n");
	freeGraph(g);
}
