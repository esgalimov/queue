#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#define LOCATION __PRETTY_FUNCTION__, __FILE__, __LINE__
#define queue_ctor(qu) queue_ctor_((qu), var_info {#qu, LOCATION})

//! @struct var_info
//! @brief Information about queue to write to log
//!
//! @var name - name of queue
//! @var func - function where queue created
//! @var file - file where queue created
//! @var line - line where queue created

typedef struct
{
    const char * name;
    const char * func;
    const char * file;
    int          line;
} var_info;

//! @struct queue
//! @brief Main struct of queue
//!
//! @var data - ptr to queue's array
//! @var head - index of first elem of queue
//! @var tail - index after end element

typedef struct
{
    double * data;
    size_t   head;
    size_t   tail;
    var_info info;
} queue;

//! @brief Type of elements in queue data

typedef double elem;

//! @brief Size of queue, must be 2ˆn to use bit mask in indexing elements

const size_t QUEUE_SIZE = 8;

//! @brief Constructor for queue struct
//!
//! @param [out] qu - ptr to queue
//! @param [in] info - info about queue
//!
//! @return 0 - if created OK, 1 - else

int queue_ctor_(queue * qu, var_info info);

//! @brief Destructor for queue
//!
//! @param [in] qu - ptr to queue
//! @return 0 if OK

int queue_dtor(queue * qu);

//! @brief Queue push
//! Add element to index = tail
//!
//! @param [out] qu - ptr to queue
//! @param [in] value - number to push
//!
//! @return 0 - Ok, 1 - Can not push, queue is full

int queue_push(queue * qu, elem value);

//! @brief Queue pop
//! Remove element from index = head, write it to variable by ptr
//!
//! @param [out] qu - ptr to queue
//! @param [out] num - ptr to write poped elemnt
//!
//! @return 0 - Ok, 1 - Can not pop, queue is empty

int queue_pop(queue * qu, elem * num);

//! @brief Func to print queue's data
//!
//! @param [out] qu - ptr to queue

void queue_print(queue * qu);

#endif
