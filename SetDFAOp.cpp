#include "SetDFAOp.h"



SetDFAOp::SetDFAOp()
{
}


SetDFAOp::~SetDFAOp()
{
}

void SetDFAOp::readDFAFile() {
	int numfStates, state;

	int prevState, nextState;
	char symbol;
	int i;
	string inputStr;
	int  numTransitions;
	char ch;

	ifstream fin("DFA.txt");
	fin >> m_numDFAs;
	for (int k = 0; k < m_numDFAs; k++) {
		DFAInterpreter *newDFA = new DFAInterpreter();

		fin >> newDFA->m_numDFAState;
		fin >> newDFA->m_alphabetSize;
		for (int i = 0; i < newDFA->m_alphabetSize; i++)
			fin >> newDFA->m_alphabet[i];
		fin >> numfStates;

		for (i = 0; i < numfStates; i++) {
			fin >> state;
			newDFA->m_finalState[state] = true;
		}

		fin >> numTransitions;
		for (int j = 0; j < numTransitions; j++) {
			fin >> prevState >> symbol >> nextState;
			if (prevState < 0 && prevState > newDFA->m_numDFAState) {
				cout << "\n Invalid State ! \n";
				cin >> ch;
				exit(-1);
			}

			bool valid = false;

			for (i = 0; i <= newDFA->m_alphabetSize; i++) {
				if (newDFA->m_alphabet[i] == symbol) {
					valid = true;
				}
			}

			if ((valid) == false) {
				cout << "\n Invalid symbol \n";
				cin >> ch;
				exit(-1);
			}

			if (nextState < 0 && nextState > newDFA->m_numDFAState) {
				cout << "\n Invalid State ! \n";
				cin >> ch;
				exit(-1);
			}

			StateDFA * newState = new StateDFA;
			newState->name = prevState;
			newState->finalState = newDFA->m_finalState[prevState];
			newState->m_symbolicTransitions[symbol] = nextState;

			bool found = 0;
			for (auto iter = newDFA->m_DFAstates.begin(); iter != newDFA->m_DFAstates.end(); ++iter) {
				if ((*iter)->name == prevState) {
					found = 1;
					(*iter)->m_symbolicTransitions[symbol] = nextState;
				}

			}
			if (found == 0)
				newDFA->m_DFAstates.push_back(newState);
			//	m_transitionTable[prevState][symbol] = nextState;
		}

		m_dfas.push_back(newDFA);
	}
	
	fin.close();
}


void  SetDFAOp::unionDFAs() {

	char symbol;
	bool found;
	int prevState = 0, nextState = 0;
	string inputStr;
	int currentState[MAX_DFAS];
	int DFAcounter = 0;
	char ch;

	cout << "Enter a string ";
	cin >> inputStr;

	for (int i = 0; i < m_numDFAs; i++) {
		currentState[i] = 0;
	}

	for (unsigned i = 0; i < inputStr.size(); i++) {
		symbol = inputStr[i];
		found = false;

		for (int j = 0; j < m_dfas[0]->m_alphabetSize; j++) {
			if (symbol == m_dfas[0]->m_alphabet[j]) {
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
			DFAcounter = 0;
			for (int i = 0; i < m_numDFAs; i++) {
				for (auto iter = m_dfas[i]->m_DFAstates.begin(); iter != m_dfas[i]->m_DFAstates.end(); ++iter) {
					if ((*iter)->name == m_currentState[i]) {
						nextState = (*iter)->m_symbolicTransitions[symbol];
						break;
					}
				}
				m_currentState[DFAcounter++] = nextState;				
			}

		}
	}
	bool accepted = false;
	for (int i = 0; i < m_numDFAs; i++) {
		if (m_dfas[i]->m_finalState[m_currentState[i]]) {
			accepted = true;
			break;
		}
	}
	if (accepted)
		cout << "\n Accepted!! \n";
	else 
		cout << "\n REJECTED!! \n";


}

void SetDFAOp::intersectionDFAs() {

	char symbol;
	bool found;
	int prevState = 0, nextState = 0;
	string inputStr;
	int currentState[MAX_DFAS];
	int DFAcounter = 0;
	

	cout << "Enter a string ";
	cin >> inputStr;

	for (int i = 0; i < m_numDFAs; i++) {
		currentState[i] = 0;
	}

	for (unsigned i = 0; i < inputStr.size(); i++) {
		symbol = inputStr[i];
		found = false;

		for (int j = 0; j < m_dfas[0]->m_alphabetSize; j++) {
			if (symbol == m_dfas[0]->m_alphabet[j]) {
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
			DFAcounter = 0;
			for (int i = 0; i < m_numDFAs; i++) {
				for (auto iter = m_dfas[i]->m_DFAstates.begin(); iter != m_dfas[i]->m_DFAstates.end(); ++iter) {
					if ((*iter)->name == m_currentState[i]) {
						nextState = (*iter)->m_symbolicTransitions[symbol];
						break;
					}
				}
				m_currentState[DFAcounter++] = nextState;
			}

		}
	}
	bool accepted = true;
	for (int i = 0; i < m_numDFAs; i++) {
		if (!m_dfas[i]->m_finalState[m_currentState[i]]) {
			accepted = false;
			break;
		}
	}
	if (accepted)
		cout << "\n Accepted!! \n";
	else
		cout << "\n not Accepted!! \n";

}

void SetDFAOp::complementDFA() {
	char symbol;
	bool found;
	int prevState = 0, nextState = 0;
	string inputStr;
	int currentState = 0;
	int DFAcounter = 0;
	char ch;

	cout << "Enter a string ";
	cin >> inputStr;


	for (unsigned i = 0; i < inputStr.size(); i++) {
		symbol = inputStr[i];
		found = false;

		for (int j = 0; j < m_dfas[0]->m_alphabetSize; j++) {
			if (symbol == m_dfas[0]->m_alphabet[j]) {
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
				for (auto iter = m_dfas[0]->m_DFAstates.begin(); iter != m_dfas[0]->m_DFAstates.end(); ++iter) {
					if ((*iter)->name == currentState) {
						nextState = (*iter)->m_symbolicTransitions[symbol];
						break;
					}
				}
				currentState = nextState;
			}

		}
	
	bool accepted = true;
	if (m_dfas[0]->m_finalState[currentState]) {
		accepted = false;
	}
	if (accepted)
		cout << "\n Accepted!! \n";
	else
		cout << "\n not Accepted!! \n";

}

