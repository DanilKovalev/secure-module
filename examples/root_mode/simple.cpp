#include <iostream>
#include <stdexcept>

#include "secmod.h"
#include "root/RootSession.h"

using namespace std;
using namespace secmode::root;

void print_uids(SUids uids)
{
    cout << "real      user id: " << uids.ruid << endl;
    cout << "save      user id: " << uids.suid << endl;
    cout << "effective user id: " << uids.euid << endl;
}

int main () {
    cout << "uids when program start:" << endl;
    print_uids(CRootModule::get_uids());

    try {
        CRootModule::init();
    } catch (std::exception& e) {
        std::cerr << e.what() << endl;
        cerr << "try command :" << endl << "sudo chown root root_mode_simple && sudo chmod +s root_mode_simple" << endl;
        return 1;
    }

    cout << endl;
    cout << "uids after root module initialized:" << endl;
    print_uids(CRootModule::get_uids());

    cout << endl;
    cout << "create root session object" << endl;
    CRootSession rootSession;

    cout << "uids after root session created:" << endl;
    print_uids(CRootModule::get_uids());



    cout << endl;
    cout << "stop root session" << endl;
    rootSession.stop();

    cout << "uids after root session stoppped:" << endl;
    print_uids(CRootModule::get_uids());

    return 0;
}
