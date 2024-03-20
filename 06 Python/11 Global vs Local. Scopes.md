A **[scope](https://hyperskill.org/learn/step/10372 "Scope in Python refers to the visibility or accessibility of a variable within the code. | When a variable is defined, it can be either global or local. A global variable is defined at the top level of the module and can be accessed from any code block in the program, making it useful for sharing state information or configuration between different functions. Local variables, on the other hand, are only visible within the nearest scope and cannot be accessed from the outside.")** is a part of the program where a certain [variable](https://hyperskill.org/learn/step/5859 "A variable in Python is a named location used to store data in memory. | It is created when a name is bound to a value for the first time, and it can be assigned and reassigned different values throughout the execution of a program. Variables in Python follow specific naming rules, such as not starting with a digit, not being a keyword, and using underscores or digits. They are objects in Python, meaning they have a unique identity and are created, assigned, passed, and returned like any other object.") can be reached by its [name](https://hyperskill.org/learn/step/6661 "In Python, a name is a unique identifier given to a variable, function, or any other object. | It's essentially a label that distinguishes one object from another in the same scope. This concept is not unique to Python, as most programming languages have some form of naming system for their entities. However, Python's dynamic typing and use of names as references to objects, rather than directly storing values, make its naming system particularly important to understand."). The scope is a very important concept in programming because it defines the visibility of a name within the code block.

When you [define](https://hyperskill.org/learn/step/5900 "In Python, define refers to the act of creating a new variable, function, class, or module. | This is done by assigning a value to a variable, creating a function with the def keyword, creating a class with the class keyword, or importing a module with the import keyword. Defining an entity in Python allows you to give it a name and specify its behavior, which can then be used and reused throughout your code.") a variable it becomes **either [global](https://hyperskill.org/learn/step/8804 "In Python, 'global' is a keyword used to declare a variable as global, meaning it can be accessed and modified from within a function. | By default, variables created inside a function are local, and cannot be accessed from outside the function. The 'global' keyword allows a function to access and modify global variables, which can be useful for sharing data between functions or maintaining state. However, it's generally recommended to avoid using global variables when possible, as they can make code harder to understand and debug due to their wide scope.") or local**.

# 01 Global vs. Local

## 1.1 Global

If a variable is defined at the **top-level** of the [module](https://hyperskill.org/learn/step/6057 "A module in Python is a file containing Python definitions and statements. | It helps in organizing and reusing code by allowing you to load it from other modules or scripts. Modules can be loaded using the import statement. A simple module written for direct execution is often called a script. The primary difference between a module and a script is in their usage; modules are loaded from other modules or scripts, while scripts are executed directly.") it is considered global.

That means that you can **refer to** this variable **from every code block** in your program. 

Global variables can be useful when you need to **share state information or some configuration between different [functions](https://hyperskill.org/learn/step/5900 "In Python, a function is a block of reusable code that performs a specific task. | It is defined using the `def` keyword followed by the function name, parameters, and the code block. Functions can take zero or more arguments, and they can return one or more values. They help in breaking down large programs into smaller and manageable tasks, making the code more readable and maintainable. Functions can be used to encapsulate complex logic, making it easier to test and debug.").**

## 1.2 Local

Local variables are created when you define them **in the body of a function**.

So its name can **only be resolved inside the current function's scope**.

### Consider the difference

```python
phrase = "Let it be"

def global_printer():
    print(phrase)  # we can use phrase because it's a global variable

global_printer()  # Let it be is printed
print(phrase)  # we can also print it directly

phrase = "Hey Jude"

global_printer()  # Hey Jude is now printed because we changed the value of phrase

def printer():
    local_phrase = "Yesterday"
    print(local_phrase)  # local_phrase is a local variable

printer()  # Yesterday is printed as expected

print(local_phrase)  # NameError is raised
```

The error will be : `NameError: name 'local_phrase' is not defined`

> [!summary] 
> Thus, a **global variable** can be accessed both **from the top-level of the module and the function's body**. On the other hand, a **local variable** is **only visible inside the nearest scope** and cannot be accessed from the outside.

# 02 LEGB rule

A variable resolution in Python follows the **LEGB rule**. That means that the [interpreter](https://hyperskill.org/learn/step/6047 "The interpreter in Python is a layer of software logic that executes your code, translating it line by line. | It's part of the standard Python installation package. When you write larger programs, it's more efficient to prepare your code in advance using a text editor and then run it with the interpreter. A file containing a list of operations that will be read and interpreted further on is called a script. The interpreter is responsible for translating your code into a form that the hardware can understand and execute.") looks for a name in the following [order](https://hyperskill.org/learn/step/10059 "In Python, order is the sequence or arrangement in which operations or elements are processed or organized. | In terms of operations, Python follows a left-to-right operation convention, similar to mathematics, where operations are performed in a specific sequence, such as parentheses, exponentiation, multiplication and division, and addition and subtraction, also known as the order of operations. In terms of data structures like lists, order refers to the position of elements within the structure, where each element has an index that corresponds to its position. This order is maintained unless explicitly altered through programming methods or operations."):

1. **Locals** : Variables defined within the **function body** and **not [declared](https://hyperskill.org/learn/step/6384 "In Python, there is no explicit 'declare' keyword or concept as in some other programming languages. | Instead, Python uses dynamic typing, which means that variables can hold values of different data types at different times during the execution of the program. When a variable is assigned a value for the first time, Python automatically determines the data type of the variable based on the assigned value. Therefore, there is no need to declare a variable's data type before using it.") globa**l.
2. **Enclosing** : Names of the local scope in all enclosing functions **from inner to outer**.
3. **Globals** : Names defined at the top-level of a module or declared global with a `global` [keyword](https://hyperskill.org/learn/step/10372 "Keywords in Python are reserved words that have special meanings and cannot be used as variable or function names. | They are part of the Python syntax and are used to define the structure and behavior of the code. Some examples of Python keywords include if, else, while, for, in, not, and, or, is, def, return, and import. These keywords are used to create control flow structures, define functions, and import modules, among other things.").
4. **Built-in** : Any built-in name in Python.

Let's consider an example to illustrate the LEGB rule:

```python
x = "global"
def outer():
    x = "outer local"
    def inner():
        x = "inner local"
        def func():
            x = "func local"
            print(x)
        func()
    inner()

outer()
```

And the output is `func local` .

# 03 Keywords "nonlocal" and "global"

## 3.1 `global`

We already mentioned one way to assign a global variable: make a definition **at the top-level of a module**. 

But there is also a special keyword `global` that allows us to **declare a variable global inside a function's body**.

You can't change the value of a global variable inside the function without using the `global` keyword:

```python
x = 1
def print_global():
    print(x)

print_global()  # 1

def modify_global():
    print(x)
    x = x + 1

modify_global()
```

This time will lead to the error `UnboundLocalError: cannot access local variable 'x' where it is not associated with a value` or `UnboundLocalError: local variable 'x' referenced before assignment` 
The error is raised because to execute `print(x)` on the 8th line, the **interpreter tries to resolve `x` and finds it in the _local_ scope** – the local `x` is declared on the next, 9th, line, i.e. **after its use on line 8**, so the interpreter raises the [error](https://hyperskill.org/learn/step/6052 "An error in Python is a problem that occurs while the program is running, which prevents it from executing correctly. | These issues are usually caused by logical mistakes in the code, and they can be identified by the error messages that Python displays. These messages often include details about the type of error, the location in the code where it occurred, and sometimes even a suggested fix. Understanding and addressing these errors is a crucial part of the programming process, as they can provide valuable insights into how the code is functioning and where improvements can be made."). 

However, if we removed line 8, the same would happen. In that case, to execute `x = x + 1`, the **interpreter would need to compute the expression `x + 1` and resolve the variable `x` in it, however, it is declared in the same line**. Since its value would be needed before it had actually been computed, the error raised.

> [!attention] 
> Remember, the interpreter **checks the local scope first** !

To fix this error, we need to declare `x` global:

```python
x = 1
def global_func():
    global x
    print(x)
    x = x + 1

global_func()  # 1
global_func()  # 2
global_func()  # 3
```

When `x` is global you can increment its value **inside** the function.

## 3.2 `nonlocal`

`nonlocal` keyword lets us assign to variables **in the outer** (but **not global**) scope:

```python
def func():
    x = 1
    def inner():
        x = 2
        print("inner:", x)
    inner()
    print("outer:", x)

def nonlocal_func():
    x = 1
    def inner():
        nonlocal x
        x = 2
        print("inner:", x)
    inner()
    print("outer:", x)

func()  # inner: 2
        # outer: 1

nonlocal_func()  # inner: 2
                 # outer: 2
```

Though `global` and `nonlocal` are present in the language, they are **not often used in practice**, because these keywords make programs less predictable and harder to understand.

# 04 Why do we need scopes?

Python distinguishes between global and local scopes to **enhance code organisation**. 

Global scope allows **retaining information between function** calls, aiding data transfer and communication in complex processes like multithreading. 

However, if all the declarations were stored in a global scope, the **namespace would be extremely clogged up and hard to navigate**, which may lead to confusion and bugs. 

Therefore Python saves you the trouble by allowing you to "isolate" some variables from the rest of the code when you split it into functions.