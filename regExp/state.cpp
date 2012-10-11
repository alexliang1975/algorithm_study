/*
 * state.cpp
 *
 */

#include "state.h"
using namespace std;

State::State(){
	this->accept = false;
	this->id = 0;
}
State::State(int stateId) {
	// TODO Auto-generated constructor stub
	this->accept=false;
	this->id = stateId;
}

State::~State() {
	// TODO Auto-generated destructor stub
}

State *State::getTransit(char input) const {
	StateMap::const_iterator it =  mapping.find(input);
	if(it == mapping.end() ){
		return NULL;
	}else{
		return it->second;
	}
}

void State::setTransition(char input, State *next){
	this->mapping[input]=next;
}

void State::setTransition(StateMap mapping){
	this->mapping = mapping;
}

bool State::isAccept() const{
	return this->accept;
}
void State::setAccept(bool b){
	this->accept=b;
}
bool State:: operator ==( State const & rhs) const{
    return (id != rhs.id);
}
bool State:: operator <( State const & rhs) const{
    return (id < rhs.id);
}

State:: operator char () const {
	return this->id;
}
State::operator string () const {
	string t = string (1,this->id);
	return t;
}

ostream& operator<<(ostream& out, const State & vec){
		out << "State [id=" << vec.id << "]";
		return out;
};


