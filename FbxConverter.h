///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
class wxFbxDestPropertyGrid;
class wxFbxSourcePropertyGrid;

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class FbxConverterDialogBase
///////////////////////////////////////////////////////////////////////////////
class FbxConverterDialogBase : public wxDialog
{
	private:

	protected:
		wxFbxSourcePropertyGrid* m_fbxSourcePropertyGrid;
		wxFbxDestPropertyGrid* m_fbxDestPropertyGrid;
		wxButton* m_OpenFile;
		wxButton* m_SaveFileButton;
		wxButton* m_ExitButton;

		// Virtual event handlers, overide them in your derived class
		virtual void CloseMainDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnOpenFbxFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveFbxFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExitApp( wxCommandEvent& event ) { event.Skip(); }


	public:

		FbxConverterDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, 
								const wxString& title = wxT("Fbx Converter"), 
								const wxPoint& pos = wxDefaultPosition, 
								const wxSize& size = wxSize( 619,474 ), 
								long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		virtual ~FbxConverterDialogBase();

};

