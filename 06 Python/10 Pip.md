# 01 What is pip?

By this time you've probably familiarized yourself with the Python standard library. It contains a lot of useful built-in modules and should be preinstalled with your Python distribution. In fact, one more thing that is preinstalled (starting with **Python 3.4**) is the **standard package manager** called **pip** (the acronym is commonly expanded as "**Pip Installs Packages**").

**Pip** is designed both to extend the functionality of the standard library by installing the additional packages on your computer and to help you share your own projects and thereby contribute to the development of Python.

## Check Pip

Now let's make sure that you have **pip** installed. All you need to do is to open a command prompt/terminal and run this line in shell :

```bash
pip --version
# or
pip3 --version
```

# 02 Install Packages

## 2.1 Lastest

Since **pip** is the recommended installer for Python, the most obvious and crucial command to begin with is `install`. Have a look at the following line :

```bash
pip install <package_name>

pip install numpy
# this command will install the `numpy` module
```

## 2.2 Specific Version

The installation is really that simple. However, if you are interested in a certain version of the package, you need to **specify it after the package name** like this :

```bash
pip install <package_name>==<version>

pip install numpy==1.1.0
```

Or, at least, define a minimal suitable version:

```bash
pip install "some_package>=version"

pip install "numpy>=1.1.0"
```

> Note that the last expression should **be enclosed within double quotes** for the comparison operator to be interpreted without any problem.

## 2.3 From the source list

When developing your project, it may be advantageous to **keep a list of packages to be installed**, i.e. **dependencies**, in a special file (see [Requirements File Format](https://pip.pypa.io/en/stable/reference/requirements-file-format/)). It is convenient because you can install the packages directly from it:

```bash
pip install -r requirements.txt
```

Of course, you are not supposed to write this file yourself listing all the necessary packages. It will be enough to run the code below in order to obtain it:

```bash
pip freeze > requirements.txt
```

# 03 Check Package

Another useful thing is the `show` command. It **shows information about installed packages**, for instance, their version, author, license, location or requirements. Here is a general example :

```bash
pip show <package_name>

pip show numpy
```

Also, the `list` command might be of use. It lists all the packages you've installed on your computer in alphabetical order:

```bash
pip list
```

If you print the `list` command with the option `--outdated`, or just `-o`, you'll get the list of outdated packages coupled with both the current and latest versions available.

```bash
pip list --outdated
```

or with a bit shorter variant:

```bash
pip list -o
```

After executing one of the mentioned lines, you will see a similar output:

```bash
first_package (Current: 2.1.1 Latest: 3.0.1)
second_package (Current: 4.2.1 Latest: 4.2.2)
```

# 04 Upgrade Package

Having discovered outdated packages, you might want to update them to the newest available version:

```bash
pip install --upgrade some_package
```

# 05 Uninstall

To remove a package from your computer run the `uninstall` command:

```no-highlight
pip uninstall some_package
```