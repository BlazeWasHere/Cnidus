#!/usr/bin/env bash

for file in bin/*; do
    printf "\ntesting ${file}...\n\n"
    ./"$file"
done