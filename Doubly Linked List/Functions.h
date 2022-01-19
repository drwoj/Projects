#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Diver.h"
#include "Flight.h"

vector<string> Inputs(int argc, char* argv[]);

bool cmpDiverDives(Diver x1, Diver x2);

bool cmpFlightFrom(Flight x1, Flight x2);