#include "queue.h"

int main(void)
{
    queue qu = {};
    queue_ctor(&qu);

    double num = 1.5;

    for (int i = 0; i < 6; i++)
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
