#!/usr/bin/python3
"""
Check if a list of integers is a valid UTF-8 encoding.
"""

def validUTF8(data):
    """
    Determines if a list of integers is a valid UTF-8 encoding.

    Args:
        data (list): List of integers.

    Returns:
        bool: True if valid, False otherwise.
    """

    # Bit masks to check byte patterns
    MASK1 = 1 << 7  # 10000000
    MASK2 = 1 << 6  # 01000000

    # Tracks remaining bytes in a multi-byte sequence
    remaining = 0

    for num in data:
        # Only consider the last 8 bits
        num &= 0xFF

        if remaining == 0:
            # Determine byte count for UTF-8 character
            if not (num & MASK1):  # 1-byte (0xxxxxxx)
                continue
            elif (num & (MASK1 >> 1)) == 0:  # Invalid case
                return False
            elif (num & (MASK1 >> 2)) == 0:  # 2-byte (110xxxxx)
                remaining = 1
            elif (num & (MASK1 >> 3)) == 0:  # 3-byte (1110xxxx)
                remaining = 2
            elif (num & (MASK1 >> 4)) == 0:  # 4-byte (11110xxx)
                remaining = 3
            else:  # Invalid start byte
                return False
        else:
            # Check if it's a valid continuation byte (10xxxxxx)
            if not ((num & MASK1) and not (num & MASK2)):
                return False
            remaining -= 1

    return remaining == 0

# Test cases
if __name__ == "__main__":
    data1 = [65]
    print(validUTF8(data1))  # True

    data2 = [80, 121, 116, 104, 111, 110, 32,
             105, 115, 32, 99, 111, 111, 108, 33]
    print(validUTF8(data2))  # True

    data3 = [229, 65, 127, 256]
    print(validUTF8(data3))  # False
