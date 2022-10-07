#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "Circuit.h"
#include <sstream>
class Menu
{
	Circuit circuit;
public:

	void handle() {
		int key;
		while (true) {

			key = displayMenu();
			if (key == '1')
				displayAdd();
			else if (key == '2')
				displayDelete();
			else if (key == '0')
				return;
			else if (key == '3')
				displayCircuit();
		}
	}

	void displayCircuit() {
		system("CLS");
		circuit.displayGates();
		std::cout << "\n";
		system("PAUSE");
	}

	int displayMenu() {
		system("CLS");
		std::cout << "0. Exit\n1. Add Gate\n2. Delete Gate\n3. Show Circuit";

		char key = _getch();

		return key;
	}

	void displayAdd() {
		system("CLS");
		std::cout << "1. OR\n2. NOR\n3. AND\n4. NAND\n";
		char key = _getch();
		std::cout << "Name of the gate: ";
		std::string name;
		std::cin >> name;
		std::cout << "Number of inputs: ";
		unsigned numInputs = 0;
		std::cin >> numInputs;

		while (true) {
			std::cout << "Inputs(logic values or names of gates separated with spacebar): ";
			std::string inputs;
			std::cin.clear();
			std::cin.ignore();
			getline(std::cin, inputs);
			if (parseInput(key, name, numInputs, inputs))
				break;
		}
	}


	void displayDelete() {
		system("CLS");
		std::cout << "Name of the gate to delete: ";
		std::string name;
		std::cin >> name;
		if (circuit.checkGate(name)) {
			circuit.deleteGate(name);
			std::cout << "Gate deleted!";
			Sleep(500);
		}
		else std::cout << "Gate not found!";
		Sleep(500);
	}

	bool parseInput(char type, std::string name, int numInputs, std::string s) {
		std::vector<bool> valueInputs;
		std::vector<std::string> gateInputs;
		std::stringstream ss(s);
		std::string input;

		while (ss >> input) {

			if (input == "1" || input == "true" || input == "TRUE" || input == "True")
				valueInputs.push_back(true);
			else if (input == "0" || input == "false" || input == "FALSE" || input == "False")
				valueInputs.push_back(false);

			else if(circuit.checkGate(input) && std::find(gateInputs.begin(), gateInputs.end(), input) ==gateInputs.end())
				gateInputs.push_back(input);
		}
		
		if (numInputs < valueInputs.size() + gateInputs.size()) {
			std::cout << "\nWrong inputs!";
			Sleep(500);
			return false;
		}

		switch (type) {
		case '1': 
			circuit.addGate<OrGate>(name, numInputs, gateInputs, valueInputs);
			break;
		case '2': 
			circuit.addGate<NorGate>(name, numInputs, gateInputs, valueInputs);
			break;
		case '3': 
			circuit.addGate<AndGate>(name, numInputs, gateInputs, valueInputs);
			break;
		case '4': 
			circuit.addGate<NandGate>(name, numInputs, gateInputs, valueInputs);
			break;
		}


		std::cout << "Gate added!";
		Sleep(500);
		return true;
	}

	
};

