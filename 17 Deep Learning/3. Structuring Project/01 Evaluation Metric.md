In Machine Learning and Deep Learning, we often use some metrics to evaluate a model, such as :

- **Accuracy** 
- **Precision** 
- **Recall** 
- **F1 Score** 
- **PR Curve** 

Before these concepts, we need to know about the **Confusion Matrix** . In confusion matrix, there are some concepts describe the result of the prediction :

- **TP (True Positive)** - the number of the model gives a true prediction for the positive objects
- **FP (False Positive)** - the number of the model gives a false prediction for the positive objects
- **TN (True Negative)** - the number of the model gives a true prediction for the negative objects
- **FN (False Negative)** - the number of the model gives a false prediction for the negative objects

# 01 Accuracy

**Accuracy** is the ratio of the predictions that are right. It is the simplest metric for evaluating a model. But if the positive and negative objects are not balanced, it could not evaluate the model well. Such as if there are 100 objects with 98 positives, the accuracy will be high, up to 98%, if the model predicts all the objects as positive.

$$A = \dfrac{Right\_Predictions}{All\_Objects} = \dfrac{TP + TN}{TP + TN + FP + FN}$$

# 02 Precision

**Precision** represents the **accuracy of positive predictions**. It calculates how often the model predicts correctly the positive values. It is **the number of true positive predictions** divided by the **total number of positive** predictions (true positives + false positives) :

$$P = \dfrac{Right\_Predictions\_in\_Positives}{All\_Predicted\_as\_Positive} = \dfrac{TP}{TP + FP}$$

# 03 Recall

**Recall (Sensitivity or True Positive Rate)** : Recall represents **how well a model can identify actual positive cases**. It is the number of **true positive predictions** divided by **the total number of actual positive instances** (true positives + false negatives). It measures the ability of the model to capture all positive instances.

$$R = \dfrac{Right\_Predictions\_in\_Positives}{All\_the\_Positive\_Objects} = \dfrac{TP}{TP + FN}$$

# 04 F1 Score

The F1 score is an important evaluation metric that is commonly used **in classification tasks** to evaluate the performance of a model. It **combines precision and recall into a single value**. 

The F1 score is calculated as the **harmonic mean of precision and recall**. A [harmonic mean](https://www.geeksforgeeks.org/harmonic-mean/) is a type of average calculated by summing the reciprocal of each value in a data set and then dividing the number of values in the dataset by that sum. The value of the F1 score **lies between 0 to 1 with 1 being a better** :

$$F1 = \dfrac{2}{\dfrac{1}{P} + \dfrac{1}{R}}$$
