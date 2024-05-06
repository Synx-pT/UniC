"""
Bucketsort implementation using linked lists

Copyright 2020, University of Freiburg.

Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
Edited by us.
"""

import random
import time
from Queue import Queue  # noqa

from ListElement import ListElement  # noqa


def bucket_sort(array, k, key=lambda x: x):
    '''
    Implements the bucket sort algorithm to sort
        data elements using a key function to
        assign sorting keys to data elements

    Args:
        array: array of data elements
        k: largest key
        key: a function mapping data elements to values
        in range(k+1) (idendity function as default)

    >>> array = [10-i for i in range(10)]
    >>> bucket_sort(array, 10)
    >>> str(array)
    '[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]'
    '''
    # make list B of Queues for each key
    B: list[Queue] = [Queue() for key in range(k + 1)]

    # add data from array to B
    for n in array:
        B[key(n)].enqueue(ListElement(n))

    # deque data from B back to array
    i = 0
    for q in B:
        while not q.is_empty():
            array[i] = q.dequeue().get_key()  # type: ignore
            i += 1


def bucket_sort_performance():
    '''
    Method that outputs key range and elapsed time for sorting.
    '''
    for k in range(2 * 10**4, (12 * (10**5)) + 1, 2 * 10**4):
        array = [random.randint(0, k) for i in range(10**4)]
        start_time = time.time()
        bucket_sort(array, k)
        run_time = (time.time() - start_time) * 1000
        print("%d\t%.1f" % (k, run_time))


def is_sorted(lst, key=lambda x: x):
    """
        Method that checks whether or not a list is sorted

        Args:
            lst: the list that will be checked
        Returns:
        bool:    True if the list is sorted, false otherwise.
        """
    return all(key(lst[i]) <= key(lst[i + 1]) for i in range(len(lst) - 1))


if __name__ == "__main__":
    # testcases
    a = []
    bucket_sort(a, 10)
    assert a == []
    bucket_sort_performance()
