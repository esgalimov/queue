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
        queue_dump(qu, queue_verify(qu));
        return 1;
    }
    queue_dump(qu, queue_verify(qu));

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

    fprintf(log_file, "Queue %p \"%s\" at %s at %s(%d): DESTRUCTED\n",
                qu, qu->info.name, qu->info.func, qu->info.file, qu->info.line);

    return 0;
}

int queue_push(queue * qu, elem value)
{
    assert(qu != NULL);

    queue_dump(qu, queue_verify(qu));

    if (((qu->tail + 1) & (QUEUE_SIZE - 1)) == qu->head)
    {
        fprintf(log_file, "Warning: Can not push. Data is full\n");
        queue_dump(qu, queue_verify(qu));

        return 1;
    }

    qu->data[qu->tail] = value;
    qu->tail = (qu->tail + 1) & (QUEUE_SIZE - 1);
    queue_dump(qu, queue_verify(qu));

    return 0;
}

int queue_pop(queue * qu, elem * num)
{
    assert(qu != NULL);
    assert(num != NULL);

    queue_dump(qu, queue_verify(qu));

    if (qu->head != qu->tail)
    {
        *num = qu->data[qu->head];
        qu->data[qu->head] = 0.0;
        qu->head = (qu->head + 1) & (QUEUE_SIZE - 1);

        queue_dump(qu, queue_verify(qu));

        return 0;
    }

    fprintf(log_file, "Warning: Can not pop empty queue\n");
    queue_dump(qu, queue_verify(qu));

    return 1;
}

void queue_print(queue * qu)
{
    assert(qu != NULL);

    queue_dump(qu, queue_verify(qu));

    for (size_t i = 1; i <= QUEUE_SIZE; i++)
    {
        printf("%lg ", qu->data[i - 1]);

        if (i % 8 == 0)
        {
            printf("\n");
        }
    }
}

int queue_verify(queue * qu)
{
    assert(qu != NULL);

    int error_number = 0;

    if (qu->data == NULL)
    {
        error_number += DATA_PTR_NULL;
    }
    if (qu->info.line <= 0)
    {
        error_number += LINE_ERROR;
    }
    if (qu->info.name == NULL)
    {
        error_number += VAR_NAME_ERROR;
    }
    if (qu->info.func == NULL)
    {
        error_number += FUNC_NAME_ERROR;
    }
    if (qu->info.file == NULL)
    {
        error_number += FILE_NAME_ERROR;
    }
    if (qu->head < 0 || qu->head >= QUEUE_SIZE)
    {
        error_number += HEAD_ERROR;
    }
    if (qu->tail < 0 || qu->tail >= QUEUE_SIZE)
    {
        error_number += TAIL_ERROR;
    }


    return error_number;
}

void error_number_translate(int error_number)
{
    int i = 0;

    while (i < ERRORS_COUNT)
    {
        switch (error_number & (1 << i))
        {
            case 0:
                break;
            case DATA_PTR_NULL:
                fprintf(log_file, "Data have NULL pointer\n");
                break;
            case LINE_ERROR:
                fprintf(log_file, "Line <= 0\n");
                break;
            case VAR_NAME_ERROR:
                fprintf(log_file, "Variable name have NULL pointer\n");
                break;
            case FUNC_NAME_ERROR:
                fprintf(log_file, "Function name have NULL pointer\n");
                break;
            case FILE_NAME_ERROR:
                fprintf(log_file, "File name have NULL pointer\n");
                break;
            case TAIL_ERROR:
                fprintf(log_file, "Bad tail value\n");
                break;
            case HEAD_ERROR:
                fprintf(log_file, "Bad head value\n");
                break;
            default:
                fprintf(log_file, "Unknown error\n");
                break;
        }
    }
}

void queue_dump_(queue * qu, int error_number, const char * func, const char * file, int line)
{
    fprintf(log_file, "%s at %s(%d):\n", func, file, line);
    if (!error_number)
    {
        fprintf(log_file, "Queue %p (OK) \"%s\" at %s at %s(%d):\n",
                qu, qu->info.name, qu->info.func, qu->info.file, qu->info.line);

        fprintf(log_file, "{\n    head = %lu\n    tail = %lu\n",
            qu->head, qu->tail);
        fprintf(log_file, "    data [%p]\n}\n", qu->data);
        fprintf(log_file, "\n");
    }
    else
    {
        fprintf(log_file, "Queue %p (ERROR) \"%s\" at %s at %s(%d):\n",
                qu, qu->info.name, qu->info.func, qu->info.file, qu->info.line);
        error_number_translate(error_number);

        fprintf(log_file, "{\n    head = %lu\n    tail = %lu\n",
            qu->head, qu->tail);
        fprintf(log_file, "    data [%p]", qu->data);
        fprintf(log_file, "\n}\n");

        fclose(log_file);
        abort();
    }
}
