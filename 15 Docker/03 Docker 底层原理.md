# 3.1 Docker 如何工作？

Docker 是一个 `Client-Server` 结构的系统，Docker 的 **守护进程运行在主机上** ， 我们可以通过 **`Socket` 从客户端访问** 。Docker-Server 收到来自 Client 的指令时就会执行命令。