/**
 * @file AnalysisView.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "AnalysisView.h"
#include "EssayManager.h"

#include <sstream>

#include <wx/dcbuffer.h>
#include <wx/stdpaths.h>
#include <wx/xrc/xmlres.h>

/**
 * Constructor
 * @param parent Pointer to wxFrame object, the main frame for the application
 */
AnalysisView::AnalysisView(wxFrame* parent, std::shared_ptr<EssayManager> essayManager) :wxScrolledCanvas(parent, wxID_ANY,wxPoint(100,100)),
mEssayManager(essayManager)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &AnalysisView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &AnalysisView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AnalysisView::OnLeftUp, this);
    Bind(wxEVT_LEFT_DCLICK, &AnalysisView::OnLeftDoubleClick, this);
    Bind(wxEVT_MOTION, &AnalysisView::OnMouseMove, this);

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AnalysisView::OnPaint(wxPaintEvent& event)
{
    auto size = wxSize(100,100);
    SetVirtualSize(size.GetWidth(), size.GetHeight());


    SetScrollRate(1, 1);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Set text color and font size
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc.SetFont(font);
    dc.SetTextForeground(*wxBLACK);  // Black text color

    // Set the position to start drawing
    wxCoord x = 10;
    wxCoord y = 10;

    // Maximum width for text wrapping
    wxCoord maxWidth = GetVirtualSize().GetWidth() - 20;  // Adjust as needed



    // Display essays with their selection scores
    dc.DrawText(mEssayManager->ListResults(), x, y);

}

/**
 * Handle the left mouse button down event
 * @param event
 */
void AnalysisView::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());
    mLastMouse = click;

    //
    // Did we hit anything?
    //
}

/**
* Handle the left mouse button up event
* @param event
*/
void AnalysisView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void AnalysisView::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    wxPoint newMouse(click.x, click.y);
    wxPoint delta = newMouse - mLastMouse;
    mLastMouse = newMouse;

}

/**
 * Handle the left mouse button double-click event
 * @param event
 */
void AnalysisView::OnLeftDoubleClick(wxMouseEvent &event)
{

}
