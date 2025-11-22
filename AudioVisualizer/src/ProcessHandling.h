#pragma once
#include <minwindef.h>
#include <mmdeviceapi.h>
#include <vector>

struct process_info
{
	int id;
	char name[MAX_PATH];
};

std::vector<process_info> getCurrentProcesses(IMMDevice* device);
IMMDevice* getDefaultAudioDevice();
