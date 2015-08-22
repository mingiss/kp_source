// ---------------
// kpsttun.cpp
// produkto licencijos naikinimo per libkpsttrg.a pavyzdys
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
        (SUCCEEDED(retc)? "" : "ne") << "uzregistruotas." << endl;

    retc = KpsUnReg();
    cout << "Produkto " << prod_ver << " licencija " <<
        (SUCCEEDED(retc)? "" : "ne") << "panaikinta." << endl;
    return 0;
}
