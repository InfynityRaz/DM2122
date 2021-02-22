#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Application.h"

class Dialogue
{
private:
	int totalLines;
	std::ifstream file;

public:
	Dialogue(std::string fileName);
	~Dialogue();

	int getTotalLines();	//return total number of lines in text file
	std::string Update();	//loads next line of dialogue (use getline)
};