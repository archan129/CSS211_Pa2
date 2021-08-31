
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node { 
        char name[20];
        struct Node* next;
        int index;
};


struct Graph {
        int size;
        struct Node* arr;
};

struct Queue {
        int items[1000];
        int front;
        int back;
};

struct Queue* allocateQueue();
int isEmpty(struct Queue* q);
void enqueue(struct Queue* q, int n);
int dequeue(struct Queue* q, struct Graph* g);
struct Node* allocateNode(char name[20], int index);
struct Graph* allocateGraph(int size);
void addNewEdge(struct Graph* g, char str[20], char nNode[20]);
void bfs(struct Graph* g, int iVertex);
void freeGraph(struct Graph* g);


struct Queue* allocateQueue() {
        struct Queue* q = malloc(sizeof(struct Queue));
        q->front = -1;
        q->back = -1;
        return q;
}



int isEmpty(struct Queue* q) {
        if (q->back == -1){
                return 1;
        } else {
                return 0;
        }
}

void enqueue(struct Queue* q, int n) {
        if (q->back == 1000 - 1){
                printf("\nQueue is full.");
        } else {
                if (q->front == -1){
                        q->front = 0;
                }
                q->back = q->back + 1;
                q->items[q->back] = n;
        }
}

int dequeue(struct Queue* q, struct Graph* g) {
        int item;
        if (isEmpty(q)) {
                item = -1;
        } else {
                item = q->items[q->front];
                q->front++;
                if (q->front > q->back) {
                        q->front = q->back = -1;
                }
        }

        printf("%s ", g[item].arr->name);
        return item;
}

struct Node* allocateNode(char name[20], int index) {
        struct Node* newNode = malloc(sizeof(struct Node));
        for(int i = 0; i < 20; i++){
                newNode -> name[i] = name[i];
        }
        newNode->next = 0;
        newNode->index = index;
        return newNode;
}

struct Graph* allocateGraph(int size) {
        struct Graph* g = malloc(size * sizeof(struct Graph));
        g->size = size;

        for (int i = 0; i < size; i++){
                g[i].arr = 0;
        }
        return g;
}

void addNewEdge(struct Graph* g, char str[20], char nNode[20]) {
        int index;
        for(int i = 0; i < g->size; i++){
                if(strcmp(g[i].arr->name, nNode) == 0){
                        index = i;
                        break;
                }
        }
        struct Node* newNode = allocateNode(nNode, index);
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

void bfs(struct Graph* g, int iVertex) {
        struct Queue* q = allocateQueue();
        int v[g->size];
	for(int i =0;i<g->size;i++){
		v[i] = 0;
	}
        int cVertex;
        enqueue(q, iVertex);
        v[iVertex] = 1;
        while (!isEmpty(q)) {
                cVertex = dequeue(q, g);
                struct Node* temp = g[cVertex].arr;
                while (temp != 0) {
                        int aVertex = temp->index;
                        if (v[aVertex] != 1) {
                                v[aVertex] = 1;
                                enqueue(q, aVertex);
                        }
                        temp = temp->next;
                }
        }

        printf("\n");
        free(q);
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
        if(argc < 3){
                printf("Insufficient Arguements\n");
                return EXIT_SUCCESS;
        }
        FILE* fp = fopen(argv[1], "r");
        int v;
        fscanf(fp,"%d \n", &v);
        struct Graph* g = allocateGraph(v);

        char list[20];
        char A[20];
        char B[20];

        for(int i = 0; i < v; i++){
                fscanf(fp,"%s \n", list);
                g[i].arr = allocateNode(list, i);

        }
        while(fscanf(fp,"%s %s\n", A, B) != EOF){
                addNewEdge(g, A, B);
                addNewEdge(g, B, A);
        }
        fclose(fp);
        FILE* fp2 = fopen(argv[2], "r");
        int sVertex;
        while(fscanf(fp2, "%s\n", list)!= EOF){
                for(int i = 0; i < g->size; i++){
                        if(strcmp(g[i].arr->name, list) == 0){
                                sVertex = g[i].arr->index;
                                break;
                        }
                }
                bfs(g, sVertex);
        }
        fclose(fp2);
        freeGraph(g);
        return EXIT_SUCCESS;
}
