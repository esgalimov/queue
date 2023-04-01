#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


#define LOCATION __PRETTY_FUNCTION__, __FILE__, __LINE__
#define queue_ctor(qu) queue_ctor_((qu), var_info {#qu, LOCATION})

#define LOG_MODE

#ifdef LOG_MODE
    #define ASSERT(condition)                                                               \
        if (!(condition))                                                                   \
        {                                                                                   \
            fprintf(log_file, "\nError in \"%s\" in %d line in function %s in file %s\n",   \
                    #condition, __LINE__, __PRETTY_FUNCTION__, __FILE__);                   \
            abort();                                                                        \
        }
    #define queue_dump(qu) queue_dump_((qu), __PRETTY_FUNCTION__, __FILE__, __LINE__)
#else
    #define ASSERT(condition)
    #define queue_dump(list)
#endif


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
    int      status;
} queue_t;

//! @brief Type of elements in queue data

typedef double elem;

//! @brief Size of queue, must be 2ˆn to use bit mask in indexing elements

const size_t QUEUE_SIZE = 8;

//! @brief Error what can be with queue
//! consists of 2ˆn numbers to use bit mask

enum ERRORS
{
    DATA_PTR_NULL   = 1 << 0,
    LINE_ERROR      = 1 << 1,
    VAR_NAME_ERROR  = 1 << 2,
    FUNC_NAME_ERROR = 1 << 3,
    FILE_NAME_ERROR = 1 << 4,
    TAIL_ERROR      = 1 << 5,
    HEAD_ERROR      = 1 << 6,
};

//! @brief Count of Error in enum ERRORS

const int ERRORS_COUNT = 7;

//! @brief Log file

extern FILE * log_file;

//! @brief Constructor for queue struct
//!
//! @param [out] qu - ptr to queue
//! @param [in] info - info about queue
//!
//! @return 0 - if created OK, 1 - else

int queue_ctor_(queue_t * qu, var_info info);

//! @brief Destructor for queue
//!
//! @param [in] qu - ptr to queue
//! @return 0 if OK

int queue_dtor(queue_t * qu);

//! @brief Queue push
//! Add element to index = tail
//!
//! @param [out] qu - ptr to queue
//! @param [in] value - number to push
//!
//! @return 0 - Ok, 1 - Can not push, queue is full

int queue_push(queue_t * qu, elem value);

//! @brief Queue pop
//! Remove element from index = head, write it to variable by ptr
//!
//! @param [out] qu - ptr to queue
//! @param [out] num - ptr to write poped elemnt
//!
//! @return 0 - Ok, 1 - Can not pop, queue is empty

int queue_pop(queue_t * qu, elem * num);

//! @brief Func to print queue's data
//!
//! @param [in] qu - ptr to queue

void queue_print(queue_t * qu);

//! @brief Func to check queue
//! Summarize codes of mistakes to make number where each bit is concrete mistake
//!
//! @param [in] qu - ptr to queue
//!
//! @return error number

void queue_verify(queue_t * qu);

//! @brief Write to log errors with using error number
//!
//! @param [in] error_number - error number what return queue verify

void error_number_translate(queue_t * qu);

//! @brief Function to write to log info about queue
//!
//! @param [in] qu - ptr to queue
//! @param [in] error_number
//! @param [in] func - name of func
//! @param [in] file - name of file
//! @param [in] line - line where queue is

void queue_dump_(queue_t * qu, const char * func, const char * file, int line);

//! @brief Open log_file
int open_logs(void);

#endif
