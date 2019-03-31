
#pragma once

#include <fbxsdk.h>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include "FbxConverter.h"

// const char* lFileTypes[] =
// {
//     "_dae.dae",            "Collada DAE (*.dae)",
//     "_fbx7binary.fbx", "FBX binary (*.fbx)",
//     "_fbx7ascii.fbx",  "FBX ascii (*.fbx)",
//     "_fbx6binary.fbx", "FBX 6.0 binary (*.fbx)",
//     "_fbx6ascii.fbx",  "FBX 6.0 ascii (*.fbx)",
//     "_obj.obj",            "Alias OBJ (*.obj)",
//     "_dxf.dxf",            "AutoCAD DXF (*.dxf)"
// };

extern FbxManager *fbxManager;

#ifdef IOS_REF
#undef IOS_REF
#define IOS_REF (*(fbxManager->GetIOSettings()))
#endif

class FbxConverterDialog : public FbxConverterDialogBase
{
	FbxScene *mainScene;

  protected:
	// Virtual event handlers, overide them in your derived class
	virtual void CloseMainDialog(wxCloseEvent &event) wxOVERRIDE
	{
		event.Skip();
	}

	virtual void OnOpenFbxFile(wxCommandEvent &event) wxOVERRIDE;
	
	virtual void OnSaveFbxFile(wxCommandEvent &event) wxOVERRIDE;
	
	virtual void OnExitApp(wxCommandEvent &event)
	{
		Close();
		event.Skip();
	}

  public:
	FbxConverterDialog(wxWindow *parent, wxWindowID id = wxID_ANY,
					   const wxString &title = wxT("Fbx Converter"),
					   const wxPoint &pos = wxDefaultPosition,
					   const wxSize &size = wxSize(619, 474),
					   long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
		: mainScene(nullptr),
		  FbxConverterDialogBase(parent, id, title, pos, size, style){};
	virtual ~FbxConverterDialog()
	{
		if (mainScene != nullptr)
		{
			mainScene->Destroy();
		}
	};
};