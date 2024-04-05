/**
 * @file Essay.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Essay.h"

/**
 * Constructor
 * @param name
 */
Essay::Essay(const std::string &id, const std::string &content) : mId(id), mContent(content)
{
}

/**
 * Select essay and update its data
 * @param loserId the id of the losing essay
 */
void Essay::SelectOver(std::string loserId)
{
    mChosenOver.push_back(loserId);
}

/**
 * Update essay's data after losing/not being chosen
 * @param winnerId
 */
void Essay::LoseTo(std::string winnerId)
{
    mLostTo.push_back((winnerId));
}

/**
 * Save this essay to an XML node
 * @param node The parent node we are going to be a child of
 * @return wXmlNode that we saved the item into
 */
wxXmlNode *Essay::XmlSave(wxXmlNode *node)
{
    auto essayNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"essay");
    node->AddChild(essayNode);

    // Add essay personal info
    essayNode->AddAttribute(L"id", wxString(mId));
    essayNode->AddAttribute(L"content", wxString(mContent));


    // Add chosen over essay list IF data is within vector
    if(!mChosenOver.empty())
    {
        for(auto essay : mChosenOver)
        {
            auto chosenOverNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"chosenOver");
            essayNode->AddChild(chosenOverNode);
            chosenOverNode->AddAttribute(L"chosenOverId", wxString(essay));
        }
    }

    // Add chosen instead of essay list IF data is within vector
    if(!mLostTo.empty())
    {
        for(auto essay : mLostTo)
        {
            auto lostToNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"lostTo");
            essayNode->AddChild(lostToNode);
            lostToNode->AddAttribute(L"lostToId", wxString(essay));
        }
    }

    return essayNode;
}
