#include <ProcessWindow.h>
#include <ClientData.h>
#include <VisualizerWindow.h>
#include <CustomizationWindow.h>
#include <LoopbackCapture.h>
#include <wx/taskbar.h>
#include <Tray.h>
#include "wx/app.h"
#include <MainApp.h>

CLoopbackCapture loopbackCapture;

wxDECLARE_APP(App);

void ProcessWindow::OnExit(wxCommandEvent& event)
{
	preview_window->Close(true);
	Destroy();
}

void ProcessWindow::OnRefresh(wxCommandEvent& event) {
	wxListBox* process_list = getProcessesList();
	process_list->Clear();
	populateProcessList();
}
void ProcessWindow::OnClose(wxCloseEvent& event)
{
	wxGetApp().activateRenderLoop(false);
	preview_window->Close(true);
	Destroy();
}

void ProcessWindow::OnReset(wxCommandEvent& event)
{
	pos_x_slider->SetValue(0);
	pos_y_slider->SetValue(0);
	size_x_slider->SetValue(screen_size.x);
	size_y_slider->SetValue(50);
	pos_x_text->SetValue(std::to_string(pos_x_slider->GetValue()));
	pos_y_text->SetValue(std::to_string(pos_y_slider->GetValue()));
	size_x_text->SetValue(std::to_string(size_x_slider->GetValue()));
	size_y_text->SetValue(std::to_string(size_y_slider->GetValue()));
	SetPreviewPos();
}

void ProcessWindow::OnConfirm(wxCommandEvent& event)
{
    // get selected processID after confirm
	wxListBox* listBox = wxDynamicCast(this->getProcessesList(), wxListBox);
	int selected = listBox->GetSelection();

	if (selected == wxNOT_FOUND) {
		wxString errorMessage = "An error occurred: Please select a process to visualize.";
		wxMessageBox(errorMessage, "Error", wxOK | wxICON_ERROR, this);
		return;
	}

	preview_window->Hide();
	ClientData* data = NULL;
	data = static_cast<ClientData*>(listBox->GetClientObject(selected));

	std::cout << std::endl << "Selected index: " << selected << ", Name: " << data->name << ", ProcessID: " << data->processID << std::endl;
    
	// get visualizer options
	//
	VisualizerOptions* selectedOptions = new VisualizerOptions();

	// layout
	selectedOptions->layout = static_cast<VisualizerLayout>(visualizer_layout_choice->GetCurrentSelection());

	// processID
	selectedOptions->processID = data->processID;

	// amplitude thresholds
	selectedOptions->amplitudeThresholds[0] = amp_thresh_quiet->GetValue();
	selectedOptions->amplitudeThresholds[1] = amp_thresh_medium->GetValue();
	selectedOptions->amplitudeThresholds[2] = amp_thresh_loud->GetValue();

	// amplitude colors
	wxColor c = amp_colorpicker_quiet->GetColour();
	selectedOptions->amplitudeColors[0] = VisualizerColor((float)c.Red(), (float)c.Green(), (float)c.Blue(), (float)c.Alpha());
	c = amp_colorpicker_medium->GetColour();
	selectedOptions->amplitudeColors[1] = VisualizerColor((float)c.Red(), (float)c.Green(), (float)c.Blue(), (float)c.Alpha());
	c = amp_colorpicker_loud->GetColour();
	selectedOptions->amplitudeColors[2] = VisualizerColor((float)c.Red(), (float)c.Green(), (float)c.Blue(), (float)c.Alpha());
	//

	// start loopback on new process if processID changed, otherwise keep original loopback open
	if (selectedOptions->processID != visualizer->options->processID) {
		// stop current audio capture if one is open
		HRESULT hr = loopbackCapture.StopCaptureAsync();
		if (FAILED(hr))
		{
			wil::unique_hlocal_string message;
			FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, hr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (PWSTR)&message, 0, nullptr);
			std::wcout << L"Failed to stop capture\n0x" << std::hex << hr << L": " << message.get() << L"\n";
		}

		// start new audio capture
		hr = loopbackCapture.StartCaptureAsync(data->processID, visualizer);
		if (FAILED(hr))
		{
			wil::unique_hlocal_string message;
			FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, hr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (PWSTR)&message, 0, nullptr);
			std::wcout << L"Failed to start capture\n0x" << std::hex << hr << L": " << message.get() << L"\n";
		}
	}

	visualizer->options = selectedOptions;

	//set visualizer window position from customization options
	int x = pos_x_slider->GetValue();
	int y = pos_y_slider->GetValue();
	visualizer->SetPosition(wxPoint(x, y));

	//resize visualizer
	x = size_x_slider->GetValue();
	y = size_y_slider->GetValue();
	visualizer->SetSize(x, y);
	visualizer->Show(true);

	VisualizerCanvas* display_canvas = visualizer->canvas;
	wxGetApp().activateRenderLoop(true);
	Hide();
}

wxListBox* ProcessWindow::getProcessesList()
{
	return processes_list;
}

//customization input callbacks
//sets text boxes to same number as slider & vice versa
void ProcessWindow::OnSL_Pos(wxCommandEvent& event)
{
	pos_x_text->SetValue(std::to_string(pos_x_slider->GetValue()));
	pos_y_text->SetValue(std::to_string(pos_y_slider->GetValue()));
	SetPreviewPos();
}
void ProcessWindow::OnSL_Size(wxCommandEvent& event) 
{
	size_x_text->SetValue(std::to_string(size_x_slider->GetValue()));
	size_y_text->SetValue(std::to_string(size_y_slider->GetValue()));
	SetPreviewPos();
}
void ProcessWindow::OnPos(wxCommandEvent& event)
{
	int x = 0;
	pos_x_text->GetValue().ToInt(&x);
	pos_x_slider->SetValue(x);
	int y = 0;
	pos_y_text->GetValue().ToInt(&y);
	pos_y_slider->SetValue(y);
	SetPreviewPos();
}
void ProcessWindow::OnSize(wxCommandEvent& event)
{
	int x = 0;
	size_x_text->GetValue().ToInt(&x);
	size_x_slider->SetValue(x);
	int y = 0;
	size_y_text->GetValue().ToInt(&y);
	size_y_slider->SetValue(y);
	SetPreviewPos();
}

inline void ProcessWindow::SetPreviewPos()
{
	int x = pos_x_slider->GetValue();
	int y = pos_y_slider->GetValue();
	preview_window->SetPosition(wxPoint(x, y));
	int size_x = size_x_slider->GetValue();
	int size_y = size_y_slider->GetValue();
	preview_window->SetSize(wxSize(size_x, size_y));
}

void ProcessWindow::populateProcessList()
{
	wxListBox* process_list = getProcessesList();
	if (process_list)
	{
		std::vector<process_info> processes_info = getCurrentAudioProcesses(getDefaultAudioDevice());
		int len = processes_info.size();

		for (int i = 0; i < len; ++i)
		{
			process_info process_info = processes_info.at(i);

			process_list->Append(process_info.name, new ClientData(process_info.name, process_info.id));

		}
	}
}