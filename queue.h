typedef int T;

typedef struct node {
	T data;
	struct node *next;
}Node;

typedef struct queue {
	Node *head, *tail;
	int size;
}*Queue;

Queue initQueue(T data);
Node *initNode(T data);
Queue enqueue(Queue queue, T data);
Queue dequeue(Queue queue);
T first(Queue queue);
int isEmptyQueue(Queue queue);
Node *freeNode(Node *node);
Queue freeQueue(Queue queue);

