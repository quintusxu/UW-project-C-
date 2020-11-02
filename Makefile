# example4/Makefile
CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -MMD -g
OBJECTS=main.o basicenemy.o character.o dragonhoard.o drow.o  dwarf.o elf.o enemy.o floor.o goblin.o halfling.o item.o mascot.o orcs.o player.o potion.o shade.o treasure.o troll.o turtle.o vampire.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

TESTDIR=test
EXECSDIR=../executables
EXECGIVEN=${EXEC}
SUITE=suiteq1.txt

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean

# @ silences output
test:
	@cp ${EXECSDIR}/${EXECGIVEN} ${TESTDIR}                 # copy over given exec
	@mv ${TESTDIR}/${EXECGIVEN} ${TESTDIR}/sol_${EXECGIVEN} # prefix it with sol_
	@cp ${EXEC} ${TESTDIR}                                  # copy over your exec
	@(cd ${TESTDIR}\							    # go into test directory
	&& ./produceOutputs ${SUITE} ./sol_${EXECGIVEN}\        # run produceOutputs
	&& ./runSuite ${SUITE} ./${EXEC})                       # run runSuite
.PHONY: test

