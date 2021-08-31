#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node{ 
        char name[20];
        struct Node* next;
        int index;
        int weight;
};

struct Graph{
        int size;
        struct Node* arr;
        int* visited;
};

struct Node* allocateNode(char name[20], int index, int w);
struct Graph* createGraph(int n);
void addNewEdge(struct Graph* g, char src[20], char dest[20], int weight);
void freeGraph(struct Graph* g);
int shortestDistance(int dist[], struct Graph* g);
void djikstra(struct Graph* g, int srcIndex);
void swap(struct Node* one, struct Node* two);
void sort(struct Graph* g);

struct Node* allocateNode(char name[20], int index, int w) {
        struct Node* temp = malloc(sizeof(struct Node));
        for(int i = 0; i < 20; i++){
                temp -> name[i] = name[i];
        }
        temp->next = 0;
        temp->index = index;
        temp->weight = w;
        return temp;
}

struct Graph* createGraph(int n) {
        struct Graph* g = malloc(n * sizeof(struct Graph));
        g->size = n;

        g->visited = malloc(n * sizeof(int));

        for(int i = 0; i < n; i++){
                g->visited[i] = 0;
        }

        for (int i = 0; i < n; i++){
                g[i].arr = 0;
        }
        return g;
}

void addNewEdge(struct Graph* g, char src[20], char dest[20], int weight) {
        int index;
        for(int i = 0; i < g->size; i++){
                if(strcmp(g[i].arr->name, dest) == 0){
                        index = i;
                        break;
                }
        }
        struct Node* newNode = allocateNode(dest, index, weight);
        for(int i = 0; i < g->size; i++){
                if(strcmp(g[i].arr->name, src) == 0){
                        struct Node* trav = g[i].arr;
                        while(trav->next!=0){
                                if(strcmp(trav->next->name, dest) < 0){
                                        trav = trav->next;
                                } else {
                                        break;
                                }

                        }
                        newNode -> next = trav->next;
                        trav->next = newNode;
                        break;
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
        free(g->visited);
        free(g);
}

int shortestDistance(int dist[], struct Graph* g){
	int temp = 10000000;
	int index = 0;
	for(int i = 0;i<g->size;i++){
		if(g->visited[i] == 0){
			if(dist[i] < temp){
				temp = dist[i];	
				index  = i;		
			}
		}
	}
	return index;
}

void djikstra(struct Graph* g, int srcIndex){
	int dist[g->size];

	for(int i = 0; i< g->size;i++){
		g->visited[i] = 0;
		if(i != srcIndex){		
			dist[i] = 10000000;
		}else{
			dist[i] = 0;
		}
	}
	
	int smallestIndex;
	for(int i = 0; i< g->size;i++){
		smallestIndex = shortestDistance(dist, g);
		struct Node* ptr = g[smallestIndex].arr;
		while(ptr!=0){
			if(g->visited[ptr->index] == 0){ 
				g->visited[smallestIndex] = 1;
				if(dist[ptr->index] > dist[smallestIndex] + ptr->weight){
                                	dist[ptr->index] = dist[smallestIndex] + ptr->weight;
                        	}
			}
			ptr= ptr->next;
		}
	}
	 for(int i = 0; i < g->size; i++){
                if(dist[i] == 10000000){
                        printf("%s INF\n", g[i].arr->name);
                } else {
                        printf("%s %d\n", g[i].arr->name, dist[i]);
                }
        }
	printf("\n");
}

void swap(struct Node* one, struct Node* two){
        char temp[20];
        strcpy(temp,one->name);
        strcpy(one->name,two->name);
        strcpy(two->name,temp);
}

void sort(struct Graph* g){
        struct Node* temp;
        struct Node* ptr;
        for(int i = 0; i < g->size-1; i++){
                for(int j = 0; j < g->size - i+1; j++){
                        temp = g[i].arr;
                        ptr = g[i+1].arr;

                        if(strcmp(temp->name,ptr->name) > 0){
                                swap(temp,ptr);
                        }
                }
        }
}

int main(int argc, char* argv[argc+1]){
        if(argc < 3){
                printf("insufficient arguements\n");
                return EXIT_SUCCESS;
        }

        FILE* fp = fopen(argv[1], "r");

        int s;
        fscanf(fp,"%d \n", &s);
        struct Graph* g = createGraph(s);

        char listName[20];
        char A[20];
        char B[20];

        for(int i = 0; i < s; i++){
                fscanf(fp,"%s \n", listName);
                g[i].arr = allocateNode(listName, i, 0);
        }

        for(int i = 0; i < g->size/4; i++){
                sort(g);
        }

        int w;
        while(fscanf(fp,"%s %s %d\n", A, B, &w) != EOF){
                addNewEdge(g, A, B, w);
        }

        fclose(fp);
        FILE* fp2 = fopen(argv[2], "r");
        int startsize;

        
        while(fscanf(fp2, "%s\n", listName)!= EOF){
                for(int i = 0; i < g->size; i++){
                        if(strcmp(g[i].arr->name, listName) == 0){
                                startsize = g[i].arr->index;
                                djikstra(g,startsize);
                        }
                }
                
        }
        fclose(fp2);
        freeGraph(g);
        return EXIT_SUCCESS;
}
