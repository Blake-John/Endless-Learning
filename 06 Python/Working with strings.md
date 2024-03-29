# 01 Basic Methods

As you already know, the string is one of the most important data types in Python. To make working with strings easier, Python has many special built-in string methods. We are about to learn some of them.

> [!note] 
> An important thing to remember, however, is that the string is an **immutable(永恒的)** data type! It means that you cannot just change the string in-place, so most string methods **return a copy** of the string (with several exceptions). To save the changes made to the string for later use you need to create a **new variable** for the copy that you made or **assign the same name** to the copy. So, what to do with the output of the methods depends on whether you are going to use the original string or its copy later.

## 1.1 "Changing" a string

The first group of string methods consists of the ones that "change" the string in a specific way, that is they return the copy with some changes made.

The syntax for calling a method is as follows: a **string is given first** (or the name of a variable that holds a string), then comes a period **followed by the method name** and **parentheses in which arguments are listed**.

Here’s a list of common string methods of that kind:

- `str.replace(old, new, count)` **replaces all** occurrences of the `old` string with the `new` one. The `count` parameter is optional, and **if specified, only the first `count`** occurrences are replaced in the given string.
    
- `str.upper()` converts **all** characters of the string to upper case.
    
- `str.lower()` converts **all** characters of the string to lower case.
    
- `str.title()` converts the **first character of each word** to upper case.
    
- `str.swapcase()` converts upper case to lower case and vice versa.
    
- `str.capitalize()` changes the **first character of the string** to upper case and the rest to lower case.

And here's an example of how these methods are used (note that we don't save the result of every method) :

```python
message = "bonjour and welcome to Paris!"

print(message.upper())  # BONJOUR AND WELCOME TO PARIS!
# `message` is not changed
print(message)  # bonjour and welcome to Paris!

title_message = message.title() 
# `title_message` contains a new string 
# with the first character of each word capitalized
print(title_message)  # Bonjour And Welcome To Paris!

print(message.replace("Paris", "Lyon"))  # bonjour and welcome to Lyon!
replaced_message = message.replace("o", "!", 2)
print(replaced_message)  # b!nj!ur and welcome to Paris!

# again, the source string is unchanged, only its copy is modified
print(message)  # bonjour and welcome to Paris!
```

## 1.2 Removing characters from a string

Often, when you read a string from somewhere (a file or the input) you need to edit it so that it contains only the information you need. For instance, the input string can have a lot of unnecessary whitespaces or some trailing combinations of characters. The "editing" methods that can help with that are `strip()`, `rstrip()`, and `lstrip()`.

- `str.lstrip([chars])` removes the **leading characters** (i.e. characters from the left side). If the argument **`chars` isn’t specified, leading whitespaces are removed**.
    
- `str.rstrip([chars])` removes the **trailing characters** (i.e. characters from the right side). The **default for the argument `chars` is also whitespace**.
    
- `str.strip([chars])` removes both the **leading and the trailing characters**. The **default is whitespace**.

The `chars` argument, when specified, is **a string of characters that are meant to be removed from the very end or beginning of the word** (depending on the method you're using). See how it works : 

```python
whitespace_string = "     hey      "
normal_string = "incomprehensibilities"

# delete spaces from the left side
whitespace_string.lstrip()  # "hey      "

# delete all "i" and "s" from the left side
normal_string.lstrip("is")  # "ncomprehensibilities"

# delete spaces from the right side
whitespace_string.rstrip()  # "     hey"

# delete all "i" and "s" from the right side
normal_string.rstrip("is")  # "incomprehensibilitie"

# no spaces from both sides
whitespace_string.strip()  # "hey"

# delete all trailing "i" and "s" from both sides
normal_string.strip("is")  # "ncomprehensibilitie"
```

Keep in mind that the methods `strip()`, `lstrip()`, and `rstrip()` get rid of all possible combinations of specified characters : 

```python
word = "Mississippi"

# starting from the right side, all "i", "p", and "s" are removed:
print(word.rstrip("ips"))  # "M"

# the word starts with "M" rather than "i", "p", or "s", so no chars are removed from the left side:
print(word.lstrip("ips"))  # "Mississippi"

# "M", "i", "p", and "s" are removed from both sides, so nothing is left:
print(word.strip("Mips"))  # ""
```