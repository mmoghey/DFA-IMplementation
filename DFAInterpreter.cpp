#include "DFAInterpreter.h"
#include <exception>



DFAInterpreter::DFAInterpreter()
{
}


DFAInterpreter::~DFAInterpreter()
{
}

void DFAInterpreter::readDFAFile() {
	int numfStates, state;

	int prevState, nextState;
	char symbol;
	int i;
	string inputStr;
	char ch;

	ifstream fin("testdfa.txt");
	fin >> m_numDFAState;
	fin >> m_alphabetSize;
	for (int i = 0; i < m_alphabetSize; i++)
		fin >> m_alphabet[i];
	fin >> numfStates;

	for (i = 0; i < numfStates; i++) {
		fin >> state;
		m_finalState[state] = true;
	}

	while (!fin.eof()) {
		fin >> prevState >> symbol >> nextState;
		if (prevState < 0 && prevState > m_numDFAState) {
			cout << "\n Invalid State ! \n";
			cin >> ch;
			exit(-1);
		}

		bool valid = false;

		for (i = 0; i <= m_alphabetSize; i++) {
			if (m_alphabet[i] == symbol) {
				valid = true;
			}
		}

		if ((valid) == false) {
			cout << "\n Invalid symbol \n";
			cin >> ch;
			exit(-1);
		}

		if (nextState < 0 && nextState > m_numDFAState) {
			cout << "\n Invalid State ! \n";
			cin >> ch;
			exit(-1);
		}

		StateDFA * newState = new StateDFA;
		newState->name = prevState;
		newState->finalState = m_finalState[prevState];
		newState->m_symbolicTransitions[symbol] = nextState;

		bool found = 0;
		for (auto iter = m_DFAstates.begin(); iter != m_DFAstates.end(); ++iter) {
			if ((*iter)->name == prevState) {
				found = 1;
				(*iter)->m_symbolicTransitions[symbol] = nextState;
			}

		}
		if (found == 0)
			m_DFAstates.push_back(newState);
		//	m_transitionTable[prevState][symbol] = nextState;
	}

	fin.close();
}

void DFAInterpreter::interpretDFA() {

	char symbol;
	bool found;
	int prevState = 0, nextState = 0;
	string inputStr;

	cout << "Enter a string ";
	cin >> inputStr;


	for (unsigned i = 0; i < inputStr.size(); i++) {
		symbol = inputStr[i];
		found = false;

		for (int j = 0; j < m_alphabetSize; j++) {
			if (symbol == m_alphabet[j]) {
				found = true; break;
			}
		}

		if (found == false) {
			cout << "Invalid input";
			cin >> symbol;
			exit(0);
		}
		else
		{
			for (auto iter = m_DFAstates.begin(); iter != m_DFAstates.end(); ++iter) {
				if ((*iter)->name == prevState) {
					nextState = (*iter)->m_symbolicTransitions[symbol];
					break;
				}
			}
			//nextState = m_transitionTable[prevState][symbol];
		}
		prevState = nextState;
	}

	if (m_finalState[nextState])
		cout << "\n Accepted\n";
	else
		cout << "\n not Accepted \n";

}
