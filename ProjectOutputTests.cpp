//
// Created by michel on 16.03.21.
//

#include <iostream>
#include <gtest/gtest.h>
#include "HUB.h"
#include "ProjectUtils.h"
#include "ProjectExporter.h"

using namespace std;

class ProjectOutputTest: public ::testing::Test {
protected:
    friend class Hub;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Hub hub_;
    Centrum centrum_;

};

/**
Tests the output of the "happy day" scenario (simulation example given in assignment).
*/
TEST_F(ProjectOutputTest, OutputHappyDay) {
    ASSERT_TRUE(DirectoryExists("../testOutput"));
    //if directory doesn't exist then no need in proceeding with the test
    Hub H;
    Centrum* a;
    Centrum aa;
    a = &aa;
    Centrum* b;
    Centrum bb;
    b = &bb;
    Centrum* c;
    Centrum cc;
    c = &cc;
    Centrum* d;
    Centrum dd;
    d = &dd;

    H.setTransport(2000);
    H.setInterval(6);
    H.setLevering(93000);

    H.centra.push_back(a);
    H.centra.push_back(b);
    H.centra.push_back(c);
    H.centra.push_back(d);

    H.centra[0]->setNaam("Park Spoor Oost");
    H.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    H.centra[0]->setInwoners(540173);
    H.centra[0]->setCapaciteit(7500);
    H.centra[0]->setVaccins(0);

    H.centra[1]->setNaam("AED Studios");
    H.centra[1]->setAdres("Fabriekstraat 38, Lint");
    H.centra[1]->setInwoners(76935);
    H.centra[1]->setCapaciteit(2000);
    H.centra[1]->setVaccins(0);

    H.centra[2]->setNaam("De Zoerla");
    H.centra[2]->setAdres("Gevaertlaan 1, Westerlo");
    H.centra[2]->setInwoners(49451);
    H.centra[2]->setCapaciteit(1000);
    H.centra[2]->setVaccins(0);


    H.centra[3]->setNaam("Flanders Expo");
    H.centra[3]->setAdres("Maaltekouter 1, Sint-Denijs-Westrem");
    H.centra[3]->setInwoners(257029);
    H.centra[3]->setCapaciteit(3000);
    H.centra[3]->setVaccins(0);

    string fileName = "../testOutput/happyDayOut.txt";
    ofstream myfile;
    myfile.open("../testOutput/happyDayOutError.txt");
    std::ostream bitBucket(NULL);
    H.simuleren(3, bitBucket);
    ProjectExporter::exportProject(fileName.c_str(),myfile, H);
    myfile.close();
    string fileName2 = "../testOutput/happyDayGraphicImpression.txt";
    myfile.open("../testOutput/happyDayGraphicImpressionError.txt");
    ProjectExporter::graphic_impression(fileName2.c_str(),myfile, H);
    myfile.close();

    EXPECT_TRUE(
            FileCompare("../testOutput/happyDayExpectedOut.txt", "../testOutput/happyDayOut.txt"));
    EXPECT_TRUE(
            FileCompare("../testOutput/happyDayGraphicImpressionExpected.txt", "../testOutput/happyDayGraphicImpression.txt"));
}

TEST_F(ProjectOutputTest, OutputOneCentrum) {
    ASSERT_TRUE(DirectoryExists("../testOutput"));
    //if directory doesn't exist then no need in proceeding with the test
    Hub H;
    Centrum* a;
    Centrum aa;
    a = &aa;

    H.setTransport(2000);
    H.setInterval(6);
    H.setLevering(93000);

    H.centra.push_back(a);
    H.centra[0]->setNaam("Park Spoor Oost");
    H.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    H.centra[0]->setInwoners(540173);
    H.centra[0]->setCapaciteit(7500);
    H.centra[0]->setVaccins(0);

    string fileName = "../testOutput/OutputOneCentrum.txt";
    ofstream myfile;
    myfile.open("../testOutput/OutputOneCentrumError.txt");
    std::ostream bitBucket(NULL);
    H.simuleren(6, bitBucket);
    ProjectExporter::exportProject(fileName.c_str(),myfile, H);
    myfile.close();
    EXPECT_TRUE(
            FileCompare("../testOutput/OutputOneCentrumExpected.txt", "../testOutput/OutputOneCentrum.txt"));
}

TEST_F(ProjectOutputTest, GraphicImpression){
    ASSERT_TRUE(DirectoryExists("../testOutput"));
    //if directory doesn't exist then no need in proceeding with the test
    Hub H;
    Centrum* a;
    Centrum aa;
    a = &aa;

    H.setTransport(2000);
    H.setInterval(6);
    H.setLevering(93000);

    H.centra.push_back(a);
    H.centra[0]->setNaam("Park Spoor Oost");
    H.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    H.centra[0]->setInwoners(540173);
    H.centra[0]->setCapaciteit(7500);
    H.centra[0]->setVaccins(0);

    string fileName = "../testOutput/OutputGraphicImpression.txt";
    ofstream myfile;
    myfile.open("../testOutput/OutputGraphicImpressionError.txt");
    std::ostream bitBucket(NULL);
    H.simuleren(6, bitBucket);
    ProjectExporter::graphic_impression(fileName.c_str(),myfile, H);
    myfile.close();
    EXPECT_TRUE(
            FileCompare("../testOutput/OutputGraphicImpressionExpected.txt", "../testOutput/OutputGraphicImpression.txt"));

}