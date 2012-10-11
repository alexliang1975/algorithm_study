/*
 * state.h
 *
 */

#ifndef STATE_H_
#define STATE_H_
#include <map>
#include <ostream>
#include <string>
using namespace std;




class State {
public:
	typedef map<char , State *> StateMap;
private:
	bool accept;
	int id;
	StateMap mapping;
public:
	State();
	State(int ch);
	virtual ~State();
	char getId(){ return id;};
	State *getTransit(char input) const ;
	void setTransition(char input, State *next) ;
	void setTransition(StateMap mapping);
	bool isAccept() const;
	void setAccept(bool b);
	bool operator ==( State const & rhs) const;
	bool operator < (State const &rhs) const;
	operator char () const ;
	operator string() const;
	friend ostream& operator<<(ostream& out, const State & vec);
};

#endif /* STATE_H_ */
