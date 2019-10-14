echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x01, 0x00, 0x01 => PORTB: 0x01, ID_State: LED_OFFPress"
set ID_State = ID_SMStart
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x01
expect ID_State LED_OFFPress
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
© 2019 GitHub, Inc.
