/**
 * @file Pair.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Pair.h"
#include "Essay.h"

/**
 * constructor
 * @param essay1
 * @param essay2
 */
Pair::Pair(std::shared_ptr<Essay> &essay1, std::shared_ptr<Essay> &essay2) : mEssay1(essay1), mEssay2(essay2)
{

}

/**
 * Save this pair to an XML node
 * @param node The parent node we are going to be a child of
 * @return wXmlNode that we saved the item into
 */
wxXmlNode *Pair::XmlSave(wxXmlNode *node)
{
    auto pairNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"pair");
    node->AddChild(pairNode);

    // Add pair essay ids
    pairNode ->AddAttribute(L"essayId1", wxString(mEssay1->GetId()));
    pairNode ->AddAttribute(L"essayId2", wxString(mEssay2->GetId()));


    return pairNode;
}
