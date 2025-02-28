#include <stdio.h>
#include "palindrome.h"

/**
 * is_palindrome - Checks if a number is a palindrome
 * @n: Number to check
 *
 * Return: 1 if palindrome, 0 otherwise
 */
int is_palindrome(unsigned long n)
{
    unsigned long original = n, reversed = 0;

    while (n)
    {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }

    return (original == reversed);
}