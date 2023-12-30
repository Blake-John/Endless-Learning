# why?
* PyTorch是用于训练神经网络的框架，而非部署应用的框架，在PyTorch下部署网络会显得比较慢
* 而ONNX专门为部署进行优化，能够很好地兼容各大平台的软件硬件
![[模型部署通用流程.png]]
* 作为桥梁，训练的归训练，部署的归部署，ONNX极大降低了部署难度 ![[原型.png]]![[优势.png]]
# what
* ONNX (Open Neural Network Exchange)
# 安装配置环境
* 安装 `PyTorch`
```bash
	conda activate env_pytorch
	conda install pytorch torchvision torchaudio pytorch-cuda=12.1 -c pytorch -c nvidia
```
* 安装onnx、onnxruntime
```bash
	conda install onnx onnxruntime
```
* 安装第三方工具包
```bash
	conda install numpy pandas matplotlib tqdm pillow
	pip install opencv-python
```
# Pytorch图像分类模型转ONNX
* 利用pytorch提供好的预训练模型进行转化测试
## 1.导入工具包
```python
	import torch
	from torchvision import models

	device = torch.device ("cuda" if torch.cuda.is_available () else "cpu")
	print ("device: ",device)
```
## 2.载入ImageNet预训练PyTorch图像分类模型
```python
	model = moodels.resnet18 (pretrained=True)
	model = model.eval ().to (device)
```
## 3.构造一个输入图像Tensor
```python
	x = torch.randn (1,3,256,256).to (device)
	# (batch_size,channels,width,height)
```
## 4.输入PyTorch模型推理预测
```python
	output = model (x)
	# output.shape --> torch.Size ([1,1000])
```
## 5.Pytorch模型转ONNX格式
```python
	with torch.no_grad () :
		torch.onnx.export (
			model,                    # 要转化的模型
			x,                        # 模型的任意一组输入
			"resnet18_imgnet.onnx",   # 导出的 ONNX 文件名
			opset_version=11,         # ONNX 算子集版本
			input_names=["input"],    # 输入 Tensor 的名称
			output_names=["output"]   # 输出 Tensor 的名称
		)
```
## 6.验证模型导出成功
```python
	import onnx

	onnx_model = onnx.load ("resnet18_imgnet.onnx")
	onnx.checker.check_model (onnx_model)
	
	print ("Succeed!")
```
## 7.以可读形式打印计算图
```python
	print (onnx.helper.printable_graph (onnx_model.graph))
```
# Pytorch水果图像分类模型转化
## 1.下载模型权重文件
```bash
	wget https://zihao-openmmlab.obs.cn-east-3.myhuaweicloud.com/20220716-mmclassification/checkpoints/fruit30_pytorch_20220814.pth -P checkpoint\n
```
## 2.导入训练好的模型并转化
```python
	import torch
	
	device = torch.device ("cuda" if torch.cuda.is_available else "cpu")
	
	model = torch.load ("checkpointn/fruit30_pytorch_20220814.pth")
	model = model.eval ().to (device)
	
	x = torch.randn (1,3,256,256).to (device=device)
	output = model (x)
	
	with torch.no_grad () :
		torch.onnx.export (
			model=model,
			args=x,
			f="resnet18_fruit30.onnx",
			opset_version=11,
			input_names=["input"],
			output_names=["output"]
		)
```
## 3.验证模型
```python
	import onnx

	onnx_model = onnx.load ("resnet18_fruit30.onnx")
	
	print (onnx.checker.check_model (onnx_model))
	print ("Succeed!")
	
	print (onnx.helper.printable_graph (onnx_model.graph))
```