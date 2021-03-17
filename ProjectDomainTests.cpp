//
// Created by michel on 12.03.21.
//
// OPMERKING: VOOR DE OPBOUW WERD ER VEELVULDIG GEKEKEN NAAR HET VOORBEELD TICTACTOE21 geschreven door professor Demeyer

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include "HUB.h"

using namespace std;

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
Tests the default constructor for Hub.
*/
TEST_F(ProjectDomainTest, DefaultConstructorHub) {
    EXPECT_TRUE(hub_.properlyInitialized());
    EXPECT_EQ(0, hub_.getLevering());
    EXPECT_EQ(0, hub_.getVaccins());
    EXPECT_EQ(1, hub_.getInterval());
    EXPECT_EQ(1, hub_.getTransport());
}

TEST_F(ProjectDomainTest, testcentrumVerbonden) {
    EXPECT_TRUE(hub_.properlyInitialized());
    Centrum* centrum1;
    Centrum* centrum2;
    Centrum a;
    centrum1 = &a;
    Centrum b;
    centrum2 = &b;
    centrum1->setNaam("naam1");
    centrum1->setAdres("adres1");
    centrum2->setNaam("naam2");
    centrum2->setAdres("adres2");
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
    Centrum *a;
    Centrum pcentrum;
    a = &pcentrum;
    a->setNaam("Park Spoor Oost");
    a->setAdres("Noordersingel 40, Antwerpen");
    a->setInwoners(540173);
    a->setCapaciteit(7500);
    a->setVaccins(0);
    hub_.centra.push_back(a);
    EXPECT_EQ(4,hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0]->setVaccins(7500);
    EXPECT_EQ(0, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0]->setVaccins(5500);
    EXPECT_EQ(1, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0]->setVaccins(0);
    hub_.centra[0]->setCapaciteit(1000);
    EXPECT_EQ(1, hub_.berekenLadingen(hub_.centra[0]));
    hub_.centra[0]->setCapaciteit(500);
    EXPECT_EQ(0, hub_.berekenLadingen(hub_.centra[0]));
}

TEST_F(ProjectDomainTest, testsimuleerTransport){
    EXPECT_TRUE(hub_.properlyInitialized());
    EXPECT_TRUE(hub_.centra.empty());
    hub_.setTransport(2000);
    hub_.setInterval(6);
    hub_.setVaccins(93000);
    hub_.setLevering(93000);
    Centrum* a;
    Centrum pcentrum;
    a = &pcentrum;
    hub_.centra.push_back(a);
    EXPECT_TRUE(hub_.centra[0]->properlyInitialized());
    hub_.centra[0]->setNaam("Park Spoor Oost");
    hub_.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    hub_.centra[0]->setInwoners(540173);
    hub_.centra[0]->setCapaciteit(7500);
    hub_.centra[0]->setVaccins(0);
    std::ostream bitBucket(NULL);
    hub_.simuleerTransport(bitBucket, hub_.centra[0]);
    EXPECT_EQ(85000, hub_.getVaccins());
    EXPECT_EQ(8000, hub_.centra[0]->getVaccins());
    hub_.simuleerTransport(bitBucket, hub_.centra[0]);
    EXPECT_EQ(85000, hub_.getVaccins());
    EXPECT_EQ(8000, hub_.centra[0]->getVaccins());
}

/**
Tests the "happy day" scenario for Hub
*/
TEST_F(ProjectDomainTest, HappyDayHub){
    EXPECT_TRUE(hub_.properlyInitialized());
    EXPECT_TRUE(hub_.centra.empty());
    EXPECT_EQ(0, hub_.getLevering());
    EXPECT_EQ(0, hub_.getVaccins());
    EXPECT_EQ(1, hub_.getInterval());
    EXPECT_EQ(1, hub_.getTransport());
    hub_.setTransport(2000);
    hub_.setInterval(6);
    hub_.setLevering(93000);
    Centrum* a;
    Centrum pcentrum;
    a = &pcentrum;
    hub_.centra.push_back(a);
    EXPECT_TRUE(hub_.centra[0]->properlyInitialized());
    hub_.centra[0]->setNaam("Park Spoor Oost");
    hub_.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    hub_.centra[0]->setInwoners(540173);
    hub_.centra[0]->setCapaciteit(7500);
    hub_.centra[0]->setVaccins(0);
    Centrum* b;
    Centrum qcentrum;
    b = &qcentrum;
    hub_.centra.push_back(b);
    EXPECT_TRUE(hub_.centra[1]->properlyInitialized());
    hub_.centra[1]->setNaam("AED Studios");
    hub_.centra[1]->setAdres("Fabriekstraat 38, Lint");
    hub_.centra[1]->setInwoners(76935);
    hub_.centra[1]->setCapaciteit(2000);
    hub_.centra[1]->setVaccins(0);
    std::ostream bitBucket(NULL);
    hub_.simuleren(3, bitBucket);
    EXPECT_EQ(63000, hub_.getVaccins());
    EXPECT_EQ(6, hub_.getInterval());
    EXPECT_EQ(2000, hub_.getTransport());
    EXPECT_EQ(1500, hub_.centra[0]->getVaccins());
    EXPECT_EQ(22500, hub_.centra[0]->getGevacineerden());
    EXPECT_EQ(0, hub_.centra[1]->getVaccins());
    EXPECT_EQ(6000, hub_.centra[1]->getGevacineerden());
}

/**
Tests the default constructor for Centrum.
*/
TEST_F(ProjectDomainTest, DefaultConstructorCentrum){
    EXPECT_TRUE(centrum_.properlyInitialized());
    EXPECT_EQ(0, centrum_.getVaccins());
    EXPECT_EQ("a", centrum_.getNaam());
    EXPECT_EQ("a", centrum_.getAdres());
    EXPECT_EQ(0, centrum_.getInwoners());
    EXPECT_EQ(0, centrum_.getCapaciteit());
    EXPECT_EQ(0, centrum_.getGevacineerden());
}

/**
Tests the "happy day" scenario for Centrum
*/
TEST_F(ProjectDomainTest, HappyDayCentrum){
    EXPECT_TRUE(centrum_.properlyInitialized());
    centrum_.setInwoners(1000);
    centrum_.setCapaciteit(500);
    std::ostream bitBucket(NULL);
    centrum_.vaccineren(bitBucket);
    EXPECT_EQ(0, centrum_.getGevacineerden());
    EXPECT_EQ(0, centrum_.getVaccins());
    centrum_.setVaccins(700);
    centrum_.vaccineren(bitBucket);
    EXPECT_EQ(500, centrum_.getGevacineerden());
    EXPECT_EQ(200, centrum_.getVaccins());
    centrum_.vaccineren(bitBucket);
    EXPECT_EQ(700, centrum_.getGevacineerden());
    EXPECT_EQ(0, centrum_.getVaccins());
}

/**
Verify whether unsatisfied pre-conditions indeed trigger failures
*/
TEST_F(ProjectDomainTest, ContractViolations) {
    EXPECT_DEATH(hub_.setVaccins(-1), "Assertion.*failed"); // setVaccins needs a positive int
    EXPECT_DEATH(hub_.setTransport(0), "Assertion.*failed"); // setTransport needs a strictly positive int
    EXPECT_DEATH(hub_.setLevering(-1), "Assertion.*failed"); // setLevering needs a positive int
    EXPECT_DEATH(hub_.setInterval(0), "Assertion.*failed"); // setInterval needs a strictly positive int
    EXPECT_DEATH(hub_.verlaagVaccins(1),"Assertion.*failed"); // verlaagVaccins needs a positive integer lower or equal to getVaccins()
    EXPECT_DEATH(hub_.verhoogVaccins(-1),"Assertion.*failed"); // verhoogVaccins needs a positive int
    std::ostream bitBucket(NULL);
    EXPECT_DEATH(hub_.simuleren(-1, bitBucket), "Assertion.*failed"); // simuleren needs a positive integer
    EXPECT_DEATH(centrum_.setVaccins(-1), "Assertion.*failed"); // centrum.setVaccins needs a positive integer
    EXPECT_DEATH(centrum_.setVaccins(10), "Assertion.*failed"); // centrum.setVaccins needs a positive integer lower than capaciteit*2
    EXPECT_DEATH(centrum_.setCapaciteit(-1), "Assertion.*failed"); // setCapaciteit needs a positive integer
    EXPECT_DEATH(centrum_.setGevacineerden(-1), "Assertion.*failed"); // setGevaccineerden needs a positive integer
    EXPECT_DEATH(centrum_.setNaam(""), "Assertion.*failed"); // setNaam needs a non empty string
    EXPECT_DEATH(centrum_.setAdres(""), "Assertion.*failed"); // setAdres needs a non empty string
    EXPECT_DEATH(centrum_.setInwoners(-1), "Assertion.*failed"); //setInwoners needs a positive integer
}