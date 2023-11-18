/**
 * @file queue.h
 * @brief implements a generics queue
 * @author Mutsuha Asada
 * @date 2023/11/18
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Queue
 * @brief The generic queue structure.
 *
 * This structure represents a generic queue. It is capable of storing data
 * of any type in a FIFO (first-in, first-out) manner.
 */
typedef struct {
    void *buffer; /**< Buffer to store generic data. */
    int length;   /**< The maximum number of items that the queue can store. */
    size_t item_size; /**< Size of each item in the queue. */
    int front;        /**< Index of the front item in the queue. */
    int rear;         /**< Index of the rear item in the queue. */
    bool full;        /**< Flag to indicate if the queue is full. */
} Queue;

/**
 * @typedef ItemToStringFunc
 */
typedef void (*ItemToStringFunc)(void *item, char *str);

/**
 * @brief create queue
 *
 * This function creates a new queue with the specified length and item size.
 *
 * @param len The length of the queue.
 * @param item_size The size of each item in the queue.
 * @return A pointer to the newly created queue.
 * @sa delete_queue
 */
Queue *create_queue(int len, size_t item_size);

bool enqueue(Queue *q, void *item);
bool dequeue(Queue *q, void *item);
unsigned int size_queue(Queue *q);
bool is_empty_queue(Queue *q);
void queue_to_string(Queue *q, char *buffer, ItemToStringFunc fn);
void display_queue(Queue *q, ItemToStringFunc fn);
void delete_queue(Queue *q);

#endif
