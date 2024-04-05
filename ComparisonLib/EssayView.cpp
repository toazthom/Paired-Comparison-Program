/**
 * @file EssayView.cpp
 * @author Thomas Toaz
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/stdpaths.h>
#include <wx/xrc/xmlres.h>

#include "EssayView.h"
#include "Essay.h"

#include <sstream>


/// A scaling factor, converts mouse motion to rotation in radians
const double RotationScaling = 0.02;

/**
 * Constructor
 * @param parent Pointer to wxFrame object, the main frame for the application
 */
EssayView::EssayView(wxFrame* parent) :wxScrolledCanvas(parent, wxID_ANY,wxPoint(100,100))
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &EssayView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &EssayView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &EssayView::OnLeftUp, this);
    Bind(wxEVT_LEFT_DCLICK, &EssayView::OnLeftDoubleClick, this);
    Bind(wxEVT_MOTION, &EssayView::OnMouseMove, this);

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void EssayView::OnPaint(wxPaintEvent& event)
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


    //Process text for line returns
    std::stringstream ss;
    std::string tempText;
    if(mFinished)
    {
        tempText = "Comparison Completed!";
    }
    else if(mCurrentEssay != nullptr)
    {
        tempText = mCurrentEssay->GetContent();
    }
    else
    {
        tempText = "Please Import Essays to Begin";
    }

    while (tempText.size()>70)
    {
        ss << tempText.substr(0, 70) << '\n';
        tempText.erase(0, 70);
    }
    // Add any parts of the line that were <60 chars
    ss << tempText;


    // Draw the text with automatic wrapping
    dc.DrawText(ss.str(), x, y);



    // Create a graphics context
//    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

//    // Draw essay text
//    graphics->PushState();
//
//    // Set text color and font size
//    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
//    graphics->SetFont(font, wxColor(0, 0, 0));  // Black text color
//    graphics->DrawText(mDisplayedText,10,10);
//
//    graphics->PushState();
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void EssayView::OnLeftDown(wxMouseEvent &event)
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
void EssayView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void EssayView::OnMouseMove(wxMouseEvent &event)
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
void EssayView::OnLeftDoubleClick(wxMouseEvent &event)
{

}

/**
 * Set the text that will be displayed within the scroll window
 * @param text the essay text being displayed
 */
void EssayView::SetEssay(std::shared_ptr<Essay> essay)
{
    mCurrentEssay = essay;
    Refresh();
}




