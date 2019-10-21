echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x01 => PORTC: 0x60"
setPINA 0x01
continue 2
expectPORTC 0x60
checkResult

test "PINA: 0xFC => PORTC: 0x3E"
setPINA 0xFC
continue 2
expectPORTC 0x3E
checkResult

test "PINA: 0x07 => PORTC: 0x3C"
setPINA 0x07
continue 2
expectPORTC 0x3C
checkResult

test "PINA: 0x00 => PORTC: 0x00"
setPINA 0x00
continue 2
expectPORTC 0x00
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
© 2019 GitHub, Inc.
