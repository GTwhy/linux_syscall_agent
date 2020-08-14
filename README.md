项目说明：
    本项目为Linux系统调用代理，将用户进程的系统调用交由系统调用代理守护程序代为执行。

使用说明：
    1.在lsca项目顶层目录执行命令make即可在daemon和lib文件夹下分别生成daemon可执行程序和agent_lib.so动态链接库。
    2.调用代理（以hello_world程序为例）：在example目录下执行命令LD_PRELOAD=../agent_lib.so hello_world
    3.在顶层目录下执行命令 make clean可清楚源码之外的临时文件、可执行程序和动态链接库。

目录说明：
    daemon：守护进程
    headers：各部分的头文件
    lib：用于代理的动态链接库
    socket_echo：项目要求的echo server和echo client程序
    syscall_agents:守护进程代理系统调用所需对应的代理程序
    tools：项目所需的工具程序，为守护进程与动态链接库共用
    test:前期测试所使用的代码文件
    examples:用于测试系统调用代理服务的例程
    video：操作演示

备注：
	本程序开发和编译环境为鲲鹏云（AArch64） Ubuntu 18.04.3 LTS (GNU/Linux 4.15.0-70-generic aarch64)
	make后可执行程序经测试在openEuler 下可正常使用


