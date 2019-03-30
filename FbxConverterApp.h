
#pragma once

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/apptrait.h>


// Custom application traits class which we use to override the default log
// target creation
class FbxConverterAppTraits : public wxGUIAppTraits
{
public:
    virtual wxLog *CreateLogTarget() wxOVERRIDE;
};

// Define a new application type
class FbxConverterApp: public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
	virtual int OnExit() wxOVERRIDE;
protected:
    virtual wxAppTraits *CreateTraits() wxOVERRIDE { return new FbxConverterAppTraits; }


};


wxDECLARE_APP(FbxConverterApp);