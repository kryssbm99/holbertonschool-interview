#!/usr/bin/python3
"""
Module to calculate the minimum number of operations needed
to achieve `n` 'H' characters in a text file starting with one 'H'.

Allowed operations:
1. Copy All: Copies all characters.
2. Paste: Adds the copied content to the file.

Functions:
    minOperations(n): Returns the minimum number of operations.
"""

def minOperations(n):
    """
    Calculate the minimum operations to get n 'H' characters.

    Parameters:
        n (int): Target number of 'H' characters.

    Returns:
        int: Minimum operations or 0 if n is not achievable.
    """
    if n <= 1:
        return 0  # Not possible for n <= 1

    operations = 0
    divisor = 2  # Start dividing from 2

    while n > 1:
        while n % divisor == 0:  # Reduce n by its divisor
            operations += divisor
            n //= divisor
        divisor += 1  # Try the next divisor

    return operations
