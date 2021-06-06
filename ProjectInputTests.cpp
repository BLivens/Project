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
    friend class Simulatie;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Simulatie simulatie_;
};


/**
Tests input.xml (happyday scenario)
*/
TEST_F(ProjectInputTest, InputHappyDay) {
    ASSERT_TRUE(DirectoryExists("../testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    string fileName = "../testInput/input_2hubs_voorbeeld.xml";

    myfile.open("../testInput/zzzError.txt");
    importResult = ProjectImporter::importProject("../testInput/input_2hubs_voorbeeld.xml", myfile, simulatie_);
    myfile.close();
    EXPECT_TRUE(importResult == Success);
    // nakijken van hubs
    EXPECT_EQ("Pfizer", simulatie_.hubs[0]->vaccins[0]->getType());
    EXPECT_EQ(93000, simulatie_.hubs[0]->vaccins[0]->getLevering());
    EXPECT_EQ(6, simulatie_.hubs[0]->vaccins[0]->getInterval());
    EXPECT_EQ(2000, simulatie_.hubs[0]->vaccins[0]->getTransport());
    EXPECT_EQ(21, simulatie_.hubs[0]->vaccins[0]->getHernieuwing());
    EXPECT_EQ(-70, simulatie_.hubs[0]->vaccins[0]->getTemperatuur());

    EXPECT_EQ("Moderna", simulatie_.hubs[0]->vaccins[1]->getType());
    EXPECT_EQ(46000, simulatie_.hubs[0]->vaccins[1]->getLevering());
    EXPECT_EQ(13, simulatie_.hubs[0]->vaccins[1]->getInterval());
    EXPECT_EQ(1000, simulatie_.hubs[0]->vaccins[1]->getTransport());
    EXPECT_EQ(28, simulatie_.hubs[0]->vaccins[1]->getHernieuwing());
    EXPECT_EQ(-20, simulatie_.hubs[0]->vaccins[1]->getTemperatuur());

    EXPECT_EQ("Moderna", simulatie_.hubs[1]->vaccins[0]->getType());
    EXPECT_EQ(46000, simulatie_.hubs[1]->vaccins[0]->getLevering());
    EXPECT_EQ(13, simulatie_.hubs[1]->vaccins[0]->getInterval());
    EXPECT_EQ(1000, simulatie_.hubs[1]->vaccins[0]->getTransport());
    EXPECT_EQ(28, simulatie_.hubs[1]->vaccins[0]->getHernieuwing());
    EXPECT_EQ(-20, simulatie_.hubs[1]->vaccins[0]->getTemperatuur());

    EXPECT_EQ("AstraZeneca", simulatie_.hubs[1]->vaccins[1]->getType());
    EXPECT_EQ(67000, simulatie_.hubs[1]->vaccins[1]->getLevering());
    EXPECT_EQ(4, simulatie_.hubs[1]->vaccins[1]->getInterval());
    EXPECT_EQ(1500, simulatie_.hubs[1]->vaccins[1]->getTransport());
    EXPECT_EQ(28, simulatie_.hubs[1]->vaccins[1]->getHernieuwing());
    EXPECT_EQ(5, simulatie_.hubs[1]->vaccins[1]->getTemperatuur());


    //nakijken van centrums
    EXPECT_EQ("Park Spoor Oost", (*simulatie_.hubs[0]->centra[0])->getNaam());
    EXPECT_EQ("Noordersingel 40, Antwerpen", (*simulatie_.hubs[0]->centra[0])->getAdres());
    EXPECT_EQ(540173, (*simulatie_.hubs[0]->centra[0])->getInwoners());
    EXPECT_EQ(7500, (*simulatie_.hubs[0]->centra[0])->getCapaciteit());

    EXPECT_EQ("Park Spoor Oost", (*simulatie_.hubs[1]->centra[0])->getNaam());
    EXPECT_EQ("Noordersingel 40, Antwerpen", (*simulatie_.hubs[1]->centra[0])->getAdres());
    EXPECT_EQ(540173, (*simulatie_.hubs[1]->centra[0])->getInwoners());
    EXPECT_EQ(7500, (*simulatie_.hubs[1]->centra[0])->getCapaciteit());

    EXPECT_EQ("AED Studios", (*simulatie_.hubs[1]->centra[1])->getNaam());
    EXPECT_EQ("Fabriekstraat 38, Lint", (*simulatie_.hubs[1]->centra[1])->getAdres());
    EXPECT_EQ(76935, (*simulatie_.hubs[1]->centra[1])->getInwoners());
    EXPECT_EQ(2000, (*simulatie_.hubs[1]->centra[1])->getCapaciteit());

    EXPECT_EQ("De Zoerla", (*simulatie_.hubs[1]->centra[2])->getNaam());
    EXPECT_EQ("Gevaertlaan 1, Westerlo", (*simulatie_.hubs[1]->centra[2])->getAdres());
    EXPECT_EQ(49451, (*simulatie_.hubs[1]->centra[2])->getInwoners());
    EXPECT_EQ(1000, (*simulatie_.hubs[1]->centra[2])->getCapaciteit());

    EXPECT_EQ("Flanders Expo", (*simulatie_.hubs[1]->centra[3])->getNaam());
    EXPECT_EQ("Maaltekouter 1, Sint-Denijs-Westrem", (*simulatie_.hubs[1]->centra[3])->getAdres());
    EXPECT_EQ(257029, (*simulatie_.hubs[1]->centra[3])->getInwoners());
    EXPECT_EQ(3000, (*simulatie_.hubs[1]->centra[3])->getCapaciteit());
}

TEST_F(ProjectInputTest, InputLegalSimulations) {
    ASSERT_TRUE(DirectoryExists("../testInput"));

    ofstream myfile;
    SuccessEnum importResult;
    int fileCounter = 1;
    string fileName = "../testInput/legalSimulations" + ToString(fileCounter) + ".xml";


    while (FileExists (fileName)) {
        myfile.open("../testInput/zzzError.txt");
        Simulatie simulatie;
        importResult = ProjectImporter::importProject(fileName.c_str(), myfile, simulatie);
        myfile.close();
        EXPECT_TRUE(importResult == Success);
        EXPECT_TRUE(FileIsEmpty("../testInput/zzzError.txt"));

        fileCounter = fileCounter + 1;
        fileName = "../testInput/legalSimulations" + ToString(fileCounter) + ".xml";
    };

    EXPECT_TRUE(fileCounter == 9);
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
        importResult = ProjectImporter::importProject(fileName.c_str(), myfile, simulatie_);
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
        Simulatie simulatie;
        importResult = ProjectImporter::importProject(fileName.c_str(), myfile, simulatie);
        myfile.close();
        EXPECT_TRUE(importResult == PartialImport);
        errorfileName = "../testInput/illegalSimulation" + ToString(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare("../testInput/zzzError.txt", errorfileName));

        fileCounter = fileCounter + 1;
        fileName = "../testInput/illegalSimulation" + ToString(fileCounter) + ".xml";
    };
    EXPECT_TRUE(fileCounter == 16);
}