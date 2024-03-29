As you already know, **object-oriented programming (OOP)** is a programming paradigm that is based on the concept of objects. Objects interact with each other and that is how the program functions. Objects have states and behaviors. Many objects can have similar characteristics and if you need to work with them in your program it may be easier to create a **class** for similar objects. Classes represent the common structure of similar objects: their data and their behavior.

# 01 Declaring classes

Classes are declared with the keyword `class` and the name of the class:

```python
# class syntax
class MyClass:
    var = ...  # some variable

    def do_smt(self):
    # some method
```

Generally, a class name starts with a capital letter and it is usually a noun or a noun phrase. The names of the classes follow the **CapWords** convention: meaning that if it's a phrase, all words in the phrase are capitalized and written without underscores between them.

```python
# good class name
class MyClass:
    ...

# not so good class name:
class My_class:
    ...
```

Classes allow you to define the data and the behaviors of similar objects. The behavior is described by **methods.** A method is similar to a function in that it is a block of code that has a name and performs a certain action. Methods, however, are not independent since they are defined within a class. Data within classes are stored in the **attributes** (variables) and there are two kinds of them: **class attributes** and **instance attributes**. The difference between those two will be explained below.

# 02 Class attribute

A class attribute is an attribute shared by all instances of the class. Let's consider the class **Book** as an example:

```python
# Book class
class Book:
    material = "paper"
    cover = "paperback"
    all_books = []
```

This class has a string variable `material` with the value "paper", a string variable `cover` with the value "paperback" and an empty list as an attribute `all_books`. All those variables are class attributes and they can be accessed using the **dot notation** with the name of the class:

```python
Book.material  # "paper"
Book.cover  # "paperback"
Book.all_books  # []
```

**Class attributes** are defined **within the class but outside of any methods**. Their value is the same for all instances of that class so you could consider them as the sort of "default" values for all objects.

As for the **instance variables**, they store the data unique to each object of the class. They are defined **within the class methods**, notably, within the `__init__` method. In this topic, we'll deal with the class attributes, but don't worry – you'll have plenty of time to learn more about instance attributes.

# 03 Class instance

Now, let's create an instance of a **Book** class. For that we would need to execute this code:

```python
# Book instance
my_book = Book()
```

Here we not only created an instance of a **Book** class but also assigned it to the variable **`my_book`**. The syntax of instantiating a class object resembles a function call : after the class name, we write parentheses.

Our `my_book` object has access to the contents of the class **Book** : its attributes and methods.

```python
print(my_book.material)  # "paper"
print(my_book.cover)  # "paperback"
print(my_book.all_books)  # []
```

A class instance is an object of the class. If, for example, there was a class **River,** we could create such instances as Volga, Seine, and Nile. They would all have the same structure and **share all class attributes** defined within the class River.

However, initially, all instances of the class would be identical to one another. Most of the time that is not what we want. To customize the initial state of an instance, the **`__init__`** method is used.

## 3.1 def \_\_init\_\_ ()

The `__init__` method is a **constructor**. Constructors are a concept from the object-oriented programming. A class **can have one and only one constructor**. If `__init__` is defined within a class, **it is automatically invoked when we create a new class instance**. Take our class River as an example:

```python
class River:
    # list of all rivers
    all_rivers = []
    
    def __init__(self, name, length):
        self.name = name
        self.length = length
        # add current river to the list of all rivers
        River.all_rivers.append(self)

volga = River("Volga", 3530)
seine = River("Seine", 776)
nile = River("Nile", 6852)

# print all river names
for river in River.all_rivers:
    print(river.name)
# Output:
# Volga
# Seine
# Nile
```

We created three instances (or objects) of the class River: `volga`, `seine`, and `nile`. Since we defined **name** and **length** parameters for the `__init__`, they must be explicitly passed when creating new instances. So something like `volga = River()` would cause an error. Look at [this](https://pythontutor.com/visualize.html#code=class%20River%3A%0A%20%20%20%20%23%20list%20of%20all%20rivers%0A%20%20%20%20all_rivers%20%3D%20%5B%5D%0A%20%20%20%20%0A%20%20%20%20def%20__init__%28self,%20name,%20length%29%3A%0A%20%20%20%20%20%20%20%20self.name%20%3D%20name%0A%20%20%20%20%20%20%20%20self.length%20%3D%20length%0A%20%20%20%20%20%20%20%20%23%20add%20current%20river%20to%20the%20list%20of%20all%20rivers%0A%20%20%20%20%20%20%20%20River.all_rivers.append%28self%29%0A%0Avolga%20%3D%20River%28%22Volga%22,%203530%29%0Aseine%20%3D%20River%28%22Seine%22,%20776%29%0Anile%20%3D%20River%28%22Nile%22,%206852%29%0A%0A%23%20print%20all%20river%20names%0Afor%20river%20in%20River.all_rivers%3A%0A%20%20%20%20print%28river.name%29%0A%23%20Output%3A%0A%23%20Volga%0A%23%20Seine%0A%23%20Nile&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=3&rawInputLstJSON=%5B%5D&textReferences=false) visualization of the code to see how it works almost in real-time!

The `__init__` method specifies what attributes we want the instances of our class to have from the very beginning. In our example, they are **name** and **length**.

## 3.2 self

You may have noticed that our `__init__` method had another argument besides name and length: **`self`**. The `self` argument represents a **particular instance of the class** and allows us to access its attributes and methods. In the example with `__init__`, we basically create attributes for the particular instance and assign the values of method arguments to them. It is important to use the `self` parameter inside the method if we want to save the values of the instance for later use.

Most of the time we also need to write the self parameter in other methods because when the method is called **the first argument that is passed to the method is the object itself**. Let's add a method to our River class and see how it works. The syntax of the methods is not of importance at the moment, just pay attention to the use of the `self` : 

```python
class River:
    all_rivers = []

    def __init__(self, name, length):
        self.name = name
        self.length = length
        River.all_rivers.append(self)

    def get_info(self):
        print("The length of the {0} is {1} km".format(self.name, self.length))
```

Now if we call this method with the objects we've created we will get this : 

```python
volga.get_info()
# The length of the Volga is 3530 km
seine.get_info()
# The length of the Seine is 776 km
nile.get_info()
# The length of the Nile is 6852 km
```

As you can see, for each object the `get_info()` method printed its particular values and that was possible because we used the `self` keyword in the method.

Note that when we actually call an object's method we don't write the `self` argument in the brackets. The `self` parameter (that represents a particular instance of the class) is passed to the instance method **implicitly** when it is called. So there are actually two ways to call an instance method: `self.method()` or `class.method(self)`. In our example it would look like this : 

```python
# self.method()
volga.get_info()
# The length of the Volga is 3530 km

# class.method(self)
River.get_info(volga)
# The length of the Volga is 3530 km
```

## 3.3 Instance attributes

Classes in Python have two types of attributes: class attributes and instance attributes. You should already know what class attributes are, so here we'll focus on the instance attributes instead. **Instance attributes** are defined within methods and they **store instance-specific information**.

In the class River, the attributes **name** and **length** are instance attributes since they are defined within a method (`__init__`) and have `self` before them. Usually, instance attributes are created within the `__init__` method since it's the constructor, but you can define instance attributes in other methods as well. However, it's not recommended **so we advise you to stick to the `__init__`**.

Instance attributes **are available only from the scope of the object** which is why this code will produce a mistake : 

```python
print(River.name)  # AttributeError
```

Instance attributes, naturally, are used to distinguish objects: their values are different for different instances .

```python
volga.name  # "Volga"
seine.name  # "Seine"
nile.name   # "Nile"
```

So when deciding which attributes to choose in your program, you should first decide whether you want it to store values unique to each object of the class or, on the contrary, the ones shared by all instances.

# 04 Methods

If attributes define the data that the objects of a particular class have, the **methods** define their behavior. Python has several types of methods that you can create within a class but, in this topic, we will focus on the instance methods.

## 4.1 Method syntax

Methods define the functionality of the objects that belong to the particular class. The basic syntax looks like this :

```python
# basic method syntax
class MyClass:
    # the constructor
    def __init__(self, arg1):
        self.att = arg1

    # custom method
    def do_smt(self):
        # does something
```

You can see that declaring a method resembles declaring a function: we have the keyword `def` followed by the name of the method. The parameters of the method are written inside the parentheses.

The first parameter of the method **should always be `self`**. You may remember that `self` represents the particular instance of the class. When it comes to instance methods, the first parameter that is passed to the method is the instance that called it.

Let's create an instance of **MyClass** and see how this works:

```python
my_object = MyClass(some_value)
# calling the instance method
my_object.do_smt()
# my_object does something
```

In this example, the **my_object** instance **is passed _implicitly(隐式地)_** so we do not write the parameter in the code. **We can, however, pass the instance explicitly**: 

```python
MyClass.do_smt(my_object)
# my_object does the same thing
```

These examples clearly illustrate why `self` has to be the first argument of the instance methods. If you want your method to have other parameters, just write them after the `self` keyword !

## 4.2 Methods vs functions

Though they are quite similar, Python does make a distinction between methods and functions. To quote the official documentation, _"a method is a function that 'belongs to' an object."_ Since we're interested in OOP, we'll specifically be looking at methods associated with class instances.

Let's consider an example:

```python
# class and its methods
class Ship:
    def __init__(self, name, capacity):
        self.name = name
        self.capacity = capacity
        self.cargo = 0

    def sail(self):
        print("{} has sailed!".format(self.name))


# function
def sail_function(name):
    print("{} has sailed!".format(name))
```

What is of interest to us here is the method `sail` of the class `Ship` and the function `sail_function`. Let's call them : 

```python
# creating an instance of the class Ship
# and calling the method sail
black_pearl = Ship("Black Pearl", 800)
black_pearl.sail()
# prints "Black Pearl has sailed!"


# calling the function sail_function
sail_function(black_pearl.name)
# also prints "Black Pearl has sailed!"
```

The way that we've defined them, both our method and our function produce the same results but in a different way. A **method is connected to an object of the class**, it is **not independent** the way a function is. Sure they are both called by their names, but to call a method we need to invoke the class that this method belongs to.

## 4.3 Return

So far, the method hasn't returned any values since we only used the `print()` function. Obviously, just as with functions, we can define what type of data the method can return with the `return` statement. For example, let's create a method that calculates how many kilograms of cargo the ship has (initially, the weight of the cargo is given in tonnes) : 

```python
class Ship:
    # other methods
    
    def convert_cargo(self):
        return self.cargo * 1000
```

The method is simple: it converts the tonnes into kilograms (by multiplying it by 1000) and then returns the calculated value. If we were to call it, we wouldn't get any messages unless we explicitly printed the result of the function : 

```python
print(black_pearl.convert_cargo())  # 0
```

Since we haven't changed the default value of the `cargo` attribute, the method would return 0 multiplied by 1000, which is also 0.

# 05 Methods and Attributes

## 5.1 Creating attributes with methods

Instance attributes are the ones defined within methods so by definition we can create new attributes inside our custom methods. Let's take the class `Ship` as an example.

```python
class Ship:
    def __init__(self, name, capacity):
        self.name = name
        self.capacity = capacity
        self.cargo = 0
```

Every ship needs a captain so let's define a method called `name_captain` for those purposes:

```python
class Ship:
    # constructor
    # ...

    def name_captain(self, cap):
        self.captain = cap
        print("{} is the captain of the {}".format(self.captain, self.name))
```

When called for the first time, the `name_captain` method creates a new attribute called `captain` and prints the corresponding message. When used next, it just changes the value of the `self.captain` attribute (and prints the message as well).

To see how it would work, let's create the ship "Black Pearl" : 

```python
black_pearl = Ship("Black Pearl", 800)
```

If we tried to print the value of the `captain` attribute now, we would get an error : 

```python
print(black_pearl.captain)  # AttributeError
```

This is because this attribute is only created within the `name_captain` method. If we call it, we will be able to access the attribute `captain` :

```python
black_pearl.name_captain("Jack Sparrow")
# prints "Jack Sparrow is the captain of the Black Pearl"

print(black_pearl.captain)  # "Jack Sparrow"
```

Note that **only those instances that have called this method will have the `captain` attribute**. It's an important thing to remember ! You may get an error if you try to use the attribute and the method hasn't been called yet.

To avoid these problems, it is recommended to define all possible attributes in the `__init__`. This can not only help you avoid `AttributeError`, but also gives a good understanding of the class and its objects from the get-go. If you do want to create the value for the attribute in a special instance method, then **list it in the `__init__` as `None`** : 

```python
class Ship:
    def __init__(self, name, capacity):
        self.name = name
        self.capacity = capacity
        self.cargo = 0
        self.captain = None
```

Then, in the specific method, you simply modify the default value which is what we'll consider in the next section.

## 5.2 Modifying attributes with methods

Methods can also be used to modify the instance attributes. Take the methods **`load_cargo`** and **`unload_cargo`** for example : 

```python
class Ship:
    def __init__(self, name, capacity):
        self.name = name
        self.capacity = capacity
        self.cargo = 0

    def load_cargo(self, weight):
        if self.cargo + weight <= self.capacity:
            self.cargo += weight
            print("Loaded {} tons".format(weight))
        else:
            print("Cannot load that much")

    def unload_cargo(self, weight):
        if self.cargo - weight >= 0:
            self.cargo -= weight
            print("Unloaded {} tons".format(weight))
        else:
            print("Cannot unload that much")
```

Both these methods are supposed to change the value of the attribute **cargo** if those changes are possible. The `load_cargo` method first checks that the loading of a particular weight will not exceed the capacity of the ship and the `unload_cargo` checks that the unloading will not make the weight of the cargo negative. Then they both make the changes or print a message that those changes are impossible.

```python
# example
black_pearl.load_cargo(600)
# "Loaded 600 tons"

black_pearl.unload_cargo(400)
# "Unloaded 400 tons"

black_pearl.load_cargo(700)
# "Cannot load that much"

black_pearl.unload_cargo(300)
# "Cannot unload that much"
```

If we wanted to print out the value of **cargo** after all these manipulations, we would see that it would equal 200 (tons). Because of the restrictions that we placed, only the first callings of `load_cargo` and `unload_cargo` made changes to the attribute **cargo.**

So far our methods haven't been returning any values since we only used the `print()` function, but we can make our methods return any type of value that we want. For example, let's create a method that calculates how much more cargo our ship can load.

```python
class Ship:
    # all other methods
    
    def free_space(self):
        return self.capacity - self.cargo
```

If we were to call this method on our Black Pearl we wouldn't get any messages, because the method doesn't print anything. But instead, we could use the value it returns in our further calculations. We could, for instance, rewrite the `load_cargo` method by using the`free_space` method : 

```python
class Ship:
    # updated load_cargo method
    def load_cargo(self, weight):
        if weight <= self.free_space():
            self.cargo += weight
            print("Loaded {} tons".format(weight))
        else:
            print("Cannot load that much")
```

In this example, we called a method inside another method and used the values in our calculations. Again, we used `self` to make sure that we only deal with the particular instance of the class `Ship` and that all calculations concern this instance.

