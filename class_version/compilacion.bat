rem "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

cl.exe /c game.cc
cl.exe /c main.cc

cl.exe *.obj /Feparcheesi.exe