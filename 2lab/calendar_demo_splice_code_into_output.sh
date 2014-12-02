#!/bin/bash
# Output a new C++ program that echoes every line of code to stdout.

# /^  / : Find lines that begin with two spaces
# {     : Begin a block of commands
# h     : Copy the matched line to hold space
# s/^\(\s\+\)\([^;]*\)/ : Extract two parts of the line: 1: the leading
#         whitespace; 2: the following text until the first semicolon
# \1std::cout << "\2" << std::endl : And insert std::cout<<" before and "<<std::endl around the instruction
# G     : Append hold space to pattern space (which now contains our replaced line)
# }     : End the block of commands
sed '/^  /{
h;
s/^\(\s\+\)\([^;]*\)/\1std::cout << "\2" << std::endl/;
G;
}' calendar_demo.cpp
