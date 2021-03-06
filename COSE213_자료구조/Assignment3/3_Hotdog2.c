//Filename : 2_Hotdog1
//Filename : Queue.c
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
	void* item;
	struct QueueNode* next;
} QueueNode;

typedef struct QueueHeader {
	QueueNode* front;
	QueueNode* rear;
	int count;
} QueueHeader;

QueueHeader* CreateQueue(void)
{
	QueueHeader* pHeader = (QueueHeader*)malloc(sizeof(QueueHeader));
	
	//If malloc didn't work
	if(pHeader == NULL) {
		printf("There's not enough memeory.\n");
		return NULL;
	}
	
	pHeader->front = pHeader->rear = NULL;
	pHeader->count = 0;
	return pHeader;
}

void Enqueue(void* data, QueueHeader* pHeader)
{
	//If there's no queue
	if(pHeader == NULL) {
		printf("There's no queue.\n");
		return;
	}
	
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	
	//If malloc didn't work
	if(newNode == NULL) {
		printf("There's not enough memeory,\n");
		return;
	}
	
	newNode->item = data;
	newNode->next = NULL;
	
	//If queue is empty
	if(pHeader->count == 0) {
		pHeader->front = pHeader->rear = newNode;
		pHeader->count++;
	}
	else {
		pHeader->rear->next = newNode;
		pHeader->rear = newNode;
		pHeader->count++;
	}
}

void* Dequeue(QueueHeader* pHeader)
{
	QueueNode* tempNode = NULL;
	void* item = NULL;
	
	//If there's no queue
	if(pHeader == NULL) {
		printf("There's no queue.\n");
		return NULL;
	}
	
	//If queue is empty
	if(pHeader->count == 0) {
		printf("Queue is empty.\n");
		return NULL;
	}
	
	else {
		tempNode = pHeader->front;
		pHeader->front = pHeader->front->next;
		item = tempNode->item;
		free(tempNode);
		pHeader->count--;
		return item;
	}
}

void* QueueFront(QueueHeader* pHeader)
{
	void* item = NULL;
	item = pHeader->front->item;
	return item;
}

void DestroyQueue(QueueHeader* pHeader)
{
	QueueNode* currentNode = NULL;
	QueueNode* t = NULL;
	t = currentNode = pHeader->front;
	
	while(currentNode != pHeader->rear) {
		currentNode = currentNode->next;
		free(t);
		t = currentNode;
	}
	
	free(currentNode);
	free(pHeader);
}

int queueCount(QueueHeader* pHeader)
{
	return pHeader->count;
}

void ShowQueue(QueueHeader* pHeader)
{
	printf("Queue status : ");
	QueueNode* currentNode = pHeader->front;
	while(currentNode != pHeader->rear) {
		printf("%d <- ", *(int*)currentNode->item);
		currentNode = currentNode->next;
	}
	printf("%d\n", *(int*)currentNode->item);
}


int main(void)
{
	int customers = 0;
	printf("number of customer : ");
	scanf(" %d", &customers);
	
	QueueHeader* q = CreateQueue();
	int i = 0, patience = 0;
	
	while(i < customers) {
		int* pp = (int*)malloc(sizeof(int));
		printf("Patience of customer : ");
		scanf(" %d", &patience);
		*pp = patience;
		Enqueue(pp, q);
		i++;
	}
	
	int time = 0, sell = 0;
	while(1) {
		if(q->count == 0) break;
		patience = *(int*)Dequeue(q);
		if(patience >= time) {
			sell++;
			if(sell % 2 == 0) time++;
		}
		else{
			continue;
		}
	}
	printf("I sell %d hotdogs.", sell);
	return 0;
}
