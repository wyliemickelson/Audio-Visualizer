#include <windows.h>
#include <mmdeviceapi.h>
#include <Audioclient.h>
#include <audioclientactivationparams.h>
#include <Psapi.h>
#include <iostream>
#include <cstdlib>
#include <audiopolicy.h>
#include <processthreadsapi.h>

#include <ProcessHandling.h>
#define ARRAY_SIZE (16)

/*
* Grab and return array of info on processes for given audio device,
* set count to length.
*
*/
process_info* getCurrentProcesses(IMMDevice* device, int* count)
{

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
	int j = 0; //process_info array pos (skip process handles that cant be retrieved)

	process_info processes[ARRAY_SIZE];

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
		if ((process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, process_id)))
		{
			char execName[MAX_PATH]; //name of executable for process
			GetProcessImageFileNameA(
				process,
				execName,
				MAX_PATH
			);
			DWORD process_id = GetProcessId(process);
			process_info pinfo;
			pinfo.id = process_id;
			strncpy_s(pinfo.name, execName, MAX_PATH);
			processes[j++] = pinfo;
		}
	}
	*count = j;
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
