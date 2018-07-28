#pragma once

#include <cstdio>
#include <fstream>
#include <iostream>
#include <bitset>
#include <map>
#include <vector>

#ifndef MAX_NFA_STATES
#define MAX_NFA_STATES 10
#endif 

#ifndef MAX_ALPHABET_SIZE
#define MAX_ALPHABET_SIZE 10
#endif // !MAX_ALPHABET_SIZE


class StateDFA
{
public:

	bool finalState;
	int name;
	std::bitset<MAX_NFA_STATES> m_NFAstates;
	//std::bitset<MAX_NFA_STATES> transitions[MAX_ALPHABET_SIZE];
	std::map<char, std::bitset<MAX_NFA_STATES>> m_dfaTransitions;
	//int symbolicTransitions[MAX_ALPHABET_SIZE];
	std::map<char, int> m_symbolicTransitions;

	StateDFA();
	~StateDFA();
};

