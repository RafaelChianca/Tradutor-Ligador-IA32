TRIA: EQU 1

SECTION TEXT
		INPUT		B
		INPUT		H
		LOAD		B
		MULT		H
		IF TRIA
		DIV		DOIS
		STORE		R
		OUTPUT	R
		STOP

SECTION DATA
	B:		SPACE	4
	H:		SPACE
	R:		SPACE
	DOIS:	CONST		2
