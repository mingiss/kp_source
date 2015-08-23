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
    HRESULT retc = KpsInit();
    if (FAILED(retc))
        cout << "Inicializavimo klaida" << endl;

    if (SUCCEEDED(retc))
    {
        retc = KpsTest();
        int prod_ver = GetProdVer();
        cout << "Produktas " << prod_ver << " " <<
            (SUCCEEDED(retc)? "" : "ne") << "uzregistruotas" << endl;

        HRESULT retc0 = KpsClose();
        if (SUCCEEDED(retc)) retc = retc0;
    }

    return retc;
}
