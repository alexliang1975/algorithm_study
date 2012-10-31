Write a parser for a simplified regular expression 

	On an alphabet set [a-z], a simplified regular expression is much simpler than the normal regular expression.
It has only two meta characters: '.' and '*'.

	'.' -- exact one arbitrary character match.

	'*' -- zero or more arbitrary character match.

some example:


pattern 	value	result


------------------------------

ab.*d 		abcd	true

ab.*d 		abccd	true

ab.*d		abad	true

ab.*d		abc		false

ab.*d		''		false

ab.*d		abd		false
		 
Two solutions are provided:

1. Finite automaton State ( FiniteAutomata.cpp & State.cpp).

2. isMatch recursive function

Also a gtest unittest suite is provided, for the test result, the isMatch function is amazing.  
