#include <VisualizerWindow.h>
#include <vector>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xmlreshandler.h>
#include <audiovisualizerapp.h>
#include <processwindow.h>
#include <processhandling.h>
#include <clientdata.h>
#include <wx/gdicmn.h>
#include <MainApp.h>
#include <Tray.h>


bool App::OnInit()
{
	//#ifdef _DEBUG
	//	AllocConsole();
	//	freopen("CONOUT$", "w", stdout);
	//#endif

	activateRenderLoop(true);
	process_window = new ProcessWindow(NULL);
	process_window->Show(true);

	//populate process list with information
	wxWindowList p_children = process_window->GetChildren();
	//wxListBox *process_list = process_selection->getProcessesList();
	process_window->populateProcessList();

	// create tray icon
	wxMenu *menu = new wxMenu();
	menu->Append(wxID_PROPERTIES, "Customize");
	menu->Append(wxID_EXIT, "Exit");
	menu->Bind(wxEVT_MENU, &App::OnExit, this, wxID_EXIT);
	menu->Bind(wxEVT_MENU, &App::OnCustomize, this, wxID_PROPERTIES);
	tray = new Tray(menu);


	return true;
}

void App::OnCustomize(wxCommandEvent& event)
{
	process_window->preview_window->Show(true);
	process_window->Show(true);
	activateRenderLoop(false);
}

void App::OnExit(wxCommandEvent& event)
{
	activateRenderLoop(false);
	tray->Destroy();
	process_window->Close();
	Exit();
}

void App::activateRenderLoop(bool on)
{
	if (on && !render_loop_on)
	{
		Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(App::onIdle));
		render_loop_on = true;
	}
	else if (!on && render_loop_on)
	{
		Disconnect(wxEVT_IDLE, wxIdleEventHandler(App::onIdle));
		process_window->visualizer->canvas->Clear();
		render_loop_on = false;
	}
}

void App::onIdle(wxIdleEvent& evt)
{
	if (render_loop_on)
	{
		// check when last render was, and only render if enough time has passed based on FPS
		Clock::time_point now = Clock::now();
		milliseconds ms_since = std::chrono::duration_cast<milliseconds>(now - last_render);
		milliseconds RENDER_THRESHOLD(1000 / FPS);
		if (ms_since > RENDER_THRESHOLD) {
			process_window->visualizer->canvas->Render();
			last_render = now; // update
		}

		evt.RequestMore(); // render continuously, not only once on idle
	}
}

wxIMPLEMENT_APP(App);
