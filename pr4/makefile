environ : environ.c
	g++ environ.c

help : environ.c
	./a.out --help

set : environ.c
	./a.out --set "SHELL=HELLO"

assign : environ.c
	./a.out --assign "SHELL" --value "NEW_VALUE"

delete : environ.c
	./a.out --del "SHELL"

printenvs : environ.c
	./a.out

clear : environ.c
	./a.out --clear
