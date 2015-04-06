@echo off
swig -c++ -lua -o EngineLua.cpp Engine.i
swig -lua -external-runtime swig.h
