#include <stdlib.h>
#include "lists.h"

/**
 * insert_node - Adds a number into an already sorted singly linked list
 * @head: Double pointer referencing the start of the list
 * @number: The value to insert into the list
 *
 * Return: Pointer to the newly created node, or NULL on failure
 */
listint_t *insert_node(listint_t **head, int number)
{
    listint_t *new_node, *current;

    if (head == NULL)
        return (NULL);

    new_node = malloc(sizeof(listint_t));
    if (new_node == NULL)
        return (NULL);

    new_node->n = number;

    /* Handle case where the list is empty or the new node is the smallest value */
    if (*head == NULL || (*head)->n >= number)
    {
        new_node->next = *head;
        *head = new_node;
        return (new_node);
    }

    /* Move through the list to locate the correct insertion point */
    current = *head;
    while (current->next != NULL && current->next->n < number)
        current = current->next;

    /* Place the new node at its correct position in the list */
    new_node->next = current->next;
    current->next = new_node;

    return (new_node);
}
