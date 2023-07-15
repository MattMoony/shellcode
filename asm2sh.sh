#!/bin/bash

# credit to https://www.commandlinefu.com/commands/view/6051/get-all-shellcode-on-binary-file-from-objdump
objdump -d "$1" | grep '[0-9a-f]:' | grep -v 'file' | cut -f2 -d: | cut -f1-7 -d' ' | tr -s ' ' | tr '\t' ' ' | sed 's/ $//g' | sed 's/ /\\x/g' | paste -d '' -s | sed 's/^/"/' | sed 's/$/"/g'
