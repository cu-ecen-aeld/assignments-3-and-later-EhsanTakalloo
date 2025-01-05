#!/bin/sh

filesdir=$1
searchstr=$2

if [ $# -lt 2 ]
then
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

if [ ! -d "$filesdir" ]
then
    echo "Directory $filesdir does not exist"
    exit 1
fi

# Count total files
X=$(find "$filesdir" -type f | wc -l)

# Count matching lines
Y=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"