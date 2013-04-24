#include <windows.h>
#include "ProcessHack_WIN32.h"
#include <Poco/Exception.h>

void ProcessHack::launch(const std::string& commandLine, Poco::Pipe* inPipe, Poco::Pipe* outPipe, Poco::Pipe* errPipe)
{
	STARTUPINFO startupInfo;
	GetStartupInfo(&startupInfo); // take defaults from current process
	startupInfo.cb          = sizeof(STARTUPINFO);
	startupInfo.lpReserved  = NULL;
	startupInfo.lpDesktop   = NULL;
	startupInfo.lpTitle     = NULL;
	startupInfo.dwFlags     = STARTF_FORCEOFFFEEDBACK | STARTF_USESTDHANDLES;// | STARTF_USESHOWWINDOW;
	startupInfo.cbReserved2 = 0;
	startupInfo.lpReserved2 = NULL;

    // change by wuyao(wuyao721@163.com)
    //StartupInfo.wShowWindow=SW_HIDE;
	
	HANDLE hProc = GetCurrentProcess();
	if (inPipe)
	{
		DuplicateHandle(hProc, inPipe->readHandle(), hProc, &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
		inPipe->close(Poco::Pipe::CLOSE_READ);
	}
	else DuplicateHandle(hProc, GetStdHandle(STD_INPUT_HANDLE), hProc, &startupInfo.hStdInput, 0, TRUE, DUPLICATE_SAME_ACCESS);
	// outPipe may be the same as errPipe, so we duplicate first and close later.
	if (outPipe)
		DuplicateHandle(hProc, outPipe->writeHandle(), hProc, &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
	else
		DuplicateHandle(hProc, GetStdHandle(STD_OUTPUT_HANDLE), hProc, &startupInfo.hStdOutput, 0, TRUE, DUPLICATE_SAME_ACCESS);
	if (errPipe)
		DuplicateHandle(hProc, errPipe->writeHandle(), hProc, &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
	else
		DuplicateHandle(hProc, GetStdHandle(STD_ERROR_HANDLE), hProc, &startupInfo.hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS);
	if (outPipe) outPipe->close(Poco::Pipe::CLOSE_WRITE);
	if (errPipe) errPipe->close(Poco::Pipe::CLOSE_WRITE);

	PROCESS_INFORMATION processInfo;
	BOOL rc = CreateProcessA(
		NULL, 
		const_cast<char*>(commandLine.c_str()), 
		NULL, 
		NULL, 
		TRUE, 
		CREATE_NO_WINDOW, 
		NULL, 
		NULL, 
		&startupInfo, 
		&processInfo
	);
	CloseHandle(startupInfo.hStdInput);
	CloseHandle(startupInfo.hStdOutput);
	CloseHandle(startupInfo.hStdError);
	if (rc)
	{
		CloseHandle(processInfo.hThread);
        return;
		//return new ProcessHandleImpl(processInfo.hProcess, processInfo.dwProcessId);
	}
	else throw Poco::SystemException("Cannot launch process", commandLine);
}
