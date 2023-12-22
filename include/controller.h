#ifndef controller_h
#define controller_h

#include "entities.h"

void main_SaveSpecificSeat(Theater t);

void main_CancelReservation(Theater t);

void main_View(Theater t);

void main_SaveStateOnFile(Theater t);

void main_SaveMultipleSeats(Theater t);

void main_SaveSpecificSeatThroughSystem(Theater t);

void main_SaveMultipleSeatsThroughSystem(Theater t);

void main_CancelMultipleReservations(Theater t);

void main_CancelAllReservations(Theater t);

void main_CheckSeat(Theater t);

void main_seeConsecutiveSeats(Theater t);

void main_SaveSpecificSeatThroughSystem(Theater t);

void main_SaveMultipleSeatsThroughSystem(Theater t);

Theater main_LoadState();
#endif
