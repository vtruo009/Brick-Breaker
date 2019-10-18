echo ======================================================\n
echo Running all tests..."\n\n

#incrementing
test "PINA: 0x00, 0x01 => PORTC: 0x01, ID_State: ID_Incr"
set ID_State = ID_SMStart
setPINA 0x00
continue 2
setPINA 0x01
continue 1
expectPORTC 0x01
expect ID_State ID_Incr
checkResult

test "PINA: 0x00, 0x01 => PORTC: 0x01, ID_State: ID_HoldIncr"
set ID_State = ID_SMStart
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTC 0x01
expect ID_State ID_HoldIncr
checkResult

test "PINA: 0x00, 0x01, 0x00, 0x01 => PORTC: 0x02, ID_State: ID_Incr"
set ID_State = ID_SMStart
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
expect ID_State ID_Incr
expectPORTC 0x02
checkResult

#***********************incrementing when PORTC = 0x09******************************
test "PINA: 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01 => PORTC: 0x09, ID_State: ID_Incr"
set ID_State = ID_SMStart
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
expectPORTC 0x09
expect ID_State ID_Incr
checkResult

#decrementing
#************************decrementing when PORTC = 0x00*********************
test "PINA: 0x02 => PORTC: 0x00, ID_State: ID_Decr"
set ID_State = ID_SMStart
setPINA 0x02
continue 2
expectPORTC 0x00
expect ID_State ID_Decr
checkResult

test "PINA: 0x01, 0x00, 0x01, 0x00, 0x02 => PORTC: 0x01, ID_State: ID_Decr"
set ID_State = ID_SMStart
setPINA 0x01
continue 2
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x02
continue 1
expectPORTC 0x01
expect ID_State ID_Decr
checkResult

test "PINA: 0x01, 0x00, 0x01, 0x00, 0x02 => PORTC: 0x01, ID_State: ID_HoldDecr"
set ID_State = ID_SMStart
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x02
continue 2
expectPORTC 0x01
expect ID_State ID_HoldDecr
checkResult

#reset
test "PINA: 0x01, 0x00, 0x01, 0x00, 0x01, 0x03 => PORTC: 0x00, ID_State: ID_Reset"
set ID_State = ID_SMStart
setPINA 0x01
continue 2
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x03
continue 1
expectPORTC 0x00
expect ID_State ID_Reset
checkResult


test "PINA: 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x03 => PORTC: 0x00, ID_State: ID_Reset"
set ID_State = ID_SMStart
setPINA 0x01
continue 2
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x03
continue 1
expectPORTC 0x00
expect ID_State ID_Reset
checkResult

test "PINA: 0x01, 0x00, 0x01, 0x00, 0x03 => PORTC: 0x00, ID_State: ID_HoldReset"
set ID_State = ID_SMStart
setPINA 0x01
continue 2
setPINA 0x00
continue 1
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x03
continue 5
expectPORTC 0x00
expect ID_State ID_HoldReset
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
© 2019 GitHub, Inc.
