#pragma once
#include <wx/listbox.h>
#include <wx/wx.h>

class ClientData : public wxClientData
{
public:
    int processID;
    wxString name;

    ClientData(wxString name, int processID) {
        this->name = name;
        this->processID = processID;
    }
};