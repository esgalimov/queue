#include "queue.h"

int queue_ctor_(queue_t * qu, var_info info)
{
    ASSERT(qu);

    qu->data = (elem *) calloc(QUEUE_SIZE, sizeof(elem));
    qu->head = 0;
    qu->tail = 0;
    qu->info = info;

    if (qu->data == NULL)
    {
        queue_dump(qu);
        return 1;
    }
    queue_dump(qu);

    return 0;
}

int queue_dtor(queue_t * qu)
{
    ASSERT(qu);

    free(qu->data);
    qu->head = 0;
    qu->tail = 0;

    qu->info.file = NULL;
    qu->info.func = NULL;
    qu->info.name = NULL;
    qu->info.line = 0;

    #ifdef LOG_MODE
        fprintf(log_file, "Queue %p \"%s\" at %s at %s(%d): DESTRUCTED\n",
                    qu, qu->info.name, qu->info.func, qu->info.file, qu->info.line);
    #endif

    return 0;
}

int queue_push(queue_t * qu, elem value)
{
    ASSERT(qu);

    if (qu->status)
    {
        queue_dump(qu);
        return 1;
    }

    if (((qu->tail + 1) & (QUEUE_SIZE - 1)) == qu->head)
    {
        fprintf(log_file, "Warning: Can not push. Data is full\n");
        queue_dump(qu);

        return 1;
    }

    qu->data[qu->tail] = value;
    qu->tail = (qu->tail + 1) & (QUEUE_SIZE - 1);
    queue_dump(qu);

    return 0;
}

int queue_pop(queue_t * qu, elem * num)
{
    ASSERT(qu);
    ASSERT(num);

    if (qu->status)
    {
        queue_dump(qu);
        return 1;
    }

    if (qu->head != qu->tail)
    {
        *num = qu->data[qu->head];
        qu->data[qu->head] = 0.0;
        qu->head = (qu->head + 1) & (QUEUE_SIZE - 1);

        queue_dump(qu);

        return 0;
    }

    fprintf(log_file, "Warning: Can not pop empty queue\n");
    queue_dump(qu);

    return 1;
}

void queue_print(queue_t * qu)
{
    ASSERT(qu);

    for (size_t i = 0; i < QUEUE_SIZE; i++)
    {
        fprintf(log_file, "%5lu", i);
    }
    fprintf(log_file, "\n");
    for (size_t i = 0; i < QUEUE_SIZE; i++)
    {
        fprintf(log_file, "%5lg", qu->data[i]);
    }
    fprintf(log_file, "\n");
}

void queue_verify(queue_t * qu)
{
    ASSERT(qu);

    if (qu->data == NULL)
    {
        qu->status |= DATA_PTR_NULL;
    }
    if (qu->info.line <= 0)
    {
        qu->status |= LINE_ERROR;
    }
    if (qu->info.name == NULL)
    {
        qu->status |= VAR_NAME_ERROR;
    }
    if (qu->info.func == NULL)
    {
        qu->status |= FUNC_NAME_ERROR;
    }
    if (qu->info.file == NULL)
    {
        qu->status |= FILE_NAME_ERROR;
    }
    if (qu->head < 0 || qu->head >= QUEUE_SIZE)
    {
        qu->status |= HEAD_ERROR;
    }
    if (qu->tail < 0 || qu->tail >= QUEUE_SIZE)
    {
        qu->status |= TAIL_ERROR;
    }
}

void error_number_translate(queue_t * qu)
{
    int i = 0;

    while (i < ERRORS_COUNT)
    {
        switch (qu->status & (1 << i))
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
        i++;
    }
}

void queue_dump_(queue_t * qu, const char * func, const char * file, int line)
{
    ASSERT(qu);

    fprintf(log_file, "%s at %s(%d):\n", func, file, line);
    queue_verify(qu);

    if (!qu->status)
    {
        fprintf(log_file, "Queue %p (OK) \"%s\" at %s at %s(%d):\n",
                qu, qu->info.name, qu->info.func, qu->info.file, qu->info.line);

        fprintf(log_file, "{\n    head = %lu\n    tail = %lu\n",
            qu->head, qu->tail);
        fprintf(log_file, "    data [%p]\n", qu->data);
        queue_print(qu);
        fprintf(log_file, "}\n\n");

    }
    else
    {
        fprintf(log_file, "Queue %p (ERROR) \"%s\" at %s at %s(%d):\n",
                qu, qu->info.name, qu->info.func, qu->info.file, qu->info.line);
        error_number_translate(qu);

        fprintf(log_file, "{\n    head = %lu\n    tail = %lu\n",
            qu->head, qu->tail);
        fprintf(log_file, "    data [%p]\n", qu->data);
        queue_print(qu);
        fprintf(log_file, "}\n\n");
    }
}

int open_logs(void)
{
    log_file = fopen("log.txt", "w");
    if (log_file == NULL)
    {
        printf("Can't open log file!");
        return 1;
    }
    return 0;
}
