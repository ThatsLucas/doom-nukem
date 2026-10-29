#!/bin/sh
# Lance chaque scénario de leak_tests et vérifie qu'il n'y a ni fuite ni erreur mémoire.
# Usage : run_leak_tests.sh <binaire leak_tests> [scénario]

BIN="$1"
ONLY="$2"
DIR=$(dirname "$0")
LOGS="$DIR/build/logs"
mkdir -p "$LOGS"

export SDL_AUDIODRIVER=dummy
export ASAN_OPTIONS="detect_leaks=1:fast_unwind_on_malloc=0"
export LSAN_OPTIONS="suppressions=$DIR/lsan.supp:print_suppressions=0"

if [ -n "$ONLY" ]; then
	TESTS="$ONLY"
else
	TESTS=$("$BIN")
fi

failed=0
for t in $TESTS; do
	log="$LOGS/$t.log"
	printf "%-12s " "$t"
	"$BIN" "$t" > "$log" 2>&1
	code=$?
	if grep -q "ERROR: AddressSanitizer" "$log"; then
		echo "FAIL  (memory error: $(grep -m1 'ERROR: AddressSanitizer' "$log" | sed 's/.*AddressSanitizer: //'))"
		failed=1
	elif grep -q "ERROR: LeakSanitizer" "$log"; then
		echo "FAIL  ($(grep -m1 'SUMMARY:' "$log" | sed 's/SUMMARY: AddressSanitizer: //'))"
		# première fonction du projet dans chaque fuite
		grep -E "^    #[0-9]+ .* (srcs|libft|tests)/" "$log" | grep -vE "in (main|start_game|test_[a-z_]+) " \
			| awk '{ $1=""; $2=""; print "      "$0 }' | sort | uniq -c | sort -rn | head -8
		failed=1
	elif [ $code -ne 0 ]; then
		echo "FAIL  (exit code $code: $(grep -m1 'leak_tests:' "$log"))"
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
echo "All tests passed: no leaks."
