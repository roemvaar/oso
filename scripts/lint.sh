#!/bin/sh

cpplint --filter=-legal/copyright,-whitespace/braces,-readability/casting,-build/include_subdir,-build/header_guard --linelength=120 \
    --quiet --recursive . &> "cpplint-$(date +%Y-%m-%d-%H-%M-%S).log"
