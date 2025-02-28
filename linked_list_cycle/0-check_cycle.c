#include "lists.h"

/**
 * check_cycle - Detects a cycle in a linked list
 * @list: Pointer to the head of the list
 * Return: 1 if a cycle is found, 0 otherwise
 */
int check_cycle(listint_t *list)
{
    listint_t *slow, *fast;

    if (list == NULL)
        return (0);

    slow = list;
    fast = list->next;

    while (fast && fast->next)
    {
        if (slow == fast)
            return (1); /* Cycle detected */

        slow = slow->next;
        fast = fast->next->next;
    }

    return (0); /* No cycle */
}