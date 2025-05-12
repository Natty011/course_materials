#!/bin/bash

echo "=== Symbol Table: no_opt.out ==="
nm no_opt.out | grep Square

echo
echo "=== Symbol Table: opt.out ==="
nm opt.out | grep Square
