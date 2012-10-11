/*
 * FiniteAutomata.h
 *
 */

#ifndef FINITEAUTOMATA_H_
#define FINITEAUTOMATA_H_
#include "state.h"
#include <set>
#include <queue>

typedef  set<State > StateSet;
class FiniteAutomata {
public:


	FiniteAutomata();
	virtual ~FiniteAutomata();
	bool match(string c) ;
	void compile(string  pattern) ;
private :
	State *start;
	char inputs[26];
	int episilonZero ;
	int episilonMany ;
	int stateId;


	State *convertToDFA(State *NFA);
	StateSet move(StateSet &currentEpisilon, char input);
	bool containsAcceptState(StateSet nextEpisilon) ;
	StateSet episilon(State *s);
	StateSet episilon(StateSet &states) ;
	StateSet episilon(const State &s, StateSet &cache);
	State *nextState() ;
	State *toNFA(string pattern) ;
};

#endif /* FINITEAUTOMATA_H_ */
