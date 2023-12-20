/**
 * @file ViewHome.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "ViewHome.h"
#include <wx/dcbuffer.h>

/**
 * Constructor
 * @param parent Pointer to wxFrame object, the main frame for the application
 */
ViewHome::ViewHome(wxFrame* parent) :wxScrolledCanvas(parent, wxID_ANY)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewHome::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewHome::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewHome::OnLeftUp, this);
    Bind(wxEVT_LEFT_DCLICK, &ViewHome::OnLeftDoubleClick, this);
    Bind(wxEVT_MOTION, &ViewHome::OnMouseMove, this);

}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewHome::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

//    mAquarium.OnDraw(&dc);
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewHome::OnLeftDown(wxMouseEvent &event)
{

}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewHome::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewHome::OnMouseMove(wxMouseEvent &event)
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
void ViewHome::OnLeftDoubleClick(wxMouseEvent &event)
{

}