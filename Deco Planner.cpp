#include <iostream>
#include <cmath>
using namespace std;

double tissuesN[16]; // Tissue Compartments for Nitrogen
int halfTimes[16];
double GFLow, GFHigh, A, B, vapourP, ATM;
double R, t; // variables for Schreiner Equation
double fN, pN; //Nitrogen fraction in breathing gas

void HalfTimes() {
	halfTimes[0] = 5;
	halfTimes[1] = 8;
	halfTimes[2] = 12.5;
	halfTimes[3] = 18.5;
	halfTimes[4] = 27;
	halfTimes[5] = 38.3;
	halfTimes[6] = 54.3;
	halfTimes[7] = 77;
	halfTimes[8] = 109;
	halfTimes[9] = 146;
	halfTimes[10] = 187;
	halfTimes[11] = 239;
	halfTimes[12] = 305;
	halfTimes[13] = 390;
	halfTimes[14] = 498;
	halfTimes[15] = 635;
}

void Init(double attitude, double nitrogenFraction) {
	HalfTimes();

	vapourP = 0.0627;
	ATM = attitude; //set diving attitude
	fN = nitrogenFraction; // Set Partial pressure of nitrogen

	for (auto&& tissue : tissuesN) // tissue loading after breathing on surface and not diving for a while.
		tissue = 0.7902 * (ATM - vapourP);
}

double SchreinerEquation(double tissuePressure, double halfTime) {

	double k = log(2) / halfTime;
	double value = pow(exp(1), -1*k*t);
	return pN + R * (t - 1 / k) - (pN - tissuePressure - R / k) * value;
}


void Descent(double depth, double descentRate) {
	R = fN * descentRate / 10;
	t = depth / descentRate; //time to descent
	pN = fN * (1 - vapourP); // pressure of inspired nitrogen

	for (int i = 0; i < 16; i++)
		tissuesN[i] = SchreinerEquation(tissuesN[i], halfTimes[i]);
}

void Dive(double depth, double time) {
	R = 0; //no pressure change
	t = time;
	pN = fN * (1 - vapourP + depth / 10);

	for (int i = 0; i < 16; i++)
		tissuesN[i] = SchreinerEquation(tissuesN[i], halfTimes[i]);
}

void Ascent(double depth, double stop) {
	R = fN * -1; // 10m/min is 1 bar pressure change (negative because while ascending)
	t = (depth - stop) / 10; //ascending rate is 10m/min

	for (int i = 0; i < 16; i++)
		tissuesN[i] = SchreinerEquation(tissuesN[i], halfTimes[i]);
}

void show() {
	for (auto&& i : tissuesN)
		cout << i << endl;
	cout << endl<<endl;
}

int main()
{
	Init(1, 0.68);
	Descent(30, 20);
	show();
	Dive(30, 20);
	show();
	Ascent(30, 10);
	show();
	
}
