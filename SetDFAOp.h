#pragma once
#include "DFAInterpreter.h"
#include "StateDFA.h"
#include <vector>
#include <map>

#define MAX_DFAS 10

class SetDFAOp
{
public:
	SetDFAOp();
	~SetDFAOp();
	void readDFAFile();
	void unionDFAs();
	void intersectionDFAs();
	void complementDFA();

	int m_numDFAs;
	std::vector<DFAInterpreter *> m_dfas;
	int m_currentState[MAX_DFAS];
};

