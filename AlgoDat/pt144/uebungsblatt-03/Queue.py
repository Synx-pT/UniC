"""
Implementation of DoublyLinkedList Data Structure

Copyright 2020, University of Freiburg.

Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
Edited by us.
"""


from ListElement import ListElement # noqa


class Queue:
    '''
    Implementation of a FIFO queue
    '''

    def __init__(self):
        '''
        Default constructor
        '''
        self._length = 0
        self._head = None
        self._tail = None

    def is_empty(self):
        '''
        Returns:
            True if queue is empty, else False

        >>> fifo = Queue()
        >>> fifo.is_empty()
        True
        >>> le = ListElement()
        >>> fifo.enqueue(le)
        >>> fifo.is_empty()
        False
        '''
        return self._length == 0

    def get_length(self):
        '''
        Returns:
            int : length of the queue

        >>> fifo = Queue()
        >>> fifo.get_length()
        0
        >>> for i in range(100): fifo.enqueue(ListElement(i))
        >>> fifo.get_length()
        100
        '''
        return self._length

    def enqueue(self, new_element):
        '''
        Insert a new object at the end of the queue
        Args:
            ListElement new_element - new element

        >>> fifo = Queue()
        >>> le = ListElement(0)
        >>> fifo.enqueue(le)
        >>> str(fifo)
        '<[0]>'
        >>> for i in range(10): fifo.enqueue(ListElement(i + 1))
        >>> str(fifo)
        '<[0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10]>'
        '''

        # if queue is empty insert element as head and tail
        if self.is_empty():
            self._head = self._tail = new_element
            new_element.set_next(None)

        # if queue is not empty then set tail pointer
        else:
            self._tail.set_next(new_element)
            self._tail = new_element

        # ensure new tail's next pointer doesn't go somwhere
        new_element.set_next(None)

        self._length += 1

    def dequeue(self):
        '''
        Removes and returns the head of queue
        Returns:
            first element of the queue,
            or None, if queue is empty

        >>> fifo = Queue()
        >>> le = ListElement(0)
        >>> fifo.enqueue(le)
        >>> str(fifo.dequeue())
        '[0]'
        >>> fifo.is_empty()
        True
        >>> str(fifo.dequeue())
        'None'

        >>> for i in range(10): fifo.enqueue(ListElement(i))
        >>> ' '.join([str(fifo.dequeue()) for i in range(10)])
        '[0] [1] [2] [3] [4] [5] [6] [7] [8] [9]'
        '''

        # not much to do if queue is empty
        if self.is_empty():
            return None

        head = self._head

        # if last element is popped delete head and tail pointers
        if self.get_length == 1:
            self._head = self._tail = None
        # else second element becomes new head
        else:
            self._head = head.get_next()

        self._length -= 1
        return head

    def get_first(self):
        '''
        Returns:
            first element of the queue,
            or None, if queue is empty

        >>> l1 = ListElement(42)
        >>> l2 = ListElement(21)
        >>> fifo = Queue()
        >>> fifo.get_first() is None
        True
        >>> fifo.enqueue(l1)
        >>> fifo.get_first() == l1
        True
        >>> fifo.enqueue(l2)
        >>> fifo.get_first() == l1
        True
        '''
        return self._head

    def get_last(self):
        '''
        Returns:
            last element of the queue,
            or None, if queue is empty

        >>> l1 = ListElement(42)
        >>> l2 = ListElement(21)
        >>> fifo = Queue()
        >>> fifo.get_last() is None
        True
        >>> fifo.enqueue(l1)
        >>> fifo.get_last() == l1
        True
        >>> fifo.enqueue(l2)
        >>> fifo.get_last() == l2
        True
        '''
        return self._tail

    def __str__(self):
        '''
        Returns:
              string representation of the queue

        >>> fifo = Queue()
        >>> str(fifo)
        '<>'
        >>> for i in range(10): fifo.enqueue(ListElement(i))
        >>> str(fifo)
        '<[0] [1] [2] [3] [4] [5] [6] [7] [8] [9]>'
        '''
        ret_string = ''
        current = self._head
        if not self.is_empty():
            for i in range(self._length - 1):
                ret_string += str(current) + ' '
                current = current.get_next()
            ret_string += str(current)

        return '<' + ret_string + '>'