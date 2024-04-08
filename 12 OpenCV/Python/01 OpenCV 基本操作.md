# 1 IO 操作

## 1.1 读取图像

```python
cv.imread ()
```

**Declaration :** 

```python
(function) def imread(  
	filename: str,  
	flags: int = ...  
) -> MatLike
```

**Parameters :** 

- `filename` : 文件路径
- `flags` : 读取图片的方式
	- `cv2.IMREAD_COLOR`
	- `cv2.IMREAD_GRAYSCALE` 
	- `cv2.IMREAD_UNCHANGED` : 包括 `alpha` 通道的加载图像模式

> [!attention] 
> 如果加载图片的路径有误，，不会报错，而是会返回一个 `None` 值！

## 1.2 显示图像

### 1.2.1 `cv2.imshow ()` 

```python
cv2.imshow ()
```

**Declatation :** 

```python
(function)  
def imshow(  
	winname: str,  
	mat: MatLike  
) -> None: ...
```

**Parameters :** 
- `winname` : 显示窗口名
- `mat` : 要显示的图像

> [!note] 
> 使用 `cv2.imshow ()` 后，应该使用 `cv2.waitKey ()` 来使窗口停滞

### 1.2.2 `cv2.waitKey ()` 

```python
(function) def waitKey(delay: int = ...) -> int
```

> 当 `delay` 为 `0` 时代表延迟时间为 **无限久** 

## 1.3 保存图像

```python
cv2.imwrite ()
```

**Declaration :** 

```python
(function)  
	def imwrite(  
	filename: str,  
	img: MatLike,  
	params: Sequence[int] = ...  
) -> bool: ...
```

**Parameters :**

- `filename` : where to save the img
- `img` : which to save

# 2 绘制几何图形

## 2.1 Line

```python
cv2.line ()
```

**Declaration :** 

```python
(function)  
def line(  
	img: MatLike,  
	pt1: Point,  
	pt2: Point,  
	color: Scalar,  
	thickness: int = ...,  
	lineType: int = ...,  
	shift: int = ...  
) -> MatLike: ...
```

**Parameters :** 
- `img` : where to draw
- `pt1` : first point
- `pt2` : second point
- `color` 
- `thickness` : the thickness of the line

## 2.2 Circle

```python
cv2.circle ()
```

**Declaration :** 

```python
(function)
def circle(  
	img: MatLike,  
	center: Point,  
	radius: int,  
	color: Scalar,  
	thickness: int = ...,  
	lineType: int = ...,  
	shift: int = ...  
) -> MatLike: ...
```

**Parameters :** 
- `thickness` : `-1` or `cv2.FILLED` will fill the circle

## 2.3 Rectangle

```python
cv2.rectangle ()
```

**Declaration :** 

```python
(function)  
def rectangle(  
	img: MatLike,  
	pt1: Point,  
	pt2: Point,  
	color: Scalar,  
	thickness: int = ...,  
	lineType: int = ...,  
	shift: int = ...  
) -> MatLike: ...

def rectangle(  
	img: MatLike,  
	rec: Rect,  
	color: Scalar,  
	thickness: int = ...,  
	lineType: int = ...,  
	shift: int = ...  
) -> MatLike: ...
```

**Parameters :** 
- `pt1` : top-left vertex
- `pt2` : bottom-right vertex
- `rec` : the rectangle generated from cv2

## 2.4 Put Text

```python
cv2.putText ()
```

**Declaration :** 

```python
(function)  
def putText(  
	img: MatLike,  
	text: str,  
	org: Point,  
	fontFace: int,  
	fontScale: float,  
	color: Scalar,  
	thickness: int = ...,  
	lineType: int = ...,  
	bottomLeftOrigin: bool = ...  
) -> MatLike: ...
```

**Parameters :** 
- `org` : the bottom-left of the text
- `fontFace` : choose the font
- `fontScale` : how large is the text

## 2.5 Create a pure color img

```python
img = np.zeros ((512, 512, 3), np.uint8)
# np.zeros (shape, dtype)
```

**Parameters :** 
- `shape` : the shape of the array, for the img, it is (height, width, channels)
- `dtype` : the number type of the array

# 3 图像操作

## 3.1 像素操作

我们可以获取图像中某一点的 **像素值** ，对于由OpenCV读取的 **彩色图像**，会返回一个 `[blue, green, red]` 的数组； **对于灰度图** ，则会返回该点的灰度值。

```python
img = cv2.imread ("test.jpg")

# 获取像素值
px = img[100, 100]

# 修改某一点的像素值
img[100, 100] = [255, 255, 255]

# 修改一部分图像的像素值
img[75 : 125, 75 : 100] = [255, 0, 255]

# 修改某些位置某一通道的像素值
img[75 : 125, :, 0] = 100
# 将第75到125行的 blue 通道的值改为 100
```

## 3.2 获取图像的属性

| 属性 | API |
| ---- | ---- |
| 形状 | `img.shape` |
| 图像的大小 | `img.size`  |
| 数据类型 | `img.dtype`  |

## 3.3 通道拆分及合并

### 3.3.1 拆分

我们可以使用数组的操作来获取颜色通道，也可以使用内部自带的函数来分离颜色通道。

```python
# 通过数组操作来分离，获取颜色通道
blue = img[:, :, 0] # 获取蓝色通道
green = img[:, :, 1] # 获取绿色通道
red = img[:, :, 2] # 获取红色通道

# 通过函数来分离通道
b, g, r = cv2.split (img)
```

### 3.3.2 合并

我们直接使用函数来合并图像

```python
img = cv2.merge (b, g, r)
```

## 3.3 色彩空间的改变

```python
c2.cvtColor ()
```

**Declaration :** 

```python
(function)  
	def cvtColor(  
	src: MatLike,  
	code: int,  
	dst: MatLike | None = ...,  
	dstCn: int = ...  
) -> MatLike: ...
```

**Parameters :** 
- `src` : source img
- `code` : the mode to change the color space
	- `cv2.COLOR_BGR2RGB` 
	- `cv2.COLOR_BGR2HSV` 
	- `cv2.COLOR_BGR2GRAY` 

# 4 算数操作

## 4.1 图像加法

你可以使用OpenCV的 `cv2.add()` 函数把两幅图像相加，或者可以简单地通过numpy操作添加两个图像，如 `res=img1+img2` 。两个图像应该具有 **相同的大小和类型**，**或者第二个图像可以是标量值**。

> 注意：OpenCV加法和Numpy加法之间存在差异。OpenCV的加法是 **饱和操作**，而Numpy添加是 **模运算**。

### 4.1.1 `cv2.add ()` 

我们可以通过 OpenCV 内置的函数来进行图像的加法，当 **超过 `255` 时，会被赋值成 `255` ** 。

```python
cv2.add ()
```

**Declaration :** 

```python
(function)  
def add(  
	src1: MatLike,  
	src2: MatLike,  
	dst: MatLike | None = ...,  
	mask: MatLike | None = ...,  
	dtype: int = ...  
) -> MatLike: ...
```

**Parameters :** 
- `src1` : first img to be added
- `src2` : second img

### 4.1.2 矩阵加法

`numpy` 模块的加法是 **模运算** ，当数值超过 `255` 时，会 **对 `256` 求模** 。

```python
x = np.uint8 ([250])
y = np.uint8 ([10])

print (x + y)
# 4 -> 250 + 10 = 260 % 256 == 4
```

## 4.2 图像的混合

图像的混合其实就是 **图像加权的加法** ，使用 `cv2.addWeighted ()` ，可以使用带权重的加法

```python
cv2.addWeighted ()
```

**Declaratoin :** 

```python
(function)  
def addWeighted(  
	src1: MatLike,  
	alpha: float,  
	src2: MatLike,  
	beta: float,  
	gamma: float,  
	dst: MatLike | None = ...,  
	dtype: int = ...  
) -> MatLike: ...
```

**Parameters :** 
- `alpha` : the weight of the first img
- `beta` : the weight of the second img
- `gamma` : the addtion number to add on the result img

> [!attention] 
> 不管是否带权重的加法，两幅图像必须有 **相同大小** 。

