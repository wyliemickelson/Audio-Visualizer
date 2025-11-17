#include <AudioVisualizerApp.h>
#include <ProcessWindow.h>

void ProcessWindow::OnExit(wxCommandEvent& event)
{
	Close(true);
}
wxListBox* ProcessWindow::getProcessesList()
{
	return processes_list;
}