//
// Created by michel on 12.03.21.
//
// OPMERKING: VOOR DE OPBOUW WERD ER VEELVULDIG GEKEKEN NAAR HET VOORBEELD TICTACTOE21 geschreven door professor Demeyer

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include "Simulatie.h"
#include "HUB.h"

using namespace std;

class ProjectDomainTest: public ::testing::Test {
protected:
    friend class Simulatie;
    friend class Hub;
    friend class Centrum;
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.
    Simulatie simulatie_;
    Hub hub_;
    Centrum centrum_;
    Vaccin vaccin_;
};

/**
Tests the default constructor for Hub.
*/
TEST_F(ProjectDomainTest, DefaultConstructorHub) {
    EXPECT_TRUE(hub_.properlyInitialized());
    EXPECT_EQ(0, hub_.getVoorraad());
    EXPECT_TRUE(hub_.centra.empty());
    EXPECT_TRUE(hub_.vaccins.empty());
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
    Centrum** double_p1 = &centrum1;
    hub_.centra.push_back(double_p1);
    EXPECT_TRUE(hub_.centrumVerbonden(centrum1));
    EXPECT_FALSE(hub_.centrumVerbonden(centrum2));
    Centrum** double_p2 = &centrum2;
    hub_.centra.push_back(double_p2);
    EXPECT_TRUE(hub_.centrumVerbonden(centrum1));
    EXPECT_TRUE(hub_.centrumVerbonden(centrum2));
}

TEST_F(ProjectDomainTest, testsimuleerTransport){
    EXPECT_TRUE(hub_.properlyInitialized());
    EXPECT_TRUE(hub_.centra.empty());
    EXPECT_TRUE(hub_.vaccins.empty());


    Vaccin* vac;
    Vaccin pvac;
    vac = &pvac;
    vac->setType("Pfizer");
    vac->setLevering(93000);
    vac->setInterval(6);
    vac->setTransport(2000);
    vac->setHernieuwing(21);
    vac->setTemperatuur(-70);
    vac->setVoorraad(93000);
    hub_.vaccins.push_back(vac);

    Vaccin* vac2;
    Vaccin pvac2;
    vac2 = &pvac2;
    vac2->setType("Pfizer");
    vac2->setLevering(93000);
    vac2->setInterval(6);
    vac2->setTransport(2000);
    vac2->setHernieuwing(21);
    vac2->setTemperatuur(-70);

    Centrum* a;
    Centrum pcentrum;
    a = &pcentrum;
    simulatie_.centra.push_back(a);
    EXPECT_TRUE(simulatie_.centra[0]->properlyInitialized());
    simulatie_.centra[0]->setNaam("Park Spoor Oost");
    simulatie_.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    simulatie_.centra[0]->setInwoners(540173);
    simulatie_.centra[0]->setCapaciteit(7500);
    simulatie_.centra[0]->vaccins.push_back(vac2);
    Centrum** double_p = &simulatie_.centra[0];
    hub_.centra.push_back(double_p);
    Hub* p = &hub_;
    simulatie_.hubs.push_back(p);
    std::ostream bitBucket(NULL);
    hub_.simuleerTransport(bitBucket, 0);

    EXPECT_EQ(85500, hub_.getVoorraad());
    EXPECT_EQ(7500, simulatie_.centra[0]->getVoorraad());
    hub_.simuleerTransport(bitBucket, 0);
    EXPECT_EQ(78000, hub_.getVoorraad());
    EXPECT_EQ(15000, simulatie_.centra[0]->getVoorraad());
}

/**
Tests the "happy day" scenario for Hub
*/

TEST_F(ProjectDomainTest, HappyDayHub){
    EXPECT_TRUE(hub_.properlyInitialized());
    EXPECT_TRUE(hub_.centra.empty());
    EXPECT_TRUE(hub_.vaccins.empty());
    EXPECT_EQ(0, hub_.getVoorraad());



    Vaccin* vac;
    Vaccin pvac;
    vac = &pvac;
    vac->setType("Pfizer");
    vac->setLevering(93000);
    vac->setInterval(6);
    vac->setTransport(2000);
    vac->setHernieuwing(2);
    vac->setTemperatuur(-70);
    hub_.vaccins.push_back(vac);

    Vaccin* vac2;
    Vaccin pvac2;
    vac2 = &pvac2;
    vac2->setType("Pfizer");
    vac2->setLevering(93000);
    vac2->setInterval(6);
    vac2->setTransport(2000);
    vac2->setHernieuwing(2);
    vac2->setTemperatuur(-70);

    Vaccin* vac3;
    Vaccin pvac3;
    vac3 = &pvac3;
    vac3->setType("Pfizer");
    vac3->setLevering(93000);
    vac3->setInterval(6);
    vac3->setTransport(2000);
    vac3->setHernieuwing(2);
    vac3->setTemperatuur(-70);

    Hub* p = &hub_;
    simulatie_.hubs.push_back(p);

    Centrum* a;
    Centrum pcentrum;
    a = &pcentrum;
    simulatie_.centra.push_back(a);
    EXPECT_TRUE(simulatie_.centra[0]->properlyInitialized());
    simulatie_.centra[0]->setNaam("Park Spoor Oost");
    simulatie_.centra[0]->setAdres("Noordersingel 40, Antwerpen");
    simulatie_.centra[0]->setInwoners(540173);
    simulatie_.centra[0]->setCapaciteit(7500);
    simulatie_.centra[0]->vaccins.push_back(vac2);

    Centrum** double_p1 = &a;
    simulatie_.hubs[0]->centra.push_back(double_p1);

    Centrum* b;
    Centrum qcentrum;
    b = &qcentrum;
    simulatie_.centra.push_back(b);
    EXPECT_TRUE(simulatie_.centra[1]->properlyInitialized());
    simulatie_.centra[1]->setNaam("AED Studios");
    simulatie_.centra[1]->setAdres("Fabriekstraat 38, Lint");
    simulatie_.centra[1]->setInwoners(76935);
    simulatie_.centra[1]->setCapaciteit(2000);
    simulatie_.centra[1]->vaccins.push_back(vac3);
    Centrum** double_p2 = &b;
    simulatie_.hubs[0]->centra.push_back(double_p2);

    std::ostream bitBucket(NULL);

    simulatie_.simuleren(6, bitBucket);
    EXPECT_EQ(7500, hub_.getVoorraad());
    EXPECT_EQ(0, simulatie_.centra[0]->getVoorraad());
    EXPECT_EQ(22500, simulatie_.centra[0]->getGevacineerden());
    EXPECT_EQ(0, simulatie_.centra[1]->getVoorraad());
    EXPECT_EQ(6000, simulatie_.centra[1]->getGevacineerden());
}

/**
Tests the default constructor for Centrum.
*/
TEST_F(ProjectDomainTest, DefaultConstructorCentrum){
    EXPECT_TRUE(centrum_.properlyInitialized());
    EXPECT_EQ("a", centrum_.getNaam());
    EXPECT_EQ("a", centrum_.getAdres());
    EXPECT_EQ(0, centrum_.getInwoners());
    EXPECT_EQ(0, centrum_.getCapaciteit());
    EXPECT_EQ(0, centrum_.getGevacineerden());
    EXPECT_EQ(0, centrum_.getVoorraad());
    EXPECT_TRUE(centrum_.vaccins.empty());
}

/**
Tests the "happy day" scenario for Centrum
*/
TEST_F(ProjectDomainTest, HappyDayCentrum){
    EXPECT_TRUE(centrum_.properlyInitialized());
    centrum_.setInwoners(1000);
    centrum_.setCapaciteit(500);
    std::ostream bitBucket(NULL);
    centrum_.vaccineren(bitBucket,0);
    EXPECT_EQ(0, centrum_.getGevacineerden());
    EXPECT_EQ(0, centrum_.getVoorraad());
    Vaccin* vac;
    Vaccin pvac;
    vac = &pvac;
    vac->setType("Pfizer");
    vac->setLevering(93000);
    vac->setInterval(6);
    vac->setTransport(2000);
    vac->setHernieuwing(21);
    vac->setTemperatuur(-70);
    centrum_.vaccins.push_back(vac);
    centrum_.vaccins[0]->setVoorraad(700);
    centrum_.vaccineren(bitBucket,0);
    EXPECT_EQ(0, centrum_.getGevacineerden());
    EXPECT_EQ(200, centrum_.getVoorraad());
    centrum_.vaccineren(bitBucket,22);
    EXPECT_EQ(200, centrum_.getGevacineerden());
    EXPECT_EQ(0, centrum_.getVoorraad());
}

/**
Tests the default constructor for Vaccin.
*/
TEST_F(ProjectDomainTest, DefaultConstructorVaccin) {
    EXPECT_TRUE(vaccin_.properlyInitialized());
    EXPECT_EQ("a", vaccin_.getType());
    EXPECT_EQ(0, vaccin_.getLevering());
    EXPECT_EQ(0, vaccin_.getVoorraad());
    EXPECT_EQ(0, vaccin_.getHernieuwing());
    EXPECT_EQ(0, vaccin_.getTemperatuur());
    EXPECT_EQ(1, vaccin_.getInterval());
    EXPECT_EQ(1, vaccin_.getTransport());
}

/**
Verify whether unsatisfied pre-conditions indeed trigger failures
*/
TEST_F(ProjectDomainTest, ContractViolations) {
    std::ostream bitBucket(NULL);
    EXPECT_DEATH(simulatie_.simuleren(-1, bitBucket), "Assertion.*failed"); // simuleren needs a positive integer
    EXPECT_DEATH(centrum_.setCapaciteit(-1), "Assertion.*failed"); // setCapaciteit needs a positive integer
    EXPECT_DEATH(centrum_.setGevacineerden(-1), "Assertion.*failed"); // setGevaccineerden needs a positive integer
    EXPECT_DEATH(centrum_.setNaam(""), "Assertion.*failed"); // setNaam needs a non empty string
    EXPECT_DEATH(centrum_.setAdres(""), "Assertion.*failed"); // setAdres needs a non empty string
    EXPECT_DEATH(centrum_.setInwoners(-1), "Assertion.*failed"); //setInwoners needs a positive integer
    EXPECT_DEATH(centrum_.vaccineren(bitBucket, -1), "Assertion.*failed"); //setInwoners needs a positive integer
    EXPECT_DEATH(vaccin_.setType(""), "Assertion.*failed"); //setType needs a non empty string
    EXPECT_DEATH(vaccin_.setLevering(-1), "Assertion.*failed"); //setLevering needs a positive integer
    EXPECT_DEATH(vaccin_.setVoorraad(-1), "Assertion.*failed"); //setVoorraad needs a positive integer
    EXPECT_DEATH(vaccin_.setHernieuwing(-1), "Assertion.*failed"); //setHernieuwing needs a positive integer
    EXPECT_DEATH(vaccin_.setInterval(0), "Assertion.*failed"); //setInterval needs a strictly positive integer
    EXPECT_DEATH(vaccin_.setTransport(0), "Assertion.*failed"); //setTransport needs a strictly positive integer
}