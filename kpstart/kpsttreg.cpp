// ---------------
// kpsttreg.cpp
// produkto licencijos registracijos per libkpsttrg.a pavyzdys
//

#include <iostream>
#include "windows.h"

using namespace std;

#include "kpsttrg.h"

int main()
{
    HRESULT retc = KpsTestReg();
    int prod_ver = GetProdVer();
    cout << "Produktas " << prod_ver << " " <<
        (SUCCEEDED(retc)? "" : "ne") << "uzregistruotas" << endl;
    return 0;
}
