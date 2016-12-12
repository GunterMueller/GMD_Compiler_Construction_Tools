@echo off
if exist yyyyyyyy.c del yyyyyyyy.c
ren %1 yyyyyyyy.c
cpp -lang-c -P yyyyyyyy.c -o %1
del yyyyyyyy.c
