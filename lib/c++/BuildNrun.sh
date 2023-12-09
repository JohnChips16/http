#!/bin/bash

# Check if the executable exists
if [ ! -f "./MyHTTP" ]; then
    echo "Building C++ code..."
    g++ -o "./MyHTTP" "$(dirname "$0")/http_server.cpp"
fi

# Run the compiled program with the specified port argument
if [ -f "./MyHTTP" ]; then
    if [ "$#" -ne 1 ]; then
        echo "Usage: $0 <port>"
        exit 1
    fi

    PORT="$1"
    echo "Running ./MyHTTP on port $PORT..."
    "./MyHTTP" "$PORT"
else
    echo "Error: Unable to build ./MyHTTP"
    exit 1
fi
