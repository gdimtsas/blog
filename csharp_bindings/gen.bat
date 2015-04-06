@echo off
mkdir csharp
swig -c++ -csharp -dllimport __Internal -outdir csharp -o CSharpBindings.cpp Engine.i