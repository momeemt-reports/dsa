#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdbool.h>

#include "primitive_to_string.h"
#include "queue.h"

void queue_test_1(void);
void queue_test_2(void);
void queue_test_3(void);
void queue_test_4(void);
void queue_test_5(void);
void queue_test_6(void);
void queue_test_7(void);

int main(void) {
    CU_initialize_registry();

    CU_pSuite queue_suite = CU_add_suite("Queue Test", NULL, NULL);
    if (queue_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(queue_suite, "Queue_Test_1", queue_test_1);
    CU_add_test(queue_suite, "Queue_Test_2", queue_test_2);
    CU_add_test(queue_suite, "Queue_Test_3", queue_test_3);
    CU_add_test(queue_suite, "Queue_Test_4", queue_test_4);
    CU_add_test(queue_suite, "Queue_Test_5", queue_test_5);
    CU_add_test(queue_suite, "Queue_Test_6", queue_test_6);
    CU_add_test(queue_suite, "Queue_Test_7", queue_test_7);

    CU_basic_run_tests();
    int ret = CU_get_number_of_failures();
    CU_cleanup_registry();
    return ret;
}

// Test case that stores and retrieves a single integer
void queue_test_1(void) {
    Queue *test_q = create_queue(10, sizeof(int));
    int val;

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 1, &val)));

    char buffer[1024] = "";
    queue_to_string(test_q, buffer, int_to_string);
    CU_ASSERT_STRING_EQUAL("[1]", buffer);

    int res;
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));

    delete_queue(test_q);
}

// Test case that stores a sequence of integers and retrieves them in the order
// in which they are stored
void queue_test_2(void) {
    Queue *test_q = create_queue(10, sizeof(int));
    int val;

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 1, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 2, &val)));

    char buffer[1024] = "";
    queue_to_string(test_q, buffer, int_to_string);
    CU_ASSERT_STRING_EQUAL("[1, 2]", buffer);

    int res;
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(1, res);
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(2, res);

    delete_queue(test_q);
}

// Test case using a ring buffer
void queue_test_3(void) {
    Queue *test_q = create_queue(3, sizeof(int));
    int val;
    int res;

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 1, &val)));
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(1, res);

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 2, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 3, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 4, &val)));

    char buffer[1024] = "";
    queue_to_string(test_q, buffer, int_to_string);
    CU_ASSERT_STRING_EQUAL("[2, 3, 4]", buffer);

    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(2, res);

    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(3, res);

    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(4, res);

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 5, &val)));
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(5, res);

    delete_queue(test_q);
}

// Test case without ring buffer that attempts to retrieve a value from an empty
// queue
void queue_test_4(void) {
    Queue *test_q = create_queue(3, sizeof(int));
    int val;
    int res;

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 1, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 2, &val)));

    char buffer[1024] = "";
    queue_to_string(test_q, buffer, int_to_string);
    CU_ASSERT_STRING_EQUAL("[1, 2]", buffer);

    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(1, res);

    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(2, res);

    CU_ASSERT_EQUAL(false, dequeue(test_q, &res));

    delete_queue(test_q);
}

// Test case with a ring buffer that attempts to retrieve a value from an empty
// queue
void queue_test_5(void) {
    Queue *test_q = create_queue(3, sizeof(int));
    int val;
    int res;

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 1, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 2, &val)));
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(1, res);
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(2, res);

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 3, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 4, &val)));

    char buffer[1024] = "";
    queue_to_string(test_q, buffer, int_to_string);
    CU_ASSERT_STRING_EQUAL("[3, 4]", buffer);

    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(3, res);
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(4, res);

    CU_ASSERT_EQUAL(false, dequeue(test_q, &res));

    delete_queue(test_q);
}

// Test case without a ring buffer to store more values when the queue is full
void queue_test_6(void) {
    Queue *test_q = create_queue(3, sizeof(int));
    int val;

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 1, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 2, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 3, &val)));
    CU_ASSERT_EQUAL(false, enqueue(test_q, (val = 4, &val)));

    char buffer[1024] = "";
    queue_to_string(test_q, buffer, int_to_string);
    CU_ASSERT_STRING_EQUAL("[1, 2, 3]", buffer);

    delete_queue(test_q);
}

// Test case using a ring buffer to store more values when the queue is full
void queue_test_7(void) {
    Queue *test_q = create_queue(3, sizeof(int));
    int val;
    int res;

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 1, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 2, &val)));

    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(1, res);
    CU_ASSERT_EQUAL(true, dequeue(test_q, &res));
    CU_ASSERT_EQUAL(2, res);

    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 3, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 4, &val)));
    CU_ASSERT_EQUAL(true, enqueue(test_q, (val = 5, &val)));
    CU_ASSERT_EQUAL(false, enqueue(test_q, (val = 6, &val)));

    char buffer[1024] = "";
    queue_to_string(test_q, buffer, int_to_string);
    CU_ASSERT_STRING_EQUAL("[3, 4, 5]", buffer);

    delete_queue(test_q);
}
