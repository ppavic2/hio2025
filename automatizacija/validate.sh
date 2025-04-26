#!/usr/bin/env bash
set -euo pipefail

for infile in test/*.in*; do
  config="${infile/in/con}"
  a1out="${infile/in/a1out}"
  a2in="${infile/in/a2in}"

  ./automatizacija < "$infile" > "$a1out"
  ./checker actor1 "$infile" "$config" "$a1out" "$a2in" > /dev/null
  echo "$infile ready"
done

./validate3_con.py test/*.con*
./validate3.py test/*.in*
./validate3.py --actor2 test/*.a2in*

rm -f test/*.a1out*
