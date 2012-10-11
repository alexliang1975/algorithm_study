/*
 * FiniteAutomata.cpp
 *
 */


#include <set>
#include <queue>
#include <utility>
#include "FiniteAutomata.h"
#include "state.h"

FiniteAutomata::FiniteAutomata() {
	// TODO Auto-generated constructor stub
	episilonZero = 0;
	episilonMany = 1;
	stateId = 2;
	start=NULL;
    for (char i = 0; i < 26; i++) {
        inputs[i] = (char) ('a' + i);
    }
}

FiniteAutomata::~FiniteAutomata() {
	// TODO Auto-generated destructor stub
}

StateSet FiniteAutomata:: move(StateSet &currentEpisilon, char input) {
		StateSet result ;
		StateSet ::iterator it;
        for (it=currentEpisilon.begin() ; it != currentEpisilon.end();it++) {
            State *next = it->getTransit(input);
            if (next != NULL) {
                result.insert(*next) ;
            }
        }
        return episilon(result);
}

bool FiniteAutomata:: containsAcceptState(StateSet nextEpisilon) {
	StateSet::const_iterator it;
	for (it=nextEpisilon.begin() ; it!=nextEpisilon.end();it++) {
        if (it->isAccept()) {
            return true;
        }
    }
    return false;
}
StateSet FiniteAutomata:: episilon( State *s){
	StateSet cache ;
    cache.insert(*s);
    return episilon(*s, cache);
}

StateSet FiniteAutomata:: episilon(StateSet &states) {
	StateSet cache ;
	StateSet::const_iterator it;
    for (it=states.begin() ; it!=states.end();it++) {
        cache.insert(*it);
        StateSet result =episilon(*it, cache);
        cache.insert(result.begin(),result.end());
    }
    return cache;
}

StateSet  FiniteAutomata:: episilon( const State &s, StateSet & cache){

	State *next = s.getTransit(this->episilonZero);
    if (next !=NULL  && cache.find(*next)==cache.end()) {
   		cache.insert(*next);
        episilon(*next, cache);
    }
	next = s.getTransit(this->episilonMany);
    if (next !=NULL  && cache.find(*next)==cache.end()) {
   		cache.insert(*next);
        episilon(*next, cache);
    }
    return cache;
}
State *FiniteAutomata:: nextState() {
	return new State(stateId++);
}

State *FiniteAutomata:: toNFA(string pattern) {
    State *currentState = nextState();
    State  * starter = currentState;

    for (size_t i =0;i<pattern.length();i++) {
    	char c =pattern[i];
        if (c == '.') {
            State *nextState = this->nextState();
            // add each transition for all inputs
            for (unsigned int n =0;n<sizeof(inputs);n ++) {
            	char i =inputs[n];
                currentState->setTransition(i, nextState);
            }
            currentState = nextState;
        } else if (c == '*') {
            State *nextState = this->nextState();
            // add each transition for all inputs
            for (unsigned int n =0;n<sizeof(inputs);n ++) {
            	char i = inputs[n];
                currentState->setTransition(i, nextState);
            }
            currentState->setTransition(episilonZero, nextState);
            nextState->setTransition(episilonMany, currentState);
            currentState = nextState;
        } else if (c >= 'a' && c <= 'z') {
            State * nextState = this->nextState();
            currentState->setTransition(c, nextState);
            currentState = nextState;
        } else {
            throw ("Unrecognized expression");
        }
    }
    currentState->setAccept(true);
    return starter;
}

State *FiniteAutomata::convertToDFA(State * NFA){

    map< StateSet, State *> cache ;
    queue< StateSet > queue ;

    // start state of DFA
    StateSet start = episilon(NFA);
    State *starter = nextState();
    starter->setAccept(NFA->isAccept());
    // put to cache map
    cache[start]=starter;

    queue.push(start);
    while (!queue.empty()) {

    	StateSet currentEpisilon = queue.front();
        queue.pop();

        map< StateSet, State *>::iterator current = cache.find(currentEpisilon);

        for (unsigned int i =0;i< sizeof(inputs); i++) {
        	char input =inputs[i];
        	StateSet nextEpisilon = move(currentEpisilon, input);
            if (nextEpisilon.empty() ) {
                continue;
            }
            map< StateSet, State *>::iterator nextIt=cache.find(nextEpisilon);
            if (nextIt==cache.end()) {
            	State * next = nextState();
                cache[nextEpisilon]= next;
                queue.push(nextEpisilon);
                nextIt=cache.find(nextEpisilon);
            }
            bool isAccept = containsAcceptState(nextEpisilon);
            nextIt->second->setAccept(isAccept);
            current->second->setTransition(input, nextIt->second);
        }
    }
    return starter;

}

void FiniteAutomata::compile(string  pattern) {
    this->stateId = 2;
    State *NFA = toNFA(pattern);
    this->start = convertToDFA(NFA);
}

bool FiniteAutomata:: match(string c) {
	State * t = start;
    for (unsigned int i=0;i<c.length();i++) {
    	char d =c[i];
    	t = t ->getTransit(d);
        if (t == NULL) {
            return false;
        }
    }
    return t->isAccept();
}

