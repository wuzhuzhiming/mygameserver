#include <stdio.h>
#include <signal.h>
#include <unistd.h>

bool g_HaveSignal;  //是否已经捕获信号

void CaptureSignals();

int main(int argc, char* argv[])
{
	printf("Base Start ...!\n");
	signal(SIGPIPE, SIG_IGN);   //屏蔽pipe信号，防止客户端连接断开时导致服务端进程结束
	CaptureSignals();
	
	int i = 1;
	while (true)
	{
		printf("%d\n", i);
		i += 1;
		sleep(1);
	}
    
	return 0;
}

void OnSignal(int iSignal);

void CaptureSignals()
{
	g_HaveSignal = false;

	//捕获自定义信号1，用于正常关闭服务器
	signal(SIGUSR1, OnSignal);

	//捕获会导致进程关闭的信号(一般是在宕机时由系统发送)，用于在宕机时保存玩家数据
	signal(SIGSEGV, OnSignal);
	signal(SIGFPE, OnSignal);
	signal(SIGILL, OnSignal);
	signal(SIGINT, OnSignal);
	signal(SIGTERM, OnSignal);
	signal(SIGABRT, OnSignal);
	signal(SIGXFSZ, OnSignal);
}

void OnSignal(int iSignal)
{
	if (g_HaveSignal)
	{
		return;
	}
	g_HaveSignal = true;

	//捕获到信号后，停止服务器逻辑，关闭所有客户端的网络连接，然后保存所有数据到数据库

	//保存所有数据后，发送系统信号给当前进程(宕机引发的系统信号)
	if (SIGUSR1 != iSignal)
	{
		signal(iSignal, SIG_DFL);
		kill(getpid(), iSignal);
	}
}