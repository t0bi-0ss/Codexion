#include "../../codexion.h"

// Returns 1 if first_req coder's burnout is sooner than second_req coder's burnout
int cmp_burnout(heap_request first_req, heap_request second_req)
{
    struct timespec *first_brnout;
    struct timespec *second_brnout;

    first_brnout = &first_req.coder->to_burnout;
    second_brnout = &second_req.coder->to_burnout;
    return (timespec_cmp(first_brnout, second_brnout));
}
