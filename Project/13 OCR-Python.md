# 目标
实现简单易用的屏幕截图、文本识别工具
# 工具包及环境
- Python 3.10
```bash
	conda create -n ocr python=3.10
	conda activate ocr
	pip3 install cnocr
	pip3 install onnx onnxruntime
```
# 步骤
## 1. 实现OCR
- 通过调用 `cnocr` 库中的 `CnOcr` 类来创建一个对象，利用该对象进行文本识别
```Python
	import cnocr

	path = r"imgs/1.png"

	myocr = CnOcr ()
	out = myocr.ocr (path)

	for i in out :
		print (i['text'])
```
- 这段代码实现了最基本的图片识别，并将识别结果输出到终端

## 2. 实现屏幕截图
### 2.1 pyautogui
```bash
	pip3 install pyautogui
```
- 我们可以利用 `pyautogui` 库中的 `screenshot ()` 来对整个屏幕截图，并且可以将图片保存到文件
```Python
	import pyautogui

	screen_shot = pyautogui.screenshot ()
	screen_shot.save (r"out/1.png")
```
### 2.2 PIL

## 3. 实现屏幕截图的图片传给OCR
## 4. 实现GUI
### 4.1 鼠标截图
### 4.2 OCR
### 4.3 UI设计
### 4.4 封装软件
