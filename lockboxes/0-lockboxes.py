#!/usr/bin/python3
"""
The program checks if all boxes can be unlocked
and returns True if they can, False otherwise
"""


def canUnlockAll(boxes):
    """
    Determines if all boxes can be unlocked
    Args:
        boxes: list of lists of integers
    Returns:
        True if all boxes can be unlocked, False otherwise
    """
    n = len(boxes)
    unlocked = [False] * n  # list of booleans to track if a box is unlocked
    unlocked[0] = True  # first box is unlocked
    keys = [0]  # list of keys to unlock boxes

    while keys:
        current_key = keys.pop()  # get the current key
        for key in boxes[current_key]:
            if 0 <= key < n and not unlocked[key]:
                unlocked[key] = True
                keys.append(key)  # add key to list of keys to unlock boxes

    return all(unlocked)  # check if all boxes are unlocked
