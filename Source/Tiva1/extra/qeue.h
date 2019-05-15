#ifndef QEUE_H
#define QEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

typedef struct {
	int intArray[MAX];
	int front;
	int rear;
	int itemCount;
} Qeue;

Qeue initQeue(void);

int peek(Qeue *q);

bool isEmpty(Qeue *q);

bool isFull(Qeue *q);

int size(Qeue *q);

void insert(Qeue *q, int data);

int removeData(Qeue *q);

#endif
