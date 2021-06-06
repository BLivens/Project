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

    Simulatie simulatie_;

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

    Vaccin* vac;
    Vaccin pvac;
    vac = &pvac;
    vac->setType("Pfizer");
    vac->setLevering(93000);
    vac->setInterval(6);
    vac->setTransport(2000);
    vac->setHernieuwing(21);
    vac->setTemperatuur(-70);
    H.vaccins.push_back(vac);

    Vaccin* vac2;
    Vaccin pvac2;
    vac2 = &pvac2;
    vac2->setType("Moderna");
    vac2->setLevering(46000);
    vac2->setInterval(13);
    vac2->setTransport(1000);
    vac2->setHernieuwing(28);
    vac2->setTemperatuur(-20);
    H.vaccins.push_back(vac2);

    Vaccin* vac3;
    Vaccin pvac3;
    vac3 = &pvac3;
    vac3->setType("AstraZeneca");
    vac3->setLevering(67000);
    vac3->setInterval(4);
    vac3->setTransport(1500);
    vac3->setHernieuwing(28);
    vac3->setTemperatuur(5);
    H.vaccins.push_back(vac3);


    simulatie_.centra.push_back(a);
    simulatie_.centra.push_back(b);
    simulatie_.centra.push_back(c);
    simulatie_.centra.push_back(d);
    Hub* p = &H;
    simulatie_.hubs.push_back(p);

    simulatie_.centra[0]->setNaam("Park Spoor Oost");
    simulatie_.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    simulatie_.centra[0]->setInwoners(540173);
    simulatie_.centra[0]->setCapaciteit(7500);

    Vaccin* vac4;
    Vaccin pvac4;
    vac4 = &pvac4;
    vac4->setType("Pfizer");
    vac4->setLevering(93000);
    vac4->setInterval(6);
    vac4->setTransport(2000);
    vac4->setHernieuwing(21);
    vac4->setTemperatuur(-70);

    Vaccin* vac5;
    Vaccin pvac5;
    vac5 = &pvac5;
    vac5->setType("Moderna");
    vac5->setLevering(46000);
    vac5->setInterval(13);
    vac5->setTransport(1000);
    vac5->setHernieuwing(28);
    vac5->setTemperatuur(-20);

    Vaccin* vac6;
    Vaccin pvac6;
    vac6 = &pvac6;
    vac6->setType("AstraZeneca");
    vac6->setLevering(67000);
    vac6->setInterval(4);
    vac6->setTransport(1500);
    vac6->setHernieuwing(28);
    vac6->setTemperatuur(5);

    simulatie_.centra[0]->vaccins.push_back(vac4);
    simulatie_.centra[0]->vaccins.push_back(vac5);
    simulatie_.centra[0]->vaccins.push_back(vac6);

    simulatie_.centra[1]->setNaam("AED Studios");
    simulatie_.centra[1]->setAdres("Fabriekstraat 38, Lint");
    simulatie_.centra[1]->setInwoners(76935);
    simulatie_.centra[1]->setCapaciteit(2000);

    Vaccin* vac7;
    Vaccin pvac7;
    vac7 = &pvac7;
    vac7->setType("Pfizer");
    vac7->setLevering(93000);
    vac7->setInterval(6);
    vac7->setTransport(2000);
    vac7->setHernieuwing(21);
    vac7->setTemperatuur(-70);

    Vaccin* vac8;
    Vaccin pvac8;
    vac8 = &pvac8;
    vac8->setType("Moderna");
    vac8->setLevering(46000);
    vac8->setInterval(13);
    vac8->setTransport(1000);
    vac8->setHernieuwing(28);
    vac8->setTemperatuur(-20);


    Vaccin* vac9;
    Vaccin pvac9;
    vac9 = &pvac9;
    vac9->setType("AstraZeneca");
    vac9->setLevering(67000);
    vac9->setInterval(4);
    vac9->setTransport(1500);
    vac9->setHernieuwing(28);
    vac9->setTemperatuur(5);

    simulatie_.centra[1]->vaccins.push_back(vac7);
    simulatie_.centra[1]->vaccins.push_back(vac8);
    simulatie_.centra[1]->vaccins.push_back(vac9);

    simulatie_.centra[2]->setNaam("De Zoerla");
    simulatie_.centra[2]->setAdres("Gevaertlaan 1, Westerlo");
    simulatie_.centra[2]->setInwoners(49451);
    simulatie_.centra[2]->setCapaciteit(1000);

    Vaccin* vac10;
    Vaccin pvac10;
    vac10 = &pvac10;
    vac10->setType("Pfizer");
    vac10->setLevering(93000);
    vac10->setInterval(6);
    vac10->setTransport(2000);
    vac10->setHernieuwing(21);
    vac10->setTemperatuur(-70);

    Vaccin* vac11;
    Vaccin pvac11;
    vac11 = &pvac11;
    vac11->setType("Moderna");
    vac11->setLevering(46000);
    vac11->setInterval(13);
    vac11->setTransport(1000);
    vac11->setHernieuwing(28);
    vac11->setTemperatuur(-20);

    Vaccin* vac12;
    Vaccin pvac12;
    vac12 = &pvac12;
    vac12->setType("AstraZeneca");
    vac12->setLevering(67000);
    vac12->setInterval(4);
    vac12->setTransport(1500);
    vac12->setHernieuwing(28);
    vac12->setTemperatuur(5);

    simulatie_.centra[2]->vaccins.push_back(vac10);
    simulatie_.centra[2]->vaccins.push_back(vac11);
    simulatie_.centra[2]->vaccins.push_back(vac12);

    simulatie_.centra[3]->setNaam("Flanders Expo");
    simulatie_.centra[3]->setAdres("Maaltekouter 1, Sint-Denijs-Westrem");
    simulatie_.centra[3]->setInwoners(257029);
    simulatie_.centra[3]->setCapaciteit(3000);

    Vaccin* vac13;
    Vaccin pvac13;
    vac13 = &pvac13;
    vac13->setType("Pfizer");
    vac13->setLevering(93000);
    vac13->setInterval(6);
    vac13->setTransport(2000);
    vac13->setHernieuwing(21);
    vac13->setTemperatuur(-70);

    Vaccin* vac14;
    Vaccin pvac14;
    vac14 = &pvac14;
    vac14->setType("Moderna");
    vac14->setLevering(46000);
    vac14->setInterval(13);
    vac14->setTransport(1000);
    vac14->setHernieuwing(28);
    vac14->setTemperatuur(-20);

    Vaccin* vac15;
    Vaccin pvac15;
    vac15 = &pvac15;
    vac15->setType("AstraZeneca");
    vac15->setLevering(67000);
    vac15->setInterval(4);
    vac15->setTransport(1500);
    vac15->setHernieuwing(28);
    vac15->setTemperatuur(5);

    simulatie_.centra[3]->vaccins.push_back(vac13);
    simulatie_.centra[3]->vaccins.push_back(vac14);
    simulatie_.centra[3]->vaccins.push_back(vac15);

    Centrum** double_p1 = &simulatie_.centra[0];
    Centrum** double_p2 = &simulatie_.centra[1];
    Centrum** double_p3 = &simulatie_.centra[2];
    Centrum** double_p4 = &simulatie_.centra[3];

    simulatie_.hubs[0]->centra.push_back(double_p1);
    simulatie_.hubs[0]->centra.push_back(double_p2);
    simulatie_.hubs[0]->centra.push_back(double_p3);
    simulatie_.hubs[0]->centra.push_back(double_p4);

    string fileName = "../testOutput/happyDayOut.txt";
    ofstream myfile;
    myfile.open("../testOutput/happyDayOutError.txt");
    std::ostream bitBucket(NULL);
    simulatie_.simuleren(25, bitBucket);
    ProjectExporter::exportProject(fileName.c_str(),myfile, H);
    myfile.close();
    string fileName2 = "../testOutput/happyDayGraphicImpression.txt";
    myfile.open("../testOutput/happyDayGraphicImpressionError.txt");
    ProjectExporter::graphic_impression(fileName2.c_str(),myfile, H);
    myfile.close();
    string fileName3 = "../testOutput/happyDayStatistics.txt";
    myfile.open("../testOutput/happyDayStatisticsError.txt");
    ProjectExporter::statistics(fileName3.c_str(), myfile,simulatie_);
    myfile.close();

    EXPECT_TRUE(
            FileCompare("../testOutput/happyDayExpectedOut.txt", "../testOutput/happyDayOut.txt"));
    EXPECT_TRUE(
            FileCompare("../testOutput/happyDayGraphicImpressionExpected.txt", "../testOutput/happyDayGraphicImpression.txt"));
    EXPECT_TRUE(
            FileCompare("../testOutput/happyDayStatisticsExpected.txt", "../testOutput/happyDayStatistics.txt"));
}

TEST_F(ProjectOutputTest, OutputOneCentrum) {
    ASSERT_TRUE(DirectoryExists("../testOutput"));
    //if directory doesn't exist then no need in proceeding with the test
    Simulatie simulatie_;
    Hub H;
    Centrum* a;
    Centrum aa;
    a = &aa;

    Vaccin* vac;
    Vaccin pvac;
    vac = &pvac;
    vac->setType("Pfizer");
    vac->setLevering(93000);
    vac->setInterval(6);
    vac->setTransport(2000);
    vac->setHernieuwing(2);
    vac->setTemperatuur(-70);
    H.vaccins.push_back(vac);

    simulatie_.centra.push_back(a);
    simulatie_.centra[0]->setNaam("Park Spoor Oost");
    simulatie_.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    simulatie_.centra[0]->setInwoners(540173);
    simulatie_.centra[0]->setCapaciteit(7500);

    Vaccin* vac2;
    Vaccin pvac2;
    vac2 = &pvac2;
    vac2->setType("Pfizer");
    vac2->setLevering(93000);
    vac2->setInterval(6);
    vac2->setTransport(2000);
    vac2->setHernieuwing(2);
    vac2->setTemperatuur(-70);
    simulatie_.centra[0]->vaccins.push_back(vac2);
    Centrum** double_p1 = &simulatie_.centra[0];
    Hub* p = &H;
    simulatie_.hubs.push_back(p);
    simulatie_.hubs[0]->centra.push_back(double_p1);

    string fileName = "../testOutput/OutputOneCentrum.txt";
    ofstream myfile;
    myfile.open("../testOutput/OutputOneCentrumError.txt");
    std::ostream bitBucket(NULL);
    simulatie_.simuleren(6, bitBucket);
    ProjectExporter::exportProject(fileName.c_str(),myfile, H);
    myfile.close();
    EXPECT_TRUE(
            FileCompare("../testOutput/OutputOneCentrumExpected.txt", "../testOutput/OutputOneCentrum.txt"));
}

TEST_F(ProjectOutputTest, GraphicImpression){
    ASSERT_TRUE(DirectoryExists("../testOutput"));
    //if directory doesn't exist then no need in proceeding with the test
    Simulatie simulatie_;

    Hub H;
    Centrum* a;
    Centrum aa;
    a = &aa;

    Vaccin* vac;
    Vaccin pvac;
    vac = &pvac;
    vac->setType("Pfizer");
    vac->setLevering(93000);
    vac->setInterval(6);
    vac->setTransport(2000);
    vac->setHernieuwing(2);
    vac->setTemperatuur(-70);
    H.vaccins.push_back(vac);

    simulatie_.centra.push_back(a);
    simulatie_.centra[0]->setNaam("Park Spoor Oost");
    simulatie_.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    simulatie_.centra[0]->setInwoners(540173);
    simulatie_.centra[0]->setCapaciteit(7500);

    Vaccin* vac2;
    Vaccin pvac2;
    vac2 = &pvac2;
    vac2->setType("Pfizer");
    vac2->setLevering(93000);
    vac2->setInterval(6);
    vac2->setTransport(2000);
    vac2->setHernieuwing(2);
    vac2->setTemperatuur(-70);
    simulatie_.centra[0]->vaccins.push_back(vac2);

    Centrum** double_p1 = &simulatie_.centra[0];
    Hub* p = &H;
    simulatie_.hubs.push_back(p);
    simulatie_.hubs[0]->centra.push_back(double_p1);

    string fileName = "../testOutput/OutputGraphicImpression.txt";
    ofstream myfile;
    myfile.open("../testOutput/OutputGraphicImpressionError.txt");
    std::ostream bitBucket(NULL);
    simulatie_.simuleren(6, bitBucket);
    ProjectExporter::graphic_impression(fileName.c_str(),myfile, H);
    myfile.close();
    EXPECT_TRUE(
            FileCompare("../testOutput/OutputGraphicImpressionExpected.txt", "../testOutput/OutputGraphicImpression.txt"));

}

TEST_F(ProjectOutputTest, Statistics){
    ASSERT_TRUE(DirectoryExists("../testOutput"));
    //if directory doesn't exist then no need in proceeding with the test
    Simulatie simulatie_;

    Hub H;
    Centrum* a;
    Centrum aa;
    a = &aa;

    Vaccin* vac;
    Vaccin pvac;
    vac = &pvac;
    vac->setType("Pfizer");
    vac->setLevering(93000);
    vac->setInterval(6);
    vac->setTransport(2000);
    vac->setHernieuwing(2);
    vac->setTemperatuur(-70);
    H.vaccins.push_back(vac);

    simulatie_.centra.push_back(a);
    simulatie_.centra[0]->setNaam("Park Spoor Oost");
    simulatie_.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    simulatie_.centra[0]->setInwoners(540173);
    simulatie_.centra[0]->setCapaciteit(7500);

    Vaccin* vac2;
    Vaccin pvac2;
    vac2 = &pvac2;
    vac2->setType("Pfizer");
    vac2->setLevering(93000);
    vac2->setInterval(6);
    vac2->setTransport(2000);
    vac2->setHernieuwing(2);
    vac2->setTemperatuur(-70);
    simulatie_.centra[0]->vaccins.push_back(vac2);

    Centrum** double_p1 = &simulatie_.centra[0];
    Hub* p = &H;
    simulatie_.hubs.push_back(p);
    simulatie_.hubs[0]->centra.push_back(double_p1);

    string fileName = "../testOutput/OutputStatistics.txt";
    ofstream myfile;
    myfile.open("../testOutput/OutputStatisticsError.txt");
    std::ostream bitBucket(NULL);
    simulatie_.simuleren(6, bitBucket);
    ProjectExporter::statistics(fileName.c_str(),myfile, simulatie_);
    myfile.close();
    EXPECT_TRUE(
            FileCompare("../testOutput/OutputStatisticsExpected.txt", "../testOutput/OutputStatistics.txt"));

}