#include "Functions.h"

vector<string> Inputs(int argc, char* argv[]) {

    vector<string> inputs;
    inputs.reserve(4);
    inputs.resize(4);
    int check = 0;

    for (int i = 0; i < argc; i++) {

        if (!strcmp(argv[i], "-d")) {
            inputs[0] = argv[i + 1];
            check++;
        }

        if (!strcmp(argv[i], "-f")) {
            inputs[1] = argv[i + 1];
            check++;
        }

        if (!strcmp(argv[i], "-i")) {
            inputs[2] = argv[i + 1];
            check++;
        }

        if (!strcmp(argv[i], "-o")) {
            inputs[3] = argv[i + 1];
            check++;
        }
    }

    if (check < 4) {
        cout << "Bledna liczba argumentow!";
        inputs.clear();
        return inputs;
    }

    return inputs;
}


bool cmpDiverDives(Diver x1, Diver x2) {
    return x1.GetDives() < x2.GetDives();
}

bool cmpFlightFrom(Flight x1, Flight x2) {
    
    return x1.GetFrom() < x2.GetFrom();
}
