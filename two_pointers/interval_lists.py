#!/usr/bin/python3

# Given A and B two interval lists, A has no overlap inside A and B has no
# overlap inside B. Write the function to merge two interval lists, output the
# result with no overlap. Ask for a very efficient solution
#
# A naive method can combine the two list, and sort and apply merge interval in
# the leetcode, but is not efficient enough.
#
#   For example,
#   A: [1,5], [10,14], [16,18]
#   B: [2,6], [8,10], [11,20]
#
#   output [1,6], [8, 20]


def merge(A, B):

    def append(C, interval):
        if not C:
            C.append(interval)
        elif C[-1][1] >= interval[0]:
            C[-1][0] = min(C[-1][0], interval[0])
            C[-1][1] = max(C[-1][1], interval[1])
        else:
            C.append(interval)

    a_idx = 0
    b_idx = 0
    C = []

    while a_idx < len(A) and b_idx < len(B):
        a = A[a_idx]
        b = B[b_idx]
        if a[0] <= b[0]:
            append(C,a)
            a_idx += 1
        elif b[0] < a[0]:
            append(C,b)
            b_idx += 1

    while a_idx < len(A):
        append(C, A[a_idx])
        a_idx += 1


    while b_idx < len(B):
        append(C, B[b_idx])
        b_idx += 1

    return C

def main():
    # A = [[1,5], [10, 14], [16,18] ]
    # B = [[2,6], [8,10], [11,20] ]

    A = [  [1,2], [3,4], [5,6] ]
    B = [  [1,3], [5, 100] ]
    C = merge(A,B)
    print(C)

main()
