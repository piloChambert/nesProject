@echo off

set CC65_HOME=C:\cc65
set name=main

.\extra\nsf2data.exe Resources\music\sounds.nsf -ca65
.\extra\text2data.exe Resources\music\music.txt -ca65
mv Resources\music\sounds.s .
mv Resources\music\music.s .

cc65 -Oi %name%.c --add-source -t nes
ca65 %name%.s
ca65 reset.s

ld65 -C %name%.cfg -o Drakaina.nes %name%.o reset.o nes.lib

del *.o

fceux Drakaina.nes
