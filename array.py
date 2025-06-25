import numpy as np

a = np.array([[1, 2, 3], [4, 5, 6]])
b = np.array([[10, 20, 30], [40, 50, 60]])

print(a)
print(b)

s1 = np.concatenate((a, b), axis = 1)
s2 = np.concatenate((a, b), axis = 0)

print(s1)
print(s2)
