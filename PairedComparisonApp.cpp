/**
 * @file PairedComparisonApp.cpp
 * @author Toazt
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

#include "PairedComparisonApp.h"
#include "MainFrame.h"

/**
 * Initialize the application.
 * @return True if successful
 */
bool PairedComparisonApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    // Do not remove this line...
    wxSetWorkingDirectory(L"..");

    // Get pointer to XML resource system
    auto xmlResource = wxXmlResource::Get();

    // Initialize XRC handlers
    xmlResource->InitAllHandlers();

    // Load all XRC resources from the program resources
    auto standardPaths = wxStandardPaths::Get();
    if (!wxXmlResource::Get()->LoadAllFiles(standardPaths.GetResourcesDir() + "/xrc"))
    {
        return false;
    }

    auto frame = new MainFrame(standardPaths.GetResourcesDir().ToStdWstring());
    frame->Initialize();
    frame->Show(true);

    return true;
}

/**
 * Exit the application. Time to shut down services
 * @return
 */
int PairedComparisonApp::OnExit()
{
    return wxAppBase::OnExit();
}