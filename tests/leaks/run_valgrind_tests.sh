#!/bin/sh
# Lance chaque scénario de leak_tests sous valgrind (4 en parallèle).
# Usage : run_valgrind_tests.sh <binaire leak_tests sans ASan> [scénario]

BIN="$1"
ONLY="$2"
DIR=$(dirname "$0")
LOGS="$DIR/build/valgrind_logs"
mkdir -p "$LOGS"

export SDL_AUDIODRIVER=dummy

if [ -n "$ONLY" ]; then
	TESTS="$ONLY"
else
	TESTS=$("$BIN")
fi

echo "Running under valgrind, this takes a while..."
for t in $TESTS; do echo "$t"; done | xargs -P4 -I{} sh -c \
	"valgrind --suppressions=valgrind.supp --leak-check=full --num-callers=20 $BIN {} > $LOGS/{}.log 2>&1"

failed=0
for t in $TESTS; do
	log="$LOGS/$t.log"
	errors=$(grep -o 'ERROR SUMMARY: [0-9]*' "$log" | grep -o '[0-9]*$')
	lost=$(grep -o 'definitely lost: [0-9,]* bytes' "$log" | grep -o '[0-9,]* bytes')
	printf "%-12s " "$t"
	if ! grep -q "thanks" "$log"; then
		echo "FAIL  (did not exit normally: $(grep -m1 'leak_tests:' "$log"))"
		failed=1
	elif [ "${errors:-1}" != "0" ] || { [ -n "$lost" ] && [ "$lost" != "0 bytes" ]; }; then
		echo "FAIL  ($errors errors, ${lost:-0 bytes} definitely lost)"
		failed=1
	else
		echo "OK"
	fi
done

echo
if [ $failed -ne 0 ]; then
	echo "Some tests failed. Full reports: $LOGS/"
	exit 1
fi
echo "All tests passed: no memory errors, no leaks."
