# 01 Underfitting and Overfitting

Let's see three examples in regression : 

![](imgs/regression_example.png)

- Graph 1 shows a model that **under fit the data** , which has **high bias** 
- Graph 2 shows a model that fit the data well and meet the require of **generalization** 
- Graph 3 shows a model that **over fit the date** , which hs **high variance** 

Let's see three examples in classification : 

![](imgs/classification_example.png)


From the examples above, if we calculate the errors in training sets and validation sets, we will find that :

- A _**High Bias**_ **model** has a **high training error** $J_{train}$ and a **high validation error** $J_{cv}$
    
- A _**High Variance**_ **model** has a **low training error** $J_{train}$ while a **high validation error** $J_{cv}$
    
- A **good model** has a **low training error** and a **low validation error**

# 02 Bias

If we train the data by an increasing order function, it will commonly behave as **with the increase of the degree, the training error will decrese :**

![](imgs/train_error_varied_with_degree.png)

It is because if we use the high order function, the model will **do its best to go through all the input sample** .

# 03 Variance

While in variance, **the validation error will only have a minimum somewhere** . Because **only the best model can predict the new data well** .

![](imgs/val_error_varied.png)

# 04 The Model

A **high bias** model indicates that **it does bad on training sets as well as the validation sets** . A **high variance** model indicates that **it does good on training sets while does bad on validation sets,** and commonly, **the error of validation sets will much larger than the training sets** .

![](imgs/model_error.png)

But if you are unfortunately enough, you may meet the model **with both high bias and high variance** . This may take place **especially in neural network** . If the model **overfits some part of the training data** , the model will have **high variance** , while there maybe some part the model **underfits the training data as well as the validation data** , the model will have both high bias and high variance .

![](imgs/both_high_variance_bias.png)

In this case, the **training error will be high** and the **validation error will be much higher than training error** .

# 05 The Recipe For Development

```mermaid
graph
	Start(Start Development) --> Model[Select the Model]
	Model --> Train[Train the Model]
	Train --> Validate[Evaluate the Model]
	
	Validate --> Bias{High Bias ?\nTraining Data Problem}
	Bias --> |yes| Improving[Improve the Model]
	Improving --> IBias[for bias]
	IBias --> Network[Bigger Network ?\nDeeper Network ?]
	IBias --> TrainTime[Train Longer Time ?\nBigger Epoches ?]
	Improving --> Train
	
	Bias --> |no| Variance{High Variance ?\nTest Data Problem}
	Variance --> |yes| Improving
	Improving --> IVar[for variance]
	IVar --> Data[More Data ?]
	IVar --> Re[Regularization ?]

	Variance --> |no| End(End Development)
	
```
