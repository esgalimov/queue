#include "queue.h"

int queue_ctor_(queue * qu, var_info info)
{
    assert(qu != NULL);

    qu->data = (elem *) calloc(QUEUE_SIZE, sizeof(elem));
    qu->head = 0;
    qu->tail = 0;
    qu->info = info;

    if (qu->data == NULL)
    {
        printf("Data calloc error");
        return 1;
    }
    return 0;
}

int queue_dtor(queue * qu)
{
    assert(qu != NULL);

    free(qu->data);
    qu->head = 0;
    qu->tail = 0;

    return 0;
}
