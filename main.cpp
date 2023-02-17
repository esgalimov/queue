#include "queue.h"

FILE * log_file = NULL;

int main(void)
{
    log_file = fopen("log.txt", "w");
    if (log_file == NULL)
    {
        printf("Can't open log file!");
        return 1;
    }

    queue qu = {};
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



    queue_print(&qu);

    queue_dtor(&qu);
    return 0;
}
