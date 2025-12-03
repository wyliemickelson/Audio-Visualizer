#pragma once
#include <minwindef.h>
#include <mmdeviceapi.h>
#include <vector>

struct process_info
{
	int id;
	char name[MAX_PATH];
};

std::vector<process_info> getCurrentAudioProcesses(IMMDevice* device);
void printProcessInfo(process_info* process);
IMMDevice* getDefaultAudioDevice();
std::vector<process_info> GetFullProcessList();