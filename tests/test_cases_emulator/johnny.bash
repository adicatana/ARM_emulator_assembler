#!/bin/bash
function runCommandForFiles {
	for file in *
	do
		valgrind --tool=memcheck --leak-check=full ./emulate $file
	done
}
runCommandForFiles;
