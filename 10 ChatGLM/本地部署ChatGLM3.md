# 0.环境配置
## 0.1 显卡
关于显卡驱动的安装，可以参照[[4.显卡管理|显卡管理]]，建议在官网下载驱动![[4.显卡管理#3.2 在官网下载驱动]]![[4.显卡管理#4.查看、切换显卡]]
## 0.2 CUDA Toolkit
- 若没有安装好 `CUDA library (cudart)`，或者没有将其 **初始化**，都会导致运行 ChatGLM3 时产生错误 -> `RuntimeError: Library cudart is not initialized`
### 0.2.1 安装 CUDA Toolkit
```bash
	sudo apt-get install nvidia-cuda-toolkit
```
### 0.2.2 将CUDA添加到环境路径
```bash
	export PATH=/usr/loacl/cuda/bin:$PATH
```
### 0.2.3 更新环境路径
```bash
	source ~/.bashrc
```
### 0.2.4 初始化 CUDA
```bash
	nvcc --version
```

# 1.克隆仓库
- 从 [`github`](https://github.com/THUDM/ChatGLM3) 上克隆ChatGLM的源码
```bash
	git clone git@github.com:THUDM/ChatGLM3.git
	# 或者
	git clone https://github.com/THUDM/ChatGLM3.git
```

# 2.安装依赖库
==强烈建议使用 `Anaconda` 进行管理==
## 2.1 创建虚拟环境
```bash
	conda create -n chatglm3-demo python=3.10
```
```ad-attention
注意！！！
创建虚拟环境的时候记得选择安装 `python`，并且版本要 ==>= 3.10==
如果在创建环境的时候没有选择安装python，那么后续安装依赖库的时候就无法利用 ==conda安装的 `pip`== 进行安装，这会导致两个问题：
1. 直接输入命令 `pip install <package>` 会调用系统自带的 `pip` 进行安装，此时安装路径为 `/home/blake/.local/bin`，anaconda无法读取，这将导致环境中不存在我们需要的库
2. 利用 `conda install pip` 安装好 `pip` 后，若直接安装依赖库，则会导致安装失败，因为这时没有可以解析包的 `wheel`

所以在创建虚拟环境的时候选择安装python会省去很多麻烦
```

## 2.2 安装依赖库
- 仓库中的 `requirements.txt` 已经帮我们打包好了我们需要用到的库
```bash
	cd ChatGLM3
	conda activate chatglm3-demo

	pip install -r requirements.txt
```

## 2.3 安装Jupyter内核
- 若要使用 Code Interpreter 还需要安装 Jupyter 内核
```bash
	pip install ipython ipykernel

	ipython kernel install --name chatglm3-demo --user
```

# 3.下载模型
## 3.1 模型介绍

>ChatGLM3 是智谱AI和清华大学 KEG 实验室联合发布的新一代对话预训练模型。ChatGLM3-6B 是 ChatGLM3 系列中的开源模型，在保留了前两代模型对话流畅、部署门槛低等众多优秀特性的基础上，ChatGLM3-6B 引入了如下特性：
> 	1. **更强大的基础模型：** ChatGLM3-6B 的基础模型 ChatGLM3-6B-Base 采用了更多样的训练数据、更充分的训练步数和更合理的训练策略。在语义、数学、推理、代码、知识等不同角度的数据集上测评显示，**ChatGLM3-6B-Base 具有在 10B 以下的基础模型中最强的性能**。
> 	2. **更完整的功能支持：** ChatGLM3-6B 采用了全新设计的 [Prompt 格式](https://file+.vscode-resource.vscode-cdn.net/home/blake/%E6%A1%8C%E9%9D%A2/ChatGLM3/PROMPT.md "PROMPT.md")，除正常的多轮对话外。同时原生支持[工具调用](https://file+.vscode-resource.vscode-cdn.net/home/blake/%E6%A1%8C%E9%9D%A2/ChatGLM3/tool_using/README.md "tool_using/README.md")（Function Call）、代码执行（Code Interpreter）和 Agent 任务等复杂场景。
> 	3. **更全面的开源序列：** 除了对话模型 [ChatGLM3-6B](https://huggingface.co/THUDM/chatglm3-6b "https://huggingface.co/THUDM/chatglm3-6b") 外，还开源了基础模型 [ChatGLM3-6B-Base](https://huggingface.co/THUDM/chatglm3-6b-base "https://huggingface.co/THUDM/chatglm3-6b-base")、长文本对话模型 [ChatGLM3-6B-32K](https://huggingface.co/THUDM/chatglm3-6b-32k "https://huggingface.co/THUDM/chatglm3-6b-32k")。以上所有权重对学术研究**完全开放**，在填写[问卷](https://open.bigmodel.cn/mla/form "https://open.bigmodel.cn/mla/form")进行登记后**亦允许免费商业使用**。
## 3.2 模型列表

| Model            | Seq Length | Download                                                                                                                                                                                                                                    |
| ---------------- | ---------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ChatGLM3-6B      | 8k         | [HuggingFace](https://huggingface.co/THUDM/chatglm3-6b "https://huggingface.co/THUDM/chatglm3-6b") \| [ModelScope](https://modelscope.cn/models/ZhipuAI/chatglm3-6b "https://modelscope.cn/models/ZhipuAI/chatglm3-6b")                     |
| ChatGLM3-6B-Base | 8k         | [HuggingFace](https://huggingface.co/THUDM/chatglm3-6b-base "https://huggingface.co/THUDM/chatglm3-6b-base") \| [ModelScope](https://modelscope.cn/models/ZhipuAI/chatglm3-6b-base "https://modelscope.cn/models/ZhipuAI/chatglm3-6b-base") |
| ChatGLM3-6B-32K  | 32k        | [HuggingFace](https://huggingface.co/THUDM/chatglm3-6b-32k "https://huggingface.co/THUDM/chatglm3-6b-32k") \| [ModelScope](https://modelscope.cn/models/ZhipuAI/chatglm3-6b-32k "https://modelscope.cn/models/ZhipuAI/chatglm3-6b-32k")     |

## 3.3 各模型对照硬件表

| 量化等级      | 最低 GPU 显存 |
| ------------- | ------------- |
| FP16 (无量化) | 13GB          |
| INT8          | 8GB           |
| INT4              | 6GB              |

## 3.4 下载模型
### 3.4.1 HuggingFace
- 需要挂梯子，不然根本下不了
- 平替 -> [HuggingFace镜像网站](https://hf-mirror.com/THUDM)
### 3.4.2 ModelScope
- 建议使用 `modelscope` 进行下载
#### 01 安装 modelscope
```bash
	conda activate chatglm3-demo
	pip install modelscope
```
#### 02 下载模型
```bash
	python
```
```python
>>> from modelscope import snapshot_download
>>> model_dir = snapshot_download("ZhipuAI/chatglm3-6b", revision = "v1.0.0")
```
- 下载好的文件会存放在 `~/.cache/modelscope/hub`


# 4.运行
## 4.0 文件结构
```
├── basic_demo
│   ├── cli_demo.py
│   ├── web_demo2.py
│   └── web_demo.py
├── composite_demo
│   └── main.py
├── langchain_demo
│   ├── ChatGLM3.py
│   ├── main.py
│   ├── README.md
│   ├── requirements.txt
│   ├── Tool
│   └── utils.py
└──  openai_api_demo
    ├── openai_api.py
    ├── openai_api_request.py
    └── utils.py
```
- basic_demo 中存放的是 `网页版` 和 `命令行版` 的 demo
- composite_demo 中存放的是 `网页版` 主程序
## 4.1 GPU 部署
### 4.1.1 全量部署
直接运行想要使用的版本
### 4.1.2 量化部署
- 该方式需要修改对应的源码
```python
	model = AutoModel.from_pretrained("THUDM/chatglm3-6b",trust_remote_code=True).quantize(4).cuda()
	# INT4 量化部署设置

	model = AutoModel.from_pretrained("THUDM/chatglm3-6b",trust_remote_code=True).quantize(8).cuda()
	# INT8 量化部署设置
```
- 接着运行需要的版本即可
## 4.2 CPU 部署
>大概需要 32GB 内存
>速度极慢
- 使用 CPU 部署也需要修改源码
```python
	model = AutoModel.from_pretrained("THUDM/chatglm3-6b",trust_remote_code=True).float ()
```
