// StudentAttendanceAnalyzer by MarZon
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "Menu.h"

using std::wcout;
using std::cin;
using std::endl;

int main()
{
    _setmode(_fileno(stdout), _O_U8TEXT);

    Menu menuObj;
    
    menuObj.openMainMenu();
    
    return 0;
}