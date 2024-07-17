The computer is good at doing matrix computation by using the specific hardware.

# 01 For loops vs. Vectorization

Assume that there is a group of data and parameters :

```Python
x = np.array ([200, 17])
W = np.array ([[1, -3, 5],
			  [-2, 4, -6]])
b = np.array ([-1, 1, 2])
```

If we do the computation of the activation value by for loop, it should be : 

```Python
def dense (a_in, W, b, g) :
	a_out = np.array (W.shape[1])
	for j in range (W.shape[1])
		w = W[:, j]
		z = np.dot (w, x) + b[j]
		a[j] = g (z)
	return a
```

If we do the computation by vector : 

```Python
x = np.array ([[200, 17]])
W = np.array ([[1, -3, 5],
			  [-2, 4, -6]])
b = np.array ([[-1, 1, 2]])

def dense (a_in, W, b, g) :
	Z = np.matmul (a_in, W) + b
	a_out = g (Z)
	return a_out
```