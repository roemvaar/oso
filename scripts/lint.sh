#!/bin/sh

cpplint --exclude=./test/Unity --filter=-legal/copyright,-whitespace/braces,-readability/casting,-build/include_subdir,-build/header_guard --linelength=120 \
    --quiet --recursive . &> "cpplint-$(date +%Y-%m-%d-%H-%M-%S).log"
