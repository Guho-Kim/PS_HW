#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 100 // 큐의 최대 크기

// 큐 구조체 선언
typedef struct Queue {
    int front; // 큐의 맨 앞 위치
    int rear; // 큐의 맨 뒤 위치
    int size; // 현재 큐에 들어있는 데이터의 개수
    int data[MAX_QUEUE_SIZE]; // 큐의 데이터를 저장할 배열
} Queue;

// 큐 초기화 함수
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// 큐가 비어있는지 확인하는 함수
bool isEmpty(Queue *q) {
    return (q->size == 0);
}

// 큐가 가득 찼는지 확인하는 함수
bool isFull(Queue *q) {
    return (q->size == MAX_QUEUE_SIZE);
}

// 큐에 데이터를 추가하는 함수
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // rear 위치 변경
    q->data[q->rear] = value; // rear 위치에 데이터 저장
    q->size++; // 큐의 데이터 개수 증가
}

// 큐에서 데이터를 제거하고 반환하는 함수
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->data[q->front]; // front 위치의 데이터 저장
    q->front = (q->front + 1) % MAX_QUEUE_SIZE; // front 위치 변경
    q->size--; // 큐의 데이터 개수 감소
    return value;
}

// 큐에서 데이터를 확인하는 함수
int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->data[q->front];
}
