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