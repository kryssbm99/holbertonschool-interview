#include "binary_trees.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * enqueue - Add a node to the queue
 * @queue: Queue array
 * @node: Node to add
 * @rear: Rear index of the queue
 */

void enqueue(heap_t **queue, heap_t *node, int *rear)
{
	queue[*rear] = node;
	(*rear)++;
}

/**
 * dequeue - Remove a node from the queue
 * @queue: Queue array
 * @front: Front index of the queue
 *
 * Return: Node removed from the queue
 */

heap_t *dequeue(heap_t **queue, int *front)
{
	(*front)++;
	return (queue[*front - 1]);
}

/**
 * heapify_up - Restore heap property
 * @node: Node to start from
 *
 * Return: Node's final position
 */

heap_t *heapify_up(heap_t *node)
{
	while (node->parent && node->n > node->parent->n)
	{
		int temp = node->n;

		node->n = node->parent->n;

		node->parent->n = temp;

		node = node->parent;
	}
	return (node);
}

/**
 * heap_insert - Insert a value into the heap
 * @root: Root of the heap
 * @value: Value to insert
 *
 * Return: Pointer to the new node, or NULL on failure
 */

heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *temp;
	heap_t *queue[1024];
	int front = 0, rear = 0;

	if (!root)
		return (NULL);

	if (!*root)
		return (*root = binary_tree_node(NULL, value));

	enqueue(queue, *root, &rear);

	while (front < rear)
	{
		temp = dequeue(queue, &front);

		if (!temp->left)
		{
			temp->left = binary_tree_node(temp, value);
			new_node = temp->left;
			break;
		}
		enqueue(queue, temp->left, &rear);

		if (!temp->right)
		{
			temp->right = binary_tree_node(temp, value);
			new_node = temp->right;
			break;
		}
		enqueue(queue, temp->right, &rear);
	}

	return (heapify_up(new_node));
}
