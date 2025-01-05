#!/bin/sh

writefile=$1
writestr=$2

# Validate arguments
if [ $# -lt 2 ]
then
    echo "Error: Missing required arguments"
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

# Create directory path if needed
dir_path=$(dirname "$writefile")
mkdir -p "$dir_path" || {
    echo "Error: Failed to create directory path"
    exit 1
}

# Write content to file
echo "$writestr" > "$writefile" || {
    echo "Error: Failed to write to file"
    exit 1
}

exit 0