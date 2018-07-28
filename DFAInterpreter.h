#pragma once

#include <cstdio>
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

#include "StateDFA.h"

#ifndef MAX_NFA_STATES
#define MAX_NFA_STATES 10
#endif 

#ifndef MAX_ALPHABET_SIZE
#define MAX_ALPHABET_SIZE 10
#endif // !MAX_ALPHABET_SIZE

using namespace std;

class DFAInterpreter
{
public:
	DFAInterpreter();
	~DFAInterpreter();
	void readDFAFile();
	void interpretDFA();

	vector<StateDFA*> m_DFAstates;
	int m_alphabetSize;
	char m_alphabet[MAX_ALPHABET_SIZE];
	int m_numDFAState;
	bool m_finalState[MAX_NFA_STATES];
};

