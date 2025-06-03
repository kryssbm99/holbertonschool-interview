#include "binary_trees.h"
#include <stdlib.h>

/**
 * create_avl_node - Creates a new AVL node.
 * @parent: Pointer to the parent node.
 * @value: Value to store in the node.
 *
 * Return: Pointer to the new node, or NULL on failure.
 */
avl_t *create_avl_node(avl_t *parent, int value)
{
	avl_t *node = malloc(sizeof(avl_t));
if (!node)
	return (NULL);

node->n = value;
node->parent = parent;
node->left = NULL;
node->right = NULL;

return (node);
}

/**
 * sorted_array_to_avl_helper - Recursively builds an AVL tree.
 * @array: The sorted array.
 * @start: Start index of the subarray.
 * @end: End index of the subarray.
 * @parent: Pointer to the parent node.
 *
 * Return: Pointer to the root node of the subtree, or NULL on failure.
 */
avl_t *sorted_array_to_avl_helper(int *array,
int start, int end, avl_t *parent)
{
	if (start > end)
		return (NULL);

	int mid = start + (end - start) / 2;
	avl_t *root = create_avl_node(parent, array[mid]);
if (!root)
	return (NULL);

root->left = sorted_array_to_avl_helper(array, start, mid - 1, root);
root->right = sorted_array_to_avl_helper(array, mid + 1, end, root);

return (root);
}

/**
 * sorted_array_to_avl - Builds an AVL tree from a sorted array.
 * @array: Pointer to the first element of the sorted array.
 * @size: Number of elements in the array.
 *
 * Return: Pointer to the root node of
 * the created AVL tree, or NULL on failure.
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (!array || size == 0)
		return (NULL);

	return (sorted_array_to_avl_helper(array, 0, size - 1, NULL));
}
