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
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);

	ProcessWindow* process_selection = new ProcessWindow(NULL);
	process_selection->Show(true);

	wxWindowList p_children = process_selection->GetChildren();
	wxListBox *process_list = process_selection->getProcessesList();
	populateProcessList(process_list);
	//populate process list with information

	return true;
}

void populateProcessList(wxListBox *process_list)
{
	if (process_list)
	{
		std::vector<process_info> processes_info = getCurrentProcesses(getDefaultAudioDevice());
		int len = processes_info.size();

		std::cout << "Process List:" << std::endl;
		for (int i = 0; i < len; ++i)
		{
			process_info process_info = processes_info.at(i);
			std::cout << process_info.name << std::endl;

			process_list->Append(process_info.name, new ClientData(process_info.name, process_info.id));
			
		}
	}
}

wxIMPLEMENT_APP(App);
