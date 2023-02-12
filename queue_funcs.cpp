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
        printf("Data calloc error\n");
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

    qu->info.file = NULL;
    qu->info.func = NULL;
    qu->info.name = NULL;
    qu->info.line = 0;

    return 0;
}

int queue_push(queue * qu, elem value)
{
    assert(qu != NULL);

    if (((qu->tail + 1) & (QUEUE_SIZE - 1)) == qu->head)
    {
        printf("Can not push. Data is full, head - %lu, tail - %lu\n", qu->head, qu->tail);
        return 1;
    }

    qu->data[qu->tail] = value;
    qu->tail = (qu->tail + 1) & (QUEUE_SIZE - 1);

    return 0;
}

int queue_pop(queue * qu, elem * num)
{
    assert(qu != NULL);
    assert(num != NULL);

    if (qu->head != qu->tail)
    {
        *num = qu->data[qu->head];
        qu->data[qu->head] = 0.0;
        qu->head = (qu->head + 1) & (QUEUE_SIZE - 1);

        return 0;
    }
    printf("Can not pop empty queue\n");
    return 1;
}

void queue_print(queue * qu)
{
    assert(qu != NULL);

    for (size_t i = 1; i <= QUEUE_SIZE; i++)
    {
        printf("%lg ", qu->data[i - 1]);

        if (i % 8 == 0)
        {
            printf("\n");
        }
    }
}



