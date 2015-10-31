#include "RootSession.h"

#include "RootModule.h"

using namespace secmode::root;

CRootSession::CRootSession() {
    start();
}


CRootSession::CRootSession(const CRootSession &session)
{
    if(session.is_root) {
        start();
    }
}

CRootSession::CRootSession(CRootSession &&session) {
    is_root = session.is_root;
    session.is_root = false;
}

CRootSession& CRootSession::operator=(const CRootSession &session)
{
    stop();
    if(session.is_root) {
        start();
    }

    return *this;
}

CRootSession &CRootSession::operator=(CRootSession &&session)
{
    stop();
    is_root = session.is_root;
    session.is_root = false;

    return *this;
}

CRootSession::~CRootSession()
{
    stop();
}

void CRootSession::start()
{
    if(!is_root){
        CRootModule::capture_root();
    }

    is_root = true;
}

void CRootSession::stop()
{
    if(is_root) {
        CRootModule::release_root();
    }

    is_root = false;
}

