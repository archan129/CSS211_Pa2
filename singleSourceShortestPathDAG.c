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

struct Stack{
        int* items;
        int top;
        int size;
};
struct Node* allocateNode(char name[20], int index, int w);
struct Graph* createGraph(int n);
struct Stack* createStack(struct Graph* g);
int isEmpty(struct Stack* s);
void push(struct Stack* s, int item);
int pop(struct Stack* s);
void addNewEdge(struct Graph* g, char src[20], char dest[20], int weight);
void freeGraph(struct Graph* g);
int allVisited(struct Graph* g);
int checkCycles(struct Stack* s, struct Graph* g, int num);
int cycle(struct Graph* g, struct Stack* s);
void topologicalSort(int u, struct Graph* g, struct Stack* s);
void shortestPath(int in, struct Graph* g, struct Stack* s);
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

struct Stack* createStack(struct Graph* g) {
        struct Stack* s = malloc(g->size * sizeof(struct Stack));
        s->top = -1;
        s->items = malloc(g->size * sizeof(int));
        s->size = 0;
        return s;

}



int isEmpty(struct Stack* s) {
        if (s->top == -1){
                return 1;
        } else {
                return 0;
        }
}

void push(struct Stack* s, int item) {
        s->top++;
        s->items[s->top] = item;
        s->size++;
}

int pop(struct Stack* s) {
        int item;
        item = s->items[s->top];
        s->top--;
	s->size--;
        return item;
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



int allVisited(struct Graph* g){
	for(int i = 0;i<g->size;i++){
		if(g->visited[i] == 0){
			return 0;	
		}
	}
	return 1;
}

int checkCycles(struct Stack* s, struct Graph* g, int num){
	int c = 0;
	if(g->visited[num] == 1){
		return c;
	}else if(g->visited[num] == 0){
		c = 1;
		return c;
	}
	int i;
	g->visited[num] = 0;
	for(struct Node* ptr = g[num].arr;ptr!=0;ptr=ptr->next){
		
		for(i = 0; i<g->size;i++){
			if(strcmp(g[i].arr->name, ptr->name) == 0){
				break;
			}
		}
		c = checkCycles(s,g,i);
	}
	g->visited[i] = 1;
	push(s,g[num].arr->index);
	return c;
}

int cycle(struct Graph* g, struct Stack* s){
	int c;
	int* arr= malloc(g->size * sizeof(int));
	for(int i = 0; i< g->size;i++){
		arr[i] = -1;
	}
	while(allVisited(g) == 0){
		int i;
		for(i = 0; i<g->size;i++){
			if(g->visited[i] == 0){
				break;
			}
		}
		c = checkCycles(s,g,i);
		
	}
	return c;
}



void topologicalSort(int u, struct Graph* g, struct Stack* s) {

	
        g->visited[u] = 1;
        struct Node* temp = g[u].arr;
        while(temp != 0) {
                int v = temp->index;
                if(g->visited[v] != 1){
                        topologicalSort(v, g, s);
                }
                temp = temp->next;
        }
        push(s, u);
}

void shortestPath(int in, struct Graph* g, struct Stack* s){
        int dist[g->size];
        for(int i = 0; i < g->size; i++){
                g->visited[i] = 0;
                if(i == in){
                        dist[i] = 0;
                } else {
                        dist[i] = 10000000;
                }
        }

        for(int i = 0; i < g->size; i++){
                if(g->visited[i] == 0){
                        topologicalSort(i, g, s);
                }
        }
        struct Node* temp;
        while(isEmpty(s) != 1){
                int vertex = pop(s);
                temp = g[vertex].arr;
                while(temp != 0){
                        int weight = temp->weight;
                        if(dist[temp->index] > dist[vertex] + weight){
                                dist[temp->index] = dist[vertex] + weight;
                        }
                        temp = temp->next;
                }
        }
        for(int i = 0; i < g->size; i++){
                if(dist[i] == 10000000){
                        printf("%s INF\n", g[i].arr->name);
                } else {
                        printf("%s %d\n", g[i].arr->name, dist[i]);
                }
        }
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
                printf("Insufficient Arguements\n");
                return EXIT_SUCCESS;
        }

        FILE* fp = fopen(argv[1], "r");

        int vertices;
        fscanf(fp,"%d \n", &vertices);
        struct Graph* g = createGraph(vertices);

        char listName[20];
        char A[20];
        char B[20];

        for(int i = 0; i < vertices; i++){
                fscanf(fp,"%s \n", listName);
                g[i].arr = allocateNode(listName, i, 0);
        }

        for(int i = 0; i < g->size/4; i++){
                sort(g);
        }

        int weight;
        while(fscanf(fp,"%s %s %d\n", A, B, &weight) != EOF){
                addNewEdge(g, A, B, weight);
        }

        fclose(fp);
	printf("\n");
	struct Stack* s = createStack(g);
	/*if(cycle(g,s) == 1){
		printf("cycle\n");
	}else{*/


        FILE* fp2 = fopen(argv[2], "r");
        int startsize;

        
        
        while(fscanf(fp2, "%s\n", listName)!= EOF){
                for(int i = 0; i < g->size; i++){
                        if(strcmp(g[i].arr->name, listName) == 0){
                                startsize = g[i].arr->index;
                                break;
                        }
                }
                shortestPath(startsize, g, s);
                printf("\n");           
                free(s->items);
                free(s);
                s = createStack(g);
        }


        fclose(fp2);
	//}
        printf("\n");
        free(s->items);
        free(s);
        freeGraph(g);
        return EXIT_SUCCESS;
}
