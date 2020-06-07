#include "Source1.h"

extern "C"
SomeSharedLibraryDllExport
int DoSomething(int n)
{
    return n + 1;
}
