# 01 Why don't initialize to Zero ?

If we initialize the parameters $W, b$ all to be zero, then, we will find that every unit **does the same calculations in the forward propagation and backward propagation** because all the inputs and parameters are the same. This will lead to a situation : no matter how many hidden units the neural network has, it will only **work like a multiple linear regression** .

# 02 Random Initialization

To avoid the repetition of the hidden units, we often initialize $W$  to a random matrix and $b$ to be 0.

