#ifndef LISTS_H
#define LISTS_H

#include <stddef.h>

/**
 * struct listint_s - Structure for a node in a singly linked list
 * @n: Integer stored in the node
 * @next: Pointer to the next node in the list
 *
 * Description: Node structure for a singly linked list,
 * used in Holberton project
 */
typedef struct listint_s
{
    int n;
    struct listint_s *next;
} listint_t;

/* Function to print all elements of a singly linked list */
size_t print_listint(const listint_t *h);

/* Function to add a new node at the end of a singly linked list */
listint_t *add_nodeint_end(listint_t **head, const int n);

/* Function to free the memory used by a singly linked list */
void free_listint(listint_t *head);

/* Function to insert a number into a sorted singly linked list */
listint_t *insert_node(listint_t **head, int number);

#endif /* LISTS_H */
