#!/usr/bin/python3
def canUnlockAll(boxes):
    """
    Determines if all boxes can be unlocked
    Args:
        boxes: list of lists of integers
    Returns:
        True if all boxes can be unlocked, False otherwise
    """
    n = len(boxes)
    unlocked = [False] * n
    unlocked[0] = True
    keys = [0]

    while keys:
        current_key = keys.pop()
        for key in boxes[current_key]:
            if 0 <= key < n and not unlocked[key]:
                unlocked[key] = True
                keys.append(key)

    return all(unlocked)
