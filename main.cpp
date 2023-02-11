#include "queue.h"

int main(void)
{
    queue qu = {};
    queue_ctor(&qu);
    queue_dtor(&qu);
    return 0;
}
