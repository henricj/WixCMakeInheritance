#pragma once

#ifdef SOMESHAREDLIBRARY_BUILDING_DLL
#define SomeSharedLibraryDllExport   __declspec( dllexport )
#else
#define SomeSharedLibraryDllExport   __declspec( dllimport )
#endif

extern "C" 
SomeSharedLibraryDllExport
int DoSomething(int n);
