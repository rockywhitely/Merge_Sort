"""
    based on recursive mergesort algorithm found in
    Sanjoy Dasgupta, Christos Papadimitriou, & Umesh Vazirani,
    Algorithms, (New York: McGraw_Hill Higher Education, 2008),
    section 2.3 "Mergesort", pages 50-51
"""

import random

def merge(X, Y):
    if X is None or len(X) < 1: return Y
    if Y is None or len(Y) < 1: return X
    if X[0] <= Y[0]:
        return X[:1] + merge(X[1:len(X)], Y)
    else:
        return Y[:1] + merge(X, Y[1:len(Y)])

def mergesort(B):
    l = len(B)
    if l > 1:
        return merge(mergesort(B[:l//2]), mergesort(B[l//2:]))
    else: return B

def main():
    A = [random.randint(1, 100) for _ in range(200)]
    print(f'Original array: {A}')
    C = mergesort(A)
    print(f'Sorted   array: {C}')
    last = -1
    for c in C:
        if c < last:
            print(f'{c} is out of order, {last} is greater')
            exit (1)
        last = c
    print('All element in sorted order')

if __name__ == '__main__':
    main()