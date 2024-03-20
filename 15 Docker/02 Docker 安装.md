# 1 Docker 结构

Docker 的基本结构如下 : 

![](DockerStruct.png)

## 1.1 镜像 image : 

Docker 的镜像就好比一个模板，可以通过这个模板来创建 **容器服务** 。 `image => run => container`

## 1.2 容器 container

Docker 利用容器技术，独立运行一个或者一组应用，容器可以通过镜像来创建。即应用在容器中运行，与外界物理机隔离开。

## 1.3 仓库 repository

仓库是用于存放镜像的地方，分为公有和私有仓库。在国内访问仓库通常需要用镜像来加速。

> 这里说的镜像并不是指同一个东西。前者是属于 **Docker 概念中的镜像**，后者则是我们通常在使用的 **镜像站**

# 2 Install

此次安装的环境 : 
- OS : Arch Linux x86_64
- Kernel : 6.7.4-arch1-1
- DE : Hyprland

## 2.1 Prerequisites

For non-Gnome Desktop environments, `gnome-terminal` **must be installed** : 

```bash
sudo pacman -S gnome-terminal
```

## 2.2 Install Docker Desktop

We can use the AUR package to install the package, so it requires `yay` or `paru` etc. [See Also](03%20Linux/Arch/01%20基本安装#3.6.4%20Yay)

```bash
yay -S docker-desktop
```

## 2.3 Launch Docker Desktop

To start Docker Desktop for Linux, search **Docker Desktop** on the **Applications** menu and open it. This launches the Docker menu icon and opens the Docker Dashboard, reporting the status of Docker Desktop.

Alternatively, open a terminal and run : 

```bash
systemctl --user start docker-desktop
```

## 2.4 Check Installation

```bash
docker compose version
# you need to additionally install docker-compose

docker --version
# show the minimum information

docker version
# show the detailed informations
```

![](CheckInstallation.png)

To enable Docker Desktop to start on sign in, from the Docker menu, select **Settings** > **General** > **Start Docker Desktop when you sign in to your computer**.

Alternatively, open a terminal and run :

```bash
systemctl --user stop docker-desktop
```

## 2.5 Test Run

```bash
docker run hello-world
```
 
 ![](TestRun.png)

We can also check the image we have pulled from the repository by : 

```bash
docker images
```

![](CheckImages.png)

# 3 Uninstall

```bash
yay -R docker-desktop

# or you can

rm -rf /var/lib/docker /opt/docker-desktop
```

# 4 设置镜像加速

1. 创建文件夹

```bash
sudo mkdir -p /etc/docker
```

2. 编辑 `/etc/docker/daemon.json` 

```nvim
{
	"registry-mirrors": [ "https://registry.docker-cn.com" ]
}
```

3. 重新启动 docker 服务

```bash
sudo systemctl daemon-reload
sudo systemctl restart docker
```

# 5 A Quick Start for Docker

[Quick hands-on guides](https://docs.docker.com/guides/walkthroughs/what-is-a-container/)
