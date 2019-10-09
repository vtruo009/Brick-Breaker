# Test file for Lab2_introToAVR


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Add tests below
#empty
test "PINA: 0x00, PINB: 0x00 => PORTC: 0x04"
setPINA 0x00
setPINB 0x00
continue 2
expectPORTC 0x04
checkResult

#full
test "PINA: 0x0F, PINB: 0x00 => PORTC: 0x80"
setPINA 0x0F
setPINB 0x00
continue 2
expectPORTC 0x80
checkResult

#3 spaces
test "PINA: 0x01, PINB: 0x00 => PORTC: 0x03"
setPINA 0x01
setPINB 0x00
continue 2
expectPORTC 0x03
checkResult

test "PINA: 0x08, PINB: 0x00 => PORTC: 0x03"
setPINA 0x08
setPINB 0x00
continue 2
expectPORTC 0x03
checkResult

#2 spaces
test "PINA: 0x03, PINB: 0x00 => PORTC: 0x02"
setPINA 0x03
setPINB 0x00
continue 2
expectPORTC 0x02
checkResult

test "PINA: 0x0A, PINB: 0x00 => PORTC: 0x02"
setPINA 0x0A
setPINB 0x00
continue 2
expectPORTC 0x02
checkResult

#1 space
test "PINA: 0x07, PINB: 0x00 => PORTC: 0x01"
setPINA 0x07
setPINB 0x00
continue 2
expectPORTC 0x01
checkResult

test "PINA: 0x0E, PINB: 0x00 => PORTC: 0x01"
setPINA 0x0E
setPINB 0x00
continue 2
expectPORTC 0x01
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
