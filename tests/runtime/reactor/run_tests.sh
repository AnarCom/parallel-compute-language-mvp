#!/bin/bash

# Script to build and run all runtime reactor tests

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Runtime Reactor Test Suite${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$SCRIPT_DIR/../../.."

# Create build directory
BUILD_DIR="$PROJECT_ROOT/build"
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Configure with CMake
echo -e "${YELLOW}Configuring with CMake...${NC}"
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Build the tests
echo -e "${YELLOW}Building tests...${NC}"
cmake --build . --target test_lifecycle test_firing_model test_events test_error_handler test_integration

echo ""
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Running Tests${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

# Array to track test results
declare -a test_results
declare -a test_names

# Function to run a test
run_test() {
    local test_name=$1
    local test_path="$BUILD_DIR/$test_name"
    
    if [ ! -f "$test_path" ]; then
        echo -e "${RED}ERROR: Test executable not found: $test_path${NC}"
        return 1
    fi
    
    echo -e "${YELLOW}Running $test_name...${NC}"
    if "$test_path"; then
        echo -e "${GREEN}✓ $test_name PASSED${NC}"
        test_results+=("PASS")
        test_names+=("$test_name")
        return 0
    else
        echo -e "${RED}✗ $test_name FAILED${NC}"
        test_results+=("FAIL")
        test_names+=("$test_name")
        return 1
    fi
}

# Run all tests
all_passed=true

run_test "test_lifecycle" || all_passed=false
echo ""

run_test "test_firing_model" || all_passed=false
echo ""

run_test "test_events" || all_passed=false
echo ""

run_test "test_error_handler" || all_passed=false
echo ""

run_test "test_integration" || all_passed=false
echo ""

# Print summary
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Test Summary${NC}"
echo -e "${BLUE}========================================${NC}"

passed_count=0
failed_count=0

for i in "${!test_names[@]}"; do
    if [ "${test_results[$i]}" == "PASS" ]; then
        echo -e "${GREEN}✓ ${test_names[$i]}${NC}"
        ((passed_count++))
    else
        echo -e "${RED}✗ ${test_names[$i]}${NC}"
        ((failed_count++))
    fi
done

echo ""
echo -e "Total: ${#test_names[@]} tests"
echo -e "${GREEN}Passed: $passed_count${NC}"
if [ $failed_count -gt 0 ]; then
    echo -e "${RED}Failed: $failed_count${NC}"
fi

echo ""
if $all_passed; then
    echo -e "${GREEN}========================================${NC}"
    echo -e "${GREEN}  ALL TESTS PASSED! ✓${NC}"
    echo -e "${GREEN}========================================${NC}"
    exit 0
else
    echo -e "${RED}========================================${NC}"
    echo -e "${RED}  SOME TESTS FAILED! ✗${NC}"
    echo -e "${RED}========================================${NC}"
    exit 1
fi
