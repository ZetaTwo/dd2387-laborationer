#!/bin/bash
# Output a new C++ program that echoes every line of code to stdout.

# /^  / : Find lines that begin with two spaces
# {     : Begin a block of commands
# p     : Print the matched line
# ;     : And perform another command...
# s/^\(\s\+\)\([^;]*\)/ : Extract two parts of the line: 1: the leading
#         whitespace; 2: the following text until the first semicolon
# \1std::cout << "\2" << std::endl : And insert std::cout<<" before and "<<std::endl around the instruction
# }     : End the block of commands
sed '/^  /{p;s/^\(\s\+\)\([^;]*\)/\1std::cout << "\2" << std::endl/}' calendar_demo.cpp
