#!/bin/bash

# ./checker.sh <exec> [-c <cluster_num>]

EXECUTABLE=$1
shift

pattern="test/*.in.*"

if [[ "$1" == "-c" ]]; then
  if [[ -z "$2" ]]; then
    echo "Error: -c requires a number argument."
    exit 1
  fi
  pattern="test/*.in.$2*"
  shift 2
fi

for f in $pattern
do
  if [[ "$f" == *".dummy"* ]]; then
    continue
  fi

  echo "$f"
  ./"$EXECUTABLE" < "$f" > a1out
  ./checker actor1 "$f" "${f/\.in\./\.con\.}" a1out a2in
  ./"$EXECUTABLE" < a2in > a2out
  ./checker actor2 "$f" "${f/\.in\./\.con\.}" a1out a2in a2out
done

