#ifndef IOF_MT_GUARD_H
#define IOF_MT_GUARD_H
#include <iostream>

namespace ignatov
{
    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        std::basic_ios< char >& s_;
        std::streamsize width_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };
}
#endif /* IOF_MT_GUARD_H */
