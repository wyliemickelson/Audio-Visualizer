#include <ProcessWindow.h>
#include <ClientData.h>
#include <VisualizerWindow.h>
#include <CustomizationWindow.h>
#include <LoopbackCapture.h>

static boolean is_rendering = true;

void ProcessWindow::OnExit(wxCommandEvent& event)
{
	is_rendering = false;
	preview_window->Close(true);
	Close(true);
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

	preview_window->Close(true);
	ClientData* data = NULL;
	data = static_cast<ClientData*>(listBox->GetClientObject(selected));

	std::cout << std::endl << "Selected index: " << selected << ", Name: " << data->name << ", ProcessID: " << data->processID << std::endl;
    
    Hide();

    // Create and open Visualizer Window
    VisualizerWindow* visualizer = new VisualizerWindow(NULL);

    // start audio capture on selected process
    CLoopbackCapture loopbackCapture;

    HRESULT hr = loopbackCapture.StartCaptureAsync(data->processID, visualizer);
    if (FAILED(hr))
    {
        wil::unique_hlocal_string message;
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (PWSTR)&message, 0, nullptr);
        std::wcout << L"Failed to start capture\n0x" << std::hex << hr << L": " << message.get() << L"\n";
    }
    else
    {
		wxGLAttributes display_attributes;
		display_attributes.PlatformDefaults();

		int x = pos_x_slider->GetValue();
		int y = pos_y_slider->GetValue();
		visualizer->SetPosition(wxPoint(x, y));
		x = size_x_slider->GetValue();
		y = size_y_slider->GetValue();
		visualizer->SetSize(x, y);
		visualizer->Show(true);

        VisualizerCanvas* display_canvas = visualizer->canvas;

        while (is_rendering) 
		{
            // run until program is terminated
            //FreqData f_data;
            //f_data.color = (0.7f, 0.0f, 0.0f, 1.0f);
            //f_data.stereo_pos = (0.0f);
            //f_data.size = (1.0f);
            //display_canvas;
            display_canvas->Render();
			wxYield();
        }

        loopbackCapture.StopCaptureAsync();
  
        Close(true);
    }

}

wxListBox* ProcessWindow::getProcessesList()
{
	return processes_list;
}

void ProcessWindow::OnReset(wxCommandEvent& event) 
{
	event.Skip();
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