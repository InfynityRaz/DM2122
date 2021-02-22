#include "Dialogue.h"

Dialogue::Dialogue(std::string fileName) : totalLines(0)
{
	file.open(fileName);
	if (!file)
		std::cout << "Cannot open dialogue text file" << std::endl;

	while (file.eof())
		++totalLines;

	file.close();

	file.open(fileName);
}

Dialogue::~Dialogue()
{
	file.close();
}

int Dialogue::getTotalLines()
{
	return totalLines;
}

std::string Dialogue::Update()
{
	std::string dialogue;
	std::getline(file, dialogue);
	return dialogue;
}