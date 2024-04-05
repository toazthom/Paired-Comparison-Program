/**
 * @file EssayManagerTest.cpp
 * @author Thomas Toaz
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

#include <EssayManager.h>
#include <Essay.h>
#include <Pair.h>

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

using namespace std;

const unsigned int RandomSeed = 1238197374;

class EssayManagerTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/comparison";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;

    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        return str;
    }

    /**
     * Test to ensure an aquarium .aqua file is empty
     */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<comp/>")));

    }

    /**
     *  Populate an Essay Manager with three essays
     */
    void PopulateThreeEssays(EssayManager *essayManager)
    {
//        essayManager->GetRandom().seed(RandomSeed);

        std::shared_ptr<Essay> essay1 = std::make_shared<Essay> ("Essay1","Filler Text for Essay1.");
        essayManager->GetEssays()->push_back(essay1);

        std::shared_ptr<Essay> essay2 = std::make_shared<Essay> ("Essay2","Filler Text for Essay2.");
        essayManager->GetEssays()->push_back(essay2);

        std::shared_ptr<Essay> essay3 = std::make_shared<Essay> ("Essay3","Filler Text for Essay3.");
        essayManager->GetEssays()->push_back(essay3);
    }


    void TestThreeEssays(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three essays
        ASSERT_TRUE(regex_search(xml, wregex(L"<comp><essay.*<essay.*<essay.*</comp>")));

        // Ensure the ids and content
        ASSERT_TRUE(regex_search(xml, wregex(L"<essay id=\"Essay1\" content=\"Filler Text for Essay1.\"/>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<essay id=\"Essay2\" content=\"Filler Text for Essay2.\"/>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<essay id=\"Essay3\" content=\"Filler Text for Essay3.\"/>")));

    }

    void TestThreeLoadedEssays(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three essays
        ASSERT_TRUE(regex_search(xml, wregex(L"<comp><essay.*<essay.*<essay.*</comp>")));

        // Ensure the ids and content
        ASSERT_TRUE(regex_search(xml, wregex(L"<essay id=\"Essay1\" content=\"Filler Text for Essay1.\"/>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<essay id=\"Essay2\" content=\"Filler Text for Essay2.\"/>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<essay id=\"Essay3\" content=\"Filler Text for Essay3.\"/>")));

    }


};

TEST(EssayMAnagerTest, ImportEssays)
{



//    EssayManager manager;
//    const std::wstring essayFile = L"resources\TestEssays.csv";
//    auto path = wxFileName::GetTempDir() + L"/Paired-Comparison-Program";


//    wxString TempPath()
//    {
//        // Create a temporary filename we can use
//        auto path = wxFileName::GetTempDir() + L"/aquarium";
//        if(!wxFileName::DirExists(path))
//        {
//            wxFileName::Mkdir(path);
//        }
//
//        return path;
//
//    }


//    auto file2 = path + L"/test2.aqua";
//    aquarium.Save(file2);


//    manager.Import(essayFile);

//    auto essays = manager.GetEssays();
//
//    ASSERT_EQ("ABCD",essays[0]->GetId());
//    ASSERT_EQ("Filler text for essay 1",essays[0]->GetContent());

}

TEST_F(EssayManagerTest, Construct){
    EssayManager manager;
}



TEST_F(EssayManagerTest, SaveLoad) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    EssayManager manager;

    //
    // First test, saving an empty comparison
    //
    auto file1 = path + L"/test1.comp";
    manager.Save(file1);


    TestEmpty(file1);

    //
    // Now populate the comparison
    //

    PopulateThreeEssays(&manager);

    auto file2 = path + L"/test2.comp";
    manager.Save(file2);

    TestThreeEssays(file2);

    //
    // Test loading
    //

    // Stimulate pair generation
    manager.CreatePairs();

    //select left on first pair
    auto currentPair = manager.GetCurrentPair();
    currentPair->GetEssay1()->SelectOver(currentPair->GetEssay2()->GetId());
    currentPair->GetEssay2()->LoseTo(currentPair->GetEssay1()->GetId());
    manager.DisplayPair();

    //select right on second pair
    currentPair = manager.GetCurrentPair();
    currentPair->GetEssay2()->SelectOver(currentPair->GetEssay1()->GetId());
    currentPair->GetEssay1()->LoseTo(currentPair->GetEssay2()->GetId());
    manager.DisplayPair();

    auto file3 = path + L"/test3.comp";
    manager.Save(file3);

    TestThreeLoadedEssays(file3);

}
//
//TEST_F(AquariumTest, clear) {
//    // Create an aquarium
//    Aquarium aquarium;
//
//    // Create a path to temporary files
//    auto path = TempPath();
//
//    //
//    // populate the aquarium and save it
//    //
//
//    PopulateThreeBetas(&aquarium);
//
//    //save the filled aquarium
//    auto file1 = path + L"/test1.aqua";
//    aquarium.Save(file1);
//
//    //
//    // Clear aquarium
//    //
//
//    aquarium.Clear();
//
//    //Save the now empty aquarium
//    aquarium.Save(file1);
//
//    TestEmpty(file1);
//
//}
//
//TEST_F(AquariumTest, Load) {
//    // Create a path to temporary files
//    auto path = TempPath();
//
//    // Create an aquarium
//    Aquarium aquarium;
//    Aquarium aquarium2;
//
//    //
//    // First test, saving an empty aquarium
//    //
//    auto file1 = path + L"/test1.aqua";
//    aquarium.Save(file1);
//
//    TestEmpty(file1);
//
//    aquarium2.Load(file1);
//    aquarium2.Save(file1);
//    TestEmpty(file1);
//
//    //
//    // Now populate the aquarium
//    //
//
//    PopulateThreeBetas(&aquarium);
//
//    auto file2 = path + L"/test2.aqua";
//    aquarium.Save(file2);
//
//    TestThreeBetas(file2);
//
//    aquarium2.Load(file2);
//    aquarium2.Save(file2);
//    TestThreeBetas(file2);
//
//    //
//    // Test all types
//    //
//    Aquarium aquarium3;
//    PopulateAllTypes(&aquarium3);
//
//    auto file3 = path + L"/test3.aqua";
//    aquarium3.Save(file3);
//
//    TestAllTypes(file3);
//
//    aquarium2.Load(file3);
//    aquarium2.Save(file3);
//    TestAllTypes(file3);
//}

