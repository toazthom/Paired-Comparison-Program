/**
 * @file EssayManager.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "EssayManager.h"
#include "Essay.h"
#include "Pair.h"
#include "EssayView.h"
#include "MainFrame.h"

#include <fstream>
#include <vector>
#include <sstream>

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

//#include <Rcpp.h>

/**
 * Constructor
 */
EssayManager::EssayManager()
{

}

/**
 * Create all the possible pairings of essays for comparison
 */
void EssayManager::CreatePairs()
{

    //Create essay pairs removing the first essay to avoid repeats
    for(int i = 0; i<mEssays.size();i++)
    {
        for(int j = i +1; j<mEssays.size();j++)
        {
            std::shared_ptr<Pair> pair = std::make_shared<Pair>(mEssays[i],mEssays[j]);
            mIncompletedPairs.push_back(pair);
        }
    }

    // Display an initial par
    DisplayPair();
}

/**
 * save comparison to a file
 * @param filename file to save to
 */
void EssayManager::Save(const wxString& filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"comp");
    xmlDoc.SetRoot(root);

    //Iterate over general essay list and save them
    for(auto essay : mEssays)
    {
        essay->XmlSave(root);
    }

    // Save incompleted pairs if any
    if(!mIncompletedPairs.empty())
    {
        auto incompletedPairNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"incompletedPair");
        root->AddChild(incompletedPairNode);
        for(auto pair: mIncompletedPairs)
        {
            pair->XmlSave(incompletedPairNode);
        }
    }


    // Save completed pairs if any
    if(!mCompletedPairs.empty())
    {
        auto completedPairNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"completedPair");
        root->AddChild(completedPairNode);
        for(auto pair: mCompletedPairs)
        {
            pair->XmlSave(completedPairNode);
        }
    }

    // Save current pair that is being displayed if there is one
    if(mCurrentPair != nullptr)
    {
        auto currentPairNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"currentPair");
        root->AddChild(currentPairNode);
        if(mCurrentPair)
        {
            mCurrentPair->XmlSave(currentPairNode);
        }
    }

    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }

}

/**
* Load a comparison from a file
* @param filename file to load from
*/
void EssayManager::Load(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Comparison file");
        return;
    }

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"essay")
        {
            XmlEssay(child);
        }
        else if(name == L"incompletedPair")
        {
            XmlIncompletedPair(child);
        }
        else if(name == L"completedPair")
        {
            XmlCompletedPair(child);
        }
        else if(name == L"currentPair")
        {
            XmlCurrentPair(child);
        }
    }
}

/**
 * Load in essays from a csv file
 * @param filename csv file to load from
 */
void EssayManager::Import(const wxString &filename)
{
    // Convert wxString to std::string
    std::string filenameStr = filename.ToStdString();

    // File pointer
    std::ifstream fin(filenameStr);

    if (!fin.is_open()) {
        wxMessageBox(L"Unable to load CSV file");
        return;
    }

    // Read the Data from the file
    std::string id, content, temp;

    while (getline(fin, temp))
    {
        // Skip empty lines
        if (temp.empty()) {
            continue;
        }

        // Use a stringstream to parse the line
        std::stringstream s(temp);

        // Read the first column data of a row
        if (getline(s, id, ','))
        {
            // Read the second column data of a row
            if (getline(s, content))
            {
                //Add essay to manager
                std::shared_ptr<Essay> essay = std::make_shared<Essay> (id,content);
                mEssays.push_back(essay);
            }
            else
            {
                std::cout << "Error: Essay is missing content." << std::endl;
            }
        }
    }

    CreatePairs();

}

/**
 * Link the essay manager to the mainframe
 * @param mainframe
 */
void EssayManager::SetMainFrame(MainFrame *mainframe)
{
    mMainFrame = mainframe;
}

/**
 * Display a pair for comparison
 */
void EssayManager::DisplayPair()
{
    // Mark any current pair being displayed as complete
    if(mCurrentPair != nullptr)
    {
        mCompletedPairs.push_back(mCurrentPair);
        mCurrentPair = nullptr;
    }

    //Randomize which pair is selected
    if(mIncompletedPairs.size() > 0)
    {
        int pairIndex = rand() % (mIncompletedPairs.size());
        mCurrentPair = mIncompletedPairs[pairIndex];
    }
    else
    {
        // Stop the function after all pairs have been displayed
        mMainFrame->EndComparison();
        mMainFrame->GetEssayView1()->SetEssay(nullptr);
        mMainFrame->GetEssayView2()->SetEssay(nullptr);
        return;
    }

    //Remove pair from incompleted pair list
    auto loc = find(std::begin(mIncompletedPairs), std::end(mIncompletedPairs), mCurrentPair);

    if (loc != std::end(mIncompletedPairs))
    {
        mIncompletedPairs.erase(loc);
    }

    //Display the pair of essays

    //Randomize which essay is displayed on which side
    int firstDisplayed = rand() % 2;

    if(firstDisplayed == 0)
    {
        mMainFrame->GetEssayView1()->SetEssay(mCurrentPair->GetEssay1());
        mMainFrame->GetEssayView2()->SetEssay(mCurrentPair->GetEssay2());
    }
    else
    {
        mMainFrame->GetEssayView1()->SetEssay(mCurrentPair->GetEssay2());
        mMainFrame->GetEssayView2()->SetEssay(mCurrentPair->GetEssay1());
    }
}

/**
 * Generate a string listing each essay(ID) and how many times it was chosen
 * @return string of all essays and how many times they were chosen
 */
std::string EssayManager::ListResults()
{
    std::stringstream ss;

    ss<<"Essay ID        Times Selected"<<'\n'<<'\n';

    for(auto essay : mEssays)
    {
        ss<<essay->GetId()<<":                     "<<essay->GetSelectedOver().size()<<'\n';
    }

    return ss.str();
}

/**
 * Clear the comparison data.
 *
 * Deletes all known items in the aquarium.
 */
void EssayManager::Clear()
{
    mCurrentPair = nullptr;
    mEssays.clear();
    mIncompletedPairs.clear();
    mCompletedPairs.clear();

}

/**
 * Handle a node of type essay.
 * @param node XML node
 */
void EssayManager::XmlEssay(wxXmlNode *node)
{
    // A pointer for the item we are loading
    std::string id = std::string(node->GetAttribute(L"id"));
    std::string content = std::string(node->GetAttribute(L"content"));
    std::shared_ptr<Essay> essay = std::make_shared<Essay> (id,content);

    // Load essay comparison data (if any)
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"chosenOver")
        {
            essay->SelectOver(std::string(child->GetAttribute(L"chosenOverId")));
        }
        else if(name == L"lostTo")
        {
            essay->LoseTo(std::string(child->GetAttribute(L"lostToId")));
        }
    }


    mEssays.push_back(essay);
}

/**
 * Handle a node of type incompleted pair.
 * @param node XML node
 */
void EssayManager::XmlIncompletedPair(wxXmlNode *node)
{
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        // A pointer for the pair we are loading
        std::string id1 = std::string(child->GetAttribute(L"essayId1"));
        std::string id2 = std::string(child->GetAttribute(L"essayId2"));
        std::shared_ptr<Essay> essay1 = nullptr;
        std::shared_ptr<Essay> essay2 = nullptr;

        for(auto essay: mEssays)
        {
            if(essay->GetId() == id1)
            {
                essay1 = essay;
            }
            else if(essay->GetId() == id2)
            {
                essay2 = essay;
            }
        }

        std::shared_ptr<Pair> pair = std::make_shared<Pair> (essay1,essay2);
        mIncompletedPairs.push_back(pair);

    }

}

/**
 * Handle a node of type completed pair.
 * @param node XML node
 */
void EssayManager::XmlCompletedPair(wxXmlNode *node)
{
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        // A pointer for the item we are loading
        std::string id1 = std::string(child->GetAttribute(L"essayId1"));
        std::string id2 = std::string(child->GetAttribute(L"essayId2"));
        std::shared_ptr<Essay> essay1 = nullptr;
        std::shared_ptr<Essay> essay2 = nullptr;

        for(auto essay : mEssays)
        {
            if(essay->GetId() == id1)
            {
                essay1 = essay;
            }
            else if(essay->GetId() == id2)
            {
                essay2 = essay;
            }
        }

        std::shared_ptr<Pair> pair = std::make_shared<Pair>(essay1, essay2);
        mCompletedPairs.push_back(pair);
    }
}

/**
 * Handle a node of type current pair.
 * @param node XML node
 */
void EssayManager::XmlCurrentPair(wxXmlNode *node)
{

    auto child = node->GetChildren();

    std::string id1 = std::string(child->GetAttribute(L"essayId1"));
    std::string id2 = std::string(child->GetAttribute(L"essayId2"));
    std::shared_ptr<Essay> essay1 = nullptr;
    std::shared_ptr<Essay> essay2 = nullptr;

    for(auto essay : mEssays)
    {
        if(essay->GetId() == id1)
        {
            essay1 = essay;
        }
        else if(essay->GetId() == id2)
        {
            essay2 = essay;
        }
    }

    std::shared_ptr<Pair> pair = std::make_shared<Pair>(essay1, essay2);
    mCurrentPair = pair;

    // Display the pair
    int firstDisplayed = rand() % 2;

    if(firstDisplayed == 0)
    {
        mMainFrame->GetEssayView1()->SetEssay(mCurrentPair->GetEssay1());
        mMainFrame->GetEssayView2()->SetEssay(mCurrentPair->GetEssay2());
    }
    else
    {
        mMainFrame->GetEssayView1()->SetEssay(mCurrentPair->GetEssay2());
        mMainFrame->GetEssayView2()->SetEssay(mCurrentPair->GetEssay1());
    }

}

