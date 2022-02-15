@echo off
latex %~n1.tex
dvisvgm --font-format=woff --clipjoin --bbox=papersize --page=1- %~n1.dvi

