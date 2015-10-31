#ifndef SECURE_MODULE_ROOTMODULE_H
#define SECURE_MODULE_ROOTMODULE_H

#include <unistd.h>

namespace secmode { namespace root {

struct SUids{
    uid_t ruid;
    uid_t euid;
    uid_t suid;
};

class CRootModule {
public:
    friend class CRootSession;

    static void init();

    static SUids get_uids();
protected:
    static void capture_root();
    static void release_root();
private:
};

} // namespace root
} // namespace secmode

#endif //SECURE_MODULE_ROOTMODULE_H
