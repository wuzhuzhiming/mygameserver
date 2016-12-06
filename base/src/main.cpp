#include <stdio.h>
#include <signal.h>
#include <unistd.h>

bool g_HaveSignal;  //�Ƿ��Ѿ������ź�

void CaptureSignals();

int main(int argc, char* argv[])
{
	printf("Base Start ...!\n");
	signal(SIGPIPE, SIG_IGN);   //����pipe�źţ���ֹ�ͻ������ӶϿ�ʱ���·���˽��̽���
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

	//�����Զ����ź�1�����������رշ�����
	signal(SIGUSR1, OnSignal);

	//����ᵼ�½��̹رյ��ź�(һ������崻�ʱ��ϵͳ����)��������崻�ʱ�����������
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

	//�����źź�ֹͣ�������߼����ر����пͻ��˵��������ӣ�Ȼ�󱣴��������ݵ����ݿ�

	//�����������ݺ󣬷���ϵͳ�źŸ���ǰ����(崻�������ϵͳ�ź�)
	if (SIGUSR1 != iSignal)
	{
		signal(iSignal, SIG_DFL);
		kill(getpid(), iSignal);
	}
}