#ifndef DECISIONS_HPP
#define DECISIONS_HPP
#include "yae.hpp"

void buy_masks(City& playground);

void close_restaurants(City& playground);

void close_theatres(City& playground);  // different from close_restaurants,
                                        // lesser economic impact but people are
                                        // sadder. affects "mixed" encounters

void close_schools(City& playground);

void close_churches(City& playground);

void curfew(City& playground);

void lockdown(City& playground);
// Open functions
void open_restaurants(City& playground);
void open_theatres(City& playground);
void open_schools(City& playground);
void open_churches(City& playground);

void alleviate_curfew(City& playground);

void invest_in_research(City& playground);

void invest_in_digital(City& playground);

void terrorize_with_media(
    City& playground);  // changes perception of the dangerousness of the virus

void tranquillize_with_media(City& playground);  // shouldn't be a good option

void modernize_hospitals(City& playground);
void build_beds(City& playground);

void vaccinate_young(City& playground);

void vaccinate_adults(City& playground);
void vaccinate_elders(City& playground);
#endif