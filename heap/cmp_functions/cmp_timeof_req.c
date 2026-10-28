#include "../../codexion.h"

// Returns 1 if first_req 'timeof' occurs sooner than second_req 'timeof'
int cmp_timeof_request(heap_request first_req, heap_request second_req)
{
    struct timespec *first_timeof;
    struct timespec *second_timeof;

    *first_timeof = first_req.timeof_request;
    *second_timeof = second_req.timeof_request;
    return (timespec_cmp(first_timeof, second_timeof));
}
