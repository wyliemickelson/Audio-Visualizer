#pragma once
#include <minwindef.h>
#include <mmdeviceapi.h>

struct process_info
{
	int id;
	char name[MAX_PATH];
};

process_info* getCurrentProcesses(IMMDevice* device, int* count);
