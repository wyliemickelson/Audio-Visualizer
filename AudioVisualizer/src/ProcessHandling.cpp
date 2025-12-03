#include <windows.h>
#include <mmdeviceapi.h>
#include <Audioclient.h>
#include <audioclientactivationparams.h>
#include <Psapi.h>
#include <iostream>
#include <cstdlib>
#include <audiopolicy.h>
#include <processthreadsapi.h>
#include <vector>
#include <algorithm>
#include <tlhelp32.h>

#include <ProcessHandling.h>
#define ARRAY_SIZE (16)

/*
* Grab and return array of info on processes for given audio device,
* set count to length.
*
*/
std::vector<process_info> getCurrentAudioProcesses(IMMDevice* device)
{
	std::vector<process_info> allProcesses = GetFullProcessList();
	std::vector<process_info> processes_using_audio;

	IAudioSessionManager2* SessionManager;
	if (FAILED(device->Activate(
		__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&SessionManager)))
	{
		std::cerr << "ERROR: Failed retrieving IAudioSessionManager." << std::endl;
	}

	IAudioSessionEnumerator* SessionEnum;
	if (FAILED(SessionManager->GetSessionEnumerator(&SessionEnum)))
	{
		std::cerr << "ERROR: Failed retrieving IAudioSessionEnumerator" << std::endl;
	}

	int session_count = 0;
	SessionEnum->GetCount(&session_count);

	for (int i = 0; i < session_count; ++i)
	{
		//get session control for each session
		IAudioSessionControl* SessionControl;
		SessionEnum->GetSession(i, &SessionControl);
		IAudioSessionControl2* SessionControl2;
		SessionControl->QueryInterface(&SessionControl2);
		LPWSTR session_name;
		SessionControl->GetDisplayName(&session_name);
		//get process info
		DWORD process_id = 0;
		SessionControl2->GetProcessId(&process_id);

		HANDLE process;
		if ((process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id)))
		{
			char moduleName[MAX_PATH]; //name of executable for process
			process_info pinfo;

			if (GetModuleBaseNameA(process, NULL, moduleName, MAX_PATH))
			{
				DWORD process_id = GetProcessId(process);
				pinfo.id = process_id;

				strncpy_s(pinfo.name, moduleName, MAX_PATH);
			}
			else {
				// process name couldn't be opened, so check full process list for matching PID and get name

				// match current pid to full process list
				auto p = std::find_if(allProcesses.begin(), allProcesses.end(),
					[process_id](process_info process) -> bool { return process.id == process_id; });

				pinfo.id = p->id;
				strncpy_s(pinfo.name, p->name, MAX_PATH);
			}

			char* strtok_state = {};
			char* name = {};
			name = strtok_s(pinfo.name, ".", &strtok_state); //remove '.exe'
			name[0] = toupper(name[0]); //capitalize first letter

			processes_using_audio.push_back(pinfo);
		}

	}
	return processes_using_audio;
}

std::vector<process_info> GetFullProcessList()
{
	std::vector<process_info> processes;

	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return processes;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap); // clean the snapshot object
		return processes;
	}

	// walk the snapshot of processes
	do
	{
		// get information
		process_info pinfo;
		pinfo.id = pe32.th32ProcessID;
		wcstombs_s(NULL, pinfo.name, sizeof(pinfo.name), pe32.szExeFile, sizeof(pe32.szExeFile));

		// add to returned process list
		processes.push_back(pinfo);

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return processes;
}

void printProcessInfo(process_info* process)
{
	std::cout << "Process ID: " << process->id << std::endl;
	std::cout << "Process Name: " << process->name << std::endl;
}

IMMDevice* getDefaultAudioDevice()
{
	IMMDeviceEnumerator* DeviceEnum;
	if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL,
		CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
		(void**)&DeviceEnum)))
	{
		std::cerr << "ERROR: Failed to grab device enumerator." << std::endl;
	}

	IMMDevice* device; //get default system audio device
	if (FAILED(DeviceEnum->GetDefaultAudioEndpoint(
		eRender,
		eMultimedia,
		&device
	)))
	{
		std::cerr << "ERROR: Failed to get default audio endpoint." << std::endl;
	}
	else
	{
		return device;
	}

}