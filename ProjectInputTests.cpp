//
// Created by michel on 15.03.21.
//

#include <iostream>
#include <gtest/gtest.h>
#include "HUB.h"
#include "ProjectUtils.h"
#include "ProjectImporter.h"

using namespace std;

class ProjectInputTest: public ::testing::Test {
protected:
    friend class Hub;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Hub hub_;
};


/**
Tests input.xml (happyday scenario)
*/
TEST_F(ProjectInputTest, InputHappyDay) {
    ASSERT_TRUE(DirectoryExists("../testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    string fileName = "../testInput/input.xml";

    myfile.open("../testInput/zzzError.txt");
    importResult = ProjectImporter::importProject("../testInput/input.xml", myfile, hub_);
    myfile.close();
    EXPECT_TRUE(importResult == Success);
    // nakijken van hub
    EXPECT_EQ(93000, hub_.getLevering());
    EXPECT_EQ(6, hub_.getInterval());
    EXPECT_EQ(2000, hub_.getTransport());
    EXPECT_EQ(0, hub_.getVaccins());

    //nakijken van centrums
    EXPECT_EQ("Park Spoor Oost", hub_.centra[0]->getNaam());
    EXPECT_EQ("Noordersingel 40, Antwerpen", hub_.centra[0]->getAdres());
    EXPECT_EQ(540173, hub_.centra[0]->getInwoners());
    EXPECT_EQ(7500, hub_.centra[0]->getCapaciteit());

    EXPECT_EQ("AED Studios", hub_.centra[1]->getNaam());
    EXPECT_EQ("Fabriekstraat 38, Lint", hub_.centra[1]->getAdres());
    EXPECT_EQ(76935, hub_.centra[1]->getInwoners());
    EXPECT_EQ(2000, hub_.centra[1]->getCapaciteit());

    EXPECT_EQ("De Zoerla", hub_.centra[2]->getNaam());
    EXPECT_EQ("Gevaertlaan 1, Westerlo", hub_.centra[2]->getAdres());
    EXPECT_EQ(49451, hub_.centra[2]->getInwoners());
    EXPECT_EQ(1000, hub_.centra[2]->getCapaciteit());

    EXPECT_EQ("Flanders Expo", hub_.centra[3]->getNaam());
    EXPECT_EQ("Maaltekouter 1, Sint-Denijs-Westrem", hub_.centra[3]->getAdres());
    EXPECT_EQ(257029, hub_.centra[3]->getInwoners());
    EXPECT_EQ(3000, hub_.centra[3]->getCapaciteit());
}

TEST_F(ProjectInputTest, InputLegalSimulations) {
    ASSERT_TRUE(DirectoryExists("../testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "../testInput/legalSimulations" + ToString(fileCounter) + ".xml";

    while (FileExists (fileName)) {
        myfile.open("../testInput/zzzError.txt");
        importResult = ProjectImporter::importProject(fileName.c_str(), myfile, hub_);
        myfile.close();
        EXPECT_TRUE(importResult == Success);
        EXPECT_TRUE(FileIsEmpty("../testInput/zzzError.txt"));

        fileCounter = fileCounter + 1;
        fileName = "../testInput/legalSimulations" + ToString(fileCounter) + ".xml";
    };

    EXPECT_TRUE(fileCounter == 6);
}

TEST_F(ProjectInputTest, InputXMLSyntaxErrors) {
    ASSERT_TRUE(DirectoryExists("../testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "../testInput/xmlsyntaxerror" + ToString(fileCounter) + ".xml";
    string errorfileName;

    while (FileExists (fileName)) {
        myfile.open("../testInput/zzzError.txt");
        importResult = ProjectImporter::importProject(fileName.c_str(), myfile, hub_);
        myfile.close();
        EXPECT_TRUE(importResult == ImportAborted);
        errorfileName = "../testInput/xmlsyntaxerror" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare("../testInput/zzzError.txt", errorfileName));

        fileCounter = fileCounter + 1;
        fileName = "../testInput/xmlsyntaxerror" + ToString(fileCounter) + ".xml";
    };
    EXPECT_TRUE(fileCounter == 5);
}

TEST_F(ProjectInputTest, InputIllegalSimulations) {
    ASSERT_TRUE(DirectoryExists("../testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "../testInput/illegalSimulation" + ToString(fileCounter) + ".xml";
    string errorfileName;

    while (FileExists (fileName)) {
        myfile.open("../testInput/zzzError.txt");
        importResult = ProjectImporter::importProject(fileName.c_str(), myfile, hub_);
        myfile.close();
        EXPECT_TRUE(importResult == PartialImport);
        errorfileName = "../testInput/illegalSimulation" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare("../testInput/zzzError.txt", errorfileName));

        fileCounter = fileCounter + 1;
        fileName = "../testInput/illegalSimulation" + ToString(fileCounter) + ".xml";
    };
    EXPECT_TRUE(fileCounter == 13);
}