#!/bin/bash

# /*
# Test exit status
# EXPECTED_TO_ARGS[0]* -> expected exit status (integer)
# RESPONSE_EXIT_STATUS -> actual exit status
# */

run_verb_match_eq()
{
  if [ `grep ${EXPECTED_TO_ARGS[0]} ${RESPONSE}` == "${EXPECTED_TO_ARGS[0]}" ]
  then
    return 0
  else
    return 1
  fi
}
