/*============================================================================
// Name        : regExp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Write a parser for a simplified regular expression
// On an alphabet set [a-z], a simplified regular expression is much simpler than the normal regular expression.
// It has only two meta characters: '.' and '*'.
// '.' -- exact one arbitrary character match.
// '*' -- zero or more arbitrary character match.
//============================================================================*/

#include <iostream>
#include "FiniteAutomata.h"
#include <gtest/gtest.h>
using namespace std;

int main(int argc, char * argv[]) {
	testing::InitGoogleTest(&argc, argv);
	 return RUN_ALL_TESTS();
}
