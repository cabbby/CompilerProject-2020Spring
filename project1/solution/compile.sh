#!/bin/bash
flex exp.lex
bison -d exp.y
mv lex.yy.c lex.yy.cc
mv exp.tab.c exp.tab.cc