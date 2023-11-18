#include "queue.h"

Queue *create_queue(int len, size_t item_size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->length = len;
    q->item_size = item_size;
    q->buffer = malloc(item_size * len);
    q->front = 0;
    q->rear = 0;
    q->full = false;
    return q;
}

bool enqueue(Queue *q, void *item) {
    if (q->full) {
        return false;
    }
    memcpy((char *)q->buffer + (q->rear * q->item_size), item, q->item_size);
    q->rear = (q->rear + 1) % q->length;

    if (q->rear == q->front) {
        q->full = true;
    }
    return true;
}

bool dequeue(Queue *q, void *item) {
    if (q->front == q->rear && !q->full) {
        return false;
    }
    memcpy(item, (char *)q->buffer + (q->front * q->item_size), q->item_size);
    q->front = (q->front + 1) % q->length;
    q->full = false;
    return true;
}

unsigned int size_queue(Queue *q) {
    int size = q->rear - q->front;
    if (size < 0) {
        size += q->length;
    }
    if (q->full) {
        size = q->length;
    }
    return size;
}

bool is_empty_queue(Queue *q) { return size_queue(q) == 0; }

void queue_to_string(Queue *q, char *buffer, ItemToStringFunc fn) {
    int i = q->front;
    if (i == q->rear && !q->full) {
        sprintf(buffer, "[]");
        return;
    }
    bool first_iteration = true;
    char item_str[256];
    do {
        fn((char *)q->buffer + +(i * q->item_size), item_str);
        if (first_iteration) {
            sprintf(buffer + strlen(buffer), "[%s", item_str);
            first_iteration = false;
        } else {
            sprintf(buffer + strlen(buffer), ", %s", item_str);
        }
        i = (i + 1) % q->length;
    } while (i != q->rear);
    strcat(buffer, "]");
}

void display_queue(Queue *q, ItemToStringFunc fn) {
    char buffer[1024] = "";
    queue_to_string(q, buffer, fn);
    printf("%s\n", buffer);
}

void delete_queue(Queue *q) {
    free(q->buffer);
    q->buffer = NULL;
    free(q);
    q = NULL;
}
