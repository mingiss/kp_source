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
    HRESULT retc = KpsInit();
    if (FAILED(retc))
        cout << "Inicializavimo klaida" << endl;

    if (SUCCEEDED(retc))
    {
        int prod_ver = GetProdVer();
        retc = KpsUnReg();
        cout << "Produkto " << prod_ver << " licencija " <<
            (SUCCEEDED(retc)? "" : "ne") << "panaikinta." << endl;

        HRESULT retc0 = KpsClose();
        if (SUCCEEDED(retc)) retc = retc0;
    }
    
    return retc;
}
