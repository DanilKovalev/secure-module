#include "RootModule.h"

#include <string.h>

#ifndef NO_THREAD
    #include <mutex>
    std::mutex root_mtx;
#endif

#define ROOT_ID 0

using namespace secmode::root;

size_t  root_count = 0;

static inline void switch_to_user_mode();
static inline void switch_to_root_mode();

void CRootModule::init() {
    SUids uids = get_uids();

    if(uids.ruid != ROOT_ID && uids.euid != ROOT_ID && uids.suid != ROOT_ID) {
        throw std::runtime_error("Unable to find root id in user ids");
    }

    switch_to_user_mode();
}

SUids CRootModule::get_uids()
{
    SUids uids;

    if(getresuid(&uids.ruid, &uids.euid, &uids.suid)) {
        std::string err = "Unable get to get user ids";
        err += ",error[" + std::to_string(errno) + "]";
        err += strerror(errno);
        throw std::runtime_error(err);
    }

    return uids;
}

void CRootModule::capture_root()
{
#ifndef NO_THREAD
    std::lock_guard<std::mutex> lock(root_mtx);
#endif

    if(root_count != 0) {
        root_count++;
        return;
    }

    switch_to_root_mode();
    root_count = 1;
}

void CRootModule::release_root() {
#ifndef NO_THREAD
    std::lock_guard<std::mutex> lock(root_mtx);
#endif

    if(root_count != 1) {
        --root_count;
        return;
    }

    switch_to_user_mode();
    root_count = 0;
}

static void switch_to_user_mode()
{
    if ( seteuid(getuid()) )
    {
        std::string err = "Unable get to release root mode";
        err += ",error[" + std::to_string(errno) + "]";
        err += strerror(errno);
        throw std::runtime_error(err);
    }
}

static void switch_to_root_mode()
{
    if (seteuid(ROOT_ID)) {
        std::string err = "Unable get to capture root mode";
        err += ",error[" + std::to_string(errno) + "]";
        err += strerror(errno);
        throw std::runtime_error(err);
    }
}

