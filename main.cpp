#include "queue.h"

FILE * log_file = NULL;

int main(void)
{
    open_logs();

    queue_t qu = {};
    queue_ctor(&qu);

    double num = 1.5;

    for (int i = 0; i < 9; i++)
    {
        queue_push(&qu, num);
        num += 0.1;
    }

    queue_pop(&qu, &num);
    queue_pop(&qu, &num);
    queue_pop(&qu, &num);

    for (int i = 0; i < 5; i++)
    {
        queue_push(&qu, num);
        num += 0.1;
    }

    for (int i = 0; i < 7; i++)
    {
        queue_pop(&qu, &num);

    }
    queue_push(&qu, num);

    queue_dtor(&qu);

    fclose(log_file);
    return 0;
}
