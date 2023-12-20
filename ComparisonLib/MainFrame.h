/**
 * @file MainFrame.h
 * @author Thomas Toaz
 *
 * The top-level (main) frame of the application
 */

#ifndef PAIRED_COMPARISON_PROGRAM_COMPARISONLIB_MAINFRAME_H
#define PAIRED_COMPARISON_PROGRAM_COMPARISONLIB_MAINFRAME_H

class ViewHome;
class ViewComparison;
class viewAnalysis;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// View class for our home window
    ViewHome *mViewHome;

    /// View class for the timeline
    ViewComparison *mViewComparison;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent&);
    void OnClose(wxCloseEvent &event);

    /// The resources directory to use
    std::wstring mResourcesDir;

public:
    MainFrame(std::wstring resourcesDir);

    void Initialize();
};

#endif //PAIRED_COMPARISON_PROGRAM_COMPARISONLIB_MAINFRAME_H
