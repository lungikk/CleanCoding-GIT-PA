#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 10
int starting_vertex;
struct Graph {
    struct Node* head[N];
};

struct Node {
    int dest;
    struct Node* next;
};

struct Edge {
    int src, dest;
};

struct Queue {
    int items[N];
    int front;
    int rear;
};

struct Stack {
    int items[N];
    int top;
};

struct Graph* createGraph(struct Edge edges[], int n) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    for (int i = 0; i < N; i++) {
        graph->head[i] = NULL;
    }
    for (int i = 0; i < n; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->dest = dest;
        newNode->next = graph->head[src];
        graph->head[src] = newNode;

        // Adăugăm și o muchie inversă pentru a asigura un graf neorientat
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->dest = src;
        newNode->next = graph->head[dest];
        graph->head[dest] = newNode;
    }
    return graph;
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < N; i++) {
        struct Node* ptr = graph->head[i];
        while (ptr) {
            printf("(%d->%d)\t", i, ptr->dest);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

bool isQueueEmpty(struct Queue* queue) {
    return queue->rear == -1;
}

void enqueue(struct Queue* queue, int value) {
    if (queue->rear == N - 1)
        printf("\nQueue is Full!!");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

int dequeue(struct Queue* queue) {
    int item;
    if (isQueueEmpty(queue)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

void BFS(struct Graph* graph, int startNode) {
    struct Queue* queue = createQueue();
    bool visited[N] = {false};

    visited[startNode] = true;
    enqueue(queue, startNode);

    printf("BFS traversal: ");
    while (!isQueueEmpty(queue)) {
        int currentNode = dequeue(queue);
        printf("%d ", currentNode);

        struct Node* temp = graph->head[currentNode];
        while (temp) {
            int adjNode = temp->dest;
            if (!visited[adjNode]) {
                visited[adjNode] = true;
                enqueue(queue, adjNode);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

bool isStackEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int value) {
    stack->items[++stack->top] = value;
}

int pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty");
        return -1;
    } else {
        return stack->items[stack->top--];
    }
}

void DFSUtil(struct Graph* graph, int startNode, bool visited[]) {
    visited[startNode] = true;
    printf("%d ", startNode);

    struct Node* temp = graph->head[startNode];
    while (temp) {
        int adjNode = temp->dest;
        if (!visited[adjNode]) {
            DFSUtil(graph, adjNode, visited);
        }
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startNode){
    bool visited[N] = {false};
    struct Stack* stack = createStack();

    printf("DFS traversal: ");
    push(stack, startNode);

    while (!isStackEmpty(stack)) {
        int currentNode = pop(stack);
        if (!visited[currentNode]) {
            printf("%d ", currentNode);
            visited[currentNode] = true;

            struct Node* temp = graph->head[currentNode];
            while (temp) {
                int adjNode = temp->dest;
                if (!visited[adjNode]) {
                    push(stack, adjNode);
                }
                temp = temp->next;
            }
        }
    }
    printf("\n");
}

int main() {
    struct Edge edges[] = {
            {1,2},{1,3},{1,4},{2,5},
            {3,6},{3,7},{4,8},{6,9}
            // prin muchie catre 0 notez nod terminal
    };

    int numEdges = sizeof(edges) / sizeof(edges[0]);

    struct Graph* graph = createGraph(edges, numEdges);

    printf("de unde plecam in DFS?");
    scanf("%d", &(starting_vertex));
    DFS(graph, starting_vertex);


    printf("de unde plecam in BFS?");
    scanf("%d", &(starting_vertex));
    BFS(graph, starting_vertex);

    return 0;
}
