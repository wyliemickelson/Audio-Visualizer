#include <AudioVisualizerApp.h>
#include <ProcessWindow.h>
#include <ClientData.h>
#include "LoopbackCapture.h"

void ProcessWindow::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void ProcessWindow::OnConfirm(wxCommandEvent& event)
{
    // get selected processID after confirm
	wxListBox* listBox = wxDynamicCast(this->getProcessesList(), wxListBox);
	int selected = listBox->GetSelection();
	ClientData* data = NULL;
	data = static_cast<ClientData*>(listBox->GetClientObject(selected));
	std::cout << std::endl << "Selected index: " << selected << ", Name: " << data->name << ", ProcessID: " << data->processID << std::endl;
    
    Hide();

    // start audio capture on selected process
    CLoopbackCapture loopbackCapture;

    HRESULT hr = loopbackCapture.StartCaptureAsync(data->processID);
    if (FAILED(hr))
    {
        wil::unique_hlocal_string message;
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (PWSTR)&message, 0, nullptr);
        std::wcout << L"Failed to start capture\n0x" << std::hex << hr << L": " << message.get() << L"\n";
    }
    else
    {
        while (true) {
            // run until program is terminated
        }

        loopbackCapture.StopCaptureAsync();
  
        Close(true);
    }

}

wxListBox* ProcessWindow::getProcessesList()
{
	return processes_list;
}