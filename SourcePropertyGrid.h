

#pragma once

#include <wx/propgrid/propgrid.h>

class wxFbxSourcePropertyGrid : public wxPropertyGrid
{
public:
 // The default constructor. The styles to be used are styles valid for
    // the wxWindow.
    wxFbxSourcePropertyGrid( wxWindow *parent, wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxPG_DEFAULT_STYLE,
                    const wxString& name = wxPropertyGridNameStr ) : wxPropertyGrid(parent, id, pos, size, style)
					{};

    // Destructor
    virtual ~wxFbxSourcePropertyGrid()
	{};
};
