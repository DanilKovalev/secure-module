#ifndef SECURE_MODULE_ROOTSESSION_H
#define SECURE_MODULE_ROOTSESSION_H

namespace secmode { namespace root {

class CRootSession
{
public:
    CRootSession();
    CRootSession(const CRootSession &);
    CRootSession(CRootSession &&);
    CRootSession& operator = (const CRootSession &);
    CRootSession& operator = (CRootSession &&);
    ~CRootSession();

    void start();
    void stop();
protected:
private:
    bool is_root = false;
};

} // namespace root
} // namespace secmode

#endif //SECURE_MODULE_ROOTSESSION_H
