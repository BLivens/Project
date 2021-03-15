//
// Created by michel on 12.03.21.
//

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

using namespace std;

#include "HUB.h"

class ProjectDomainTest: public ::testing::Test {
protected:
    friend class Hub;
    friend class Centrum;
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    Hub hub_;
    Centrum centrum_;
};

/**
Tests the default constructor.
*/
TEST_F(ProjectDomainTest, DefaultConstructor) {
    EXPECT_TRUE(hub_.properlyInitialized());
    // verify post-condition
    EXPECT_EQ(0, hub_.getLevering());
    EXPECT_EQ(0, hub_.getVaccins());
    EXPECT_EQ(0, hub_.getInterval());
    EXPECT_EQ(1, hub_.getTransport());
    /*
    for(unsigned int i = 0; i<hub_.centra.size(); i++){
        EXPECT_TRUE(hub_.centra[i].properlyInitialized());
    }
     */
}

TEST_F(ProjectDomainTest, testcentrumVerbonden) {
    EXPECT_TRUE(hub_.properlyInitialized());
    Centrum centrum1;
    Centrum centrum2;
    centrum1.naam = "naam1";
    centrum1.adres = "adres1";
    centrum2.naam = "naam2";
    centrum2.adres = "adres2";
    EXPECT_FALSE(hub_.centrumVerbonden(centrum1));
    EXPECT_FALSE(hub_.centrumVerbonden(centrum2));
    hub_.centra.push_back(centrum1);
    EXPECT_TRUE(hub_.centrumVerbonden(centrum1));
    EXPECT_FALSE(hub_.centrumVerbonden(centrum2));
    hub_.centra.push_back(centrum2);
    EXPECT_TRUE(hub_.centrumVerbonden(centrum1));
    EXPECT_TRUE(hub_.centrumVerbonden(centrum2));
}

TEST_F(ProjectDomainTest, testberekenLadingen){
    EXPECT_TRUE(hub_.properlyInitialized());
    EXPECT_TRUE(hub_.centra.empty());
    hub_.setTransport(2000);
    hub_.setInterval(6);
    hub_.setVaccins(93000);
    hub_.setLevering(93000);
    Centrum a;
    a.naam = "Park Spoor Oost";
    a.adres = "Noordersingel 40, Antwerpen";
    a.inwoners = 540173;
    a.capaciteit = 7500;
    a.vaccins = 0;
    hub_.centra.push_back(a);
    EXPECT_EQ(4,hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0].vaccins = 7500;
    EXPECT_EQ(0, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0].vaccins = 5500;
    EXPECT_EQ(1, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0].vaccins = 0;
    hub_.centra[0].capaciteit = 1000;
    EXPECT_EQ(1, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0].capaciteit = 500;
    EXPECT_EQ(0, hub_.berekenLadingen(hub_.centra[0]));
}

TEST_F(ProjectDomainTest, testsimuleerTransport){
    EXPECT_TRUE(hub_.properlyInitialized());
    EXPECT_TRUE(hub_.centra.empty());
    hub_.setTransport(2000);
    hub_.setInterval(6);
    hub_.setVaccins(93000);
    hub_.setLevering(93000);
    Centrum a;
    a.naam = "Park Spoor Oost";
    a.adres = "Noordersingel 40, Antwerpen";
    a.inwoners = 540173;
    a.capaciteit = 7500;
    a.vaccins = 0;
    hub_.centra.push_back(a);
    EXPECT_EQ(4,hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0].vaccins = 7500;
    EXPECT_EQ(0, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0].vaccins = 5500;
    EXPECT_EQ(1, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0].vaccins = 0;
    hub_.centra[0].capaciteit = 1000;
    EXPECT_EQ(1, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0].capaciteit = 500;
    EXPECT_EQ(0, hub_.berekenLadingen(hub_.centra[0]));
}