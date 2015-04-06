@echo off
swig -c++ -csharp -dllimport __Internal -outdir E:\projects\blog\build\Engine -o CSharpBindings.cpp Engine.i