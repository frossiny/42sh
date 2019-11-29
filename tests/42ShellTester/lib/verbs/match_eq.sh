#!/bin/bash

# /*
# Test exit status
# EXPECTED_TO_ARGS[0]* -> expected exit status (integer)
# RESPONSE_EXIT_STATUS -> actual exit status
# */

run_verb_match_eq()
{
	while IFS= read -r line; do
		if [ $line == ${EXPECTED_TO_ARGS[0]} ]
		then
			return 0
		fi
	done < ${RESPONSE}
	return 1
}
