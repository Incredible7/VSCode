import string
import math
import random


def demo(x, n):
    if n not in x:
        print(n, 'is not an element of ', x)
        return
    i = x.index(n)
    x[0], x[i] = x[i], x[0]
    key = x[0]
    i = 0
    j = len(x) - 1
    while i < j:
        while i < j and x[j] >= key:
            j -= 1
        x[i] = x[j]
        while i < j and x[i] <= key:
            i += 1
        x[j] = x[i]
        x[i] = key
    x = list(range(1, 10))
    random.shuffle(x)
    print(x)
    demo(x, 4)
    print(x)


demo([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 4)
