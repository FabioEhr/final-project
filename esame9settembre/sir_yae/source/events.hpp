#ifndef EVENTS_HPP
#define EVENTS_HPP
#include "yae.hpp"

void mutate_contagiousness(
    City& playground);  // mutations occur when there are a lot of infected

void mutate_recovery(City& playground);

void mutate_deadliness(City& playground);

void protests(City& playground);  // they occur when morale is low

void violent_protests(City& playground);  // they occur when morale is low

void illegal_parties(City& playground);

void eureka(City& playground);

void panic(City& playground);

void no_beds(City& playground);

void rnd_events(City& playground);

#endif