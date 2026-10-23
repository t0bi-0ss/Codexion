#include "../../codexion.h"

void    swap_nodes(heap_node *first_node, heap_node *second_node)
{
    heap_node   *node_1;
    heap_node   *node_4;

    node_1 = first_node->previous;
    node_4 = second_node->next;
    node_1->next = second_node;
    second_node->previous = node_1;
    second_node->next = first_node;
    first_node->previous = second_node;
    first_node->next = node_4;
    node_4->previous = first_node;
}
