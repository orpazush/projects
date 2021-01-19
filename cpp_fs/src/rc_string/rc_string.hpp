/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg     						         *
 * 					Last update : 3.8.20									 *
 ****************************************************************************/

#ifndef ILRD_RD8788_RC_STRING_HPP
#define ILRD_RD8788_RC_STRING_HPP

#include <iosfwd> // ostream

namespace ilrd
{

    class RCString
    {
    public:
        // might throw bad_alloc
        RCString(const char *str = ""); // non-explicit by intention
        ~RCString();
        RCString(const RCString &other);
        RCString &operator=(const RCString &str);

        char operator[](size_t index) const;
        // the function offers strong guarantee. might throw bad_alloc
        char &operator[](size_t index);

        const char *GetStr() const;
        size_t GetLength() const;

    private:
        struct RC
        {
            size_t counter;
            char str[1];
        };
        RC *m_rc;

        void CopyRc(const RCString &to_copy);
        void InitRc(const char *str); // might throw bad_alloc
    };

    std::ostream &operator<<(std::ostream &out, const RCString &str);

    bool operator==(const RCString &str1, const RCString &str2);
    bool operator!=(const RCString &str1, const RCString &str2);
    bool operator<(const RCString &str1, const RCString &str2);
    bool operator>(const RCString &str1, const RCString &str2);

} // namespace ilrd

#endif //ILRD_RD8788_RC_STRING_HPP
