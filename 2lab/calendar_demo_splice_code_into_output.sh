#!/bin/bash
# Output a new C++ program that echoes every line of code to stdout.

# /^  / : Find lines that begin with two spaces
# {     : Begin a block of commands
# h     : Copy the matched line to hold space
# s/"/\\"/g; : Replace all occurrences of " with \"
# s/^\(\s\+\)\([^;]*\)/ : Extract two parts of the line: 1: the leading
#         whitespace; 2: the following text
# \1std::cout << " > \2" << std::endl : And insert std::cout<<" before and "<<std::endl around
#         the instruction, and prefix the instruction line with " > " in the output
# G     : Append hold space to pattern space (which now contains our replaced line)
# }     : End the block of commands
sed '/^  /{
h;
s/"/\\"/g;
s/^\(\s\+\)\(.*\)/\1std::cout << " > \2" << std::endl;/;
G;
}' calendar_demo.cpp
