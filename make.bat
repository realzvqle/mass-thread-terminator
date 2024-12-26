@echo off

cl src/*.c user32.lib /Fe:winsta.exe
del *.obj
