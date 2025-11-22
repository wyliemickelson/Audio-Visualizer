#include <VisualizerWindow.h>
#include <vector>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xmlreshandler.h>
#include <audiovisualizerapp.h>
#include <processwindow.h>
#include <processhandling.h>
#include <clientdata.h>

//prototypes
void populateProcessList(wxListBox *process_list);

class App : public wxApp
{
	public:
		virtual bool OnInit();
};

bool App::OnInit()
{
	// set console to the one that started the .exe
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	ProcessWindow* process_selection = new ProcessWindow(NULL);
	process_selection->Show(true);

	//populate process list with information
	wxWindowList p_children = process_selection->GetChildren();
	wxListBox *process_list = process_selection->getProcessesList();
	populateProcessList(process_list);

	return true;
}

void populateProcessList(wxListBox *process_list)
{
	if (process_list)
	{
		std::vector<process_info> processes_info = getCurrentProcesses(getDefaultAudioDevice());
		int len = processes_info.size();

		for (int i = 0; i < len; ++i)
		{
			process_info process_info = processes_info.at(i);

			process_list->Append(process_info.name, new ClientData(process_info.name, process_info.id));
			
		}
	}
}

wxIMPLEMENT_APP(App);
