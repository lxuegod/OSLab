/*
提供该示例代码是为了阐释一个概念，或者进行一个测试，并不代表着
最安全的编码实践，因此不应在应用程序或网站中使用该示例代码。对
于超出本示例代码的预期用途以外的使用所造成的偶然或继发性损失，
北京英真时代科技有限公司不承担任何责任。
*/

#include "EOSApp.h"

//	bool类型头文件
#include <stdbool.h>

//	宏定义10个进程
#define Num 10


//
// main 函数参数的意义：
// argc - argv 数组的长度，大小至少为 1，argc - 1 为命令行参数的数量。
// argv - 字符串指针数组，数组长度为命令行参数个数 + 1。其中 argv[0] 固定指向当前
//        进程所执行的可执行文件的路径字符串，argv[1] 及其后面的指针指向各个命令行
//        参数。
//        例如通过命令行内容 "a:\hello.exe -a -b" 启动进程后，hello.exe 的 main 函
//        数的参数 argc 的值为 3，argv[0] 指向字符串 "a:\hello.exe"，argv[1] 指向
//        参数字符串 "-a"，argv[2] 指向参数字符串 "-b"。
//




int main(int argc, char* argv[])
{
	//
	// 启动调试 EOS 应用程序前要特别注意下面的问题：
	//
	// 1、如果要在调试应用程序时能够调试进入内核并显示对应的源码，
	//    必须使用 EOS 核心项目编译生成完全版本的 SDK 文件夹，然
	//    后使用此文件夹覆盖应用程序项目中的 SDK 文件夹，并且 EOS
	//    核心项目在磁盘上的位置不能改变。
	//
	
	STARTUPINFO StartupInfo;
	//PROCESS_INFORMATION ProcInfoOne, ProcInfoTwo;
	
	//	定义进程数组
	PROCESS_INFORMATION ProcInfo[Num];
	
	ULONG ulExitCode;	// 子进程退出码
	INT nResult = 0;	// main 函数返回值。0 表示成功，非 0 表示失败。

	//printf("Create two processes and wait for the processes exit...\n\n");
	printf("Create ten processes and wait for the processes exit...\n\n");

	//
	// 使子进程和父进程使用相同的标准句柄。
	//
	StartupInfo.StdInput = GetStdHandle(STD_INPUT_HANDLE);
	StartupInfo.StdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	StartupInfo.StdError = GetStdHandle(STD_ERROR_HANDLE);

	//
	// 为一个应用程序同时创建十个子进程。
	//
	int j;
	
	bool flag = true;
	for (j = 0; j < Num; j++) {
		flag = flag && CreateProcess("A:\\Hello.exe", NULL, 0, &StartupInfo, &ProcInfo[j]);
	}
		
	if(flag) {
		
		for (j = 0; j < Num; j++) {
			//
			// 创建子进程成功，等待子进程运行结束。
			//
			WaitForSingleObject(ProcInfo[j].ProcessHandle, INFINITE);
		}
		for (j = 0; j < Num; j++) {
			//
			// 得到并输出子进程的退出码。
			//
			GetExitCodeProcess(ProcInfo[j].ProcessHandle, &ulExitCode);
			printf("\nThe process %d exit with %d.\n", j+1, ulExitCode);
		}
		for (j = 0; j < Num; j++) {
			
			//
			// 关闭不再使用的句柄。
			//
			CloseHandle(ProcInfo[j].ProcessHandle);
			CloseHandle(ProcInfo[j].ThreadHandle);
		}
			
	}else {

		printf("CreateProcess Failed, Error code: 0x%X.\n", GetLastError());
		nResult = 1;
	}
	


	return nResult;
}


