#!/usr/bin/env bash

# Exit immediately if a command exits with a non-zero status
set -e

# =====================================================================
# 1. SETUP EXAMPLE VARIABLES (Replace these with your actual inputs)
# =====================================================================

# Initialize our destination lists as empty strings
first_tests=""
second_tests=""

echo "--------------------------------------------------"
echo "Modified Targets to check: $modified_targets"
echo "--------------------------------------------------"

# =====================================================================
# 2. QUERY CTEST AND LOOP THROUGH EACH TEST
# =====================================================================
for test_name in $test_names:
  do
    # Skip empty lines or the ctest summary lines (like "Total Tests: X")
    [ -z "$test_name" ] && continue

    # =====================================================================
    # 3. CHECK IF THE TEST NAME IS IN MODIFIED_TARGETS
    # =====================================================================
    # We use a regex match inside [[ ]] to look for the exact word boundary
    # to prevent partial word matches (e.g., catching "test_math" inside "test_math_advanced")
    if [[ " $modified_targets " =~ [[:space:]]${test_name}[[:space:]] ]]; then
        # Append to the string (adding a space delimiter if it's not the first item)
        if [ -z "$first_tests" ]; then first_tests="$test_name"; else first_tests="$first_tests $test_name"; fi
    else
        if [ -z "$second_tests" ]; then second_tests="$test_name"; else second_tests="$second_tests $test_name"; fi
    fi
  done


# =====================================================================
# 4. PRINT THE FINAL RESULTS
# =====================================================================
echo "$first_tests"
echo "###" #delimiter
echo "$second_tests"

