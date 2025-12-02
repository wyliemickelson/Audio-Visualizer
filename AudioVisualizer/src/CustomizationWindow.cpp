#include <CustomizationWindow.h>

	void CustomizationWindow::OnExit(wxCommandEvent& event) 
	{
		preview_window->Close(true);
		Close(true);
	}

	void CustomizationWindow::OnApply(wxCommandEvent& event) 
	{
		event.Skip();
	}

	//customization input callbacks
	//sets text boxes to same number as slider & vice versa
	void CustomizationWindow::OnSL_Pos(wxCommandEvent& event)
	{
		pos_x_text->SetValue(std::to_string(pos_x_slider->GetValue()));
		pos_y_text->SetValue(std::to_string(pos_y_slider->GetValue()));
		SetPreviewPos();
	}
	void CustomizationWindow::OnSL_Size(wxCommandEvent& event) 
	{
		size_x_text->SetValue(std::to_string(size_x_slider->GetValue()));
		size_y_text->SetValue(std::to_string(size_y_slider->GetValue()));
		SetPreviewPos();
	}
	void CustomizationWindow::OnPos(wxCommandEvent& event)
	{
		int x = 0;
		pos_x_text->GetValue().ToInt(&x);
		pos_x_slider->SetValue(x);
		int y = 0;
		pos_y_text->GetValue().ToInt(&y);
		pos_y_slider->SetValue(y);
		SetPreviewPos();
	}
	void CustomizationWindow::OnSize(wxCommandEvent& event)
	{
		int x = 0;
		size_x_text->GetValue().ToInt(&x);
		size_x_slider->SetValue(x);
		int y = 0;
		size_y_text->GetValue().ToInt(&y);
		size_y_slider->SetValue(y);
		SetPreviewPos();
	}

	inline void CustomizationWindow::SetPreviewPos()
	{
		int x = pos_x_slider->GetValue();
		int y = pos_y_slider->GetValue();
		preview_window->SetPosition(wxPoint(x, y));

		int size_x = size_x_slider->GetValue();
		int size_y = size_y_slider->GetValue();
		preview_window->SetSize(wxSize(size_x, size_y));

	}
