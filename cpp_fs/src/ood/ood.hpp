/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : chanan komar     						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_OOD_HPP
#define ILRD_RD8788_OOD_HPP

#include <string>   //string
#include <vector>   // vector

using namespace std;

namespace ilrd
{
class Block
{
public:
    explicit Block(const string& name);
    virtual ~Block();
    virtual void DisplayName()=0;

protected:
    string GetName() const;

private:
    string m_name;
};

class Directory : public Block
{
public:
    explicit Directory(const string& path);
    virtual ~Directory();
    virtual void DisplayName();

private:
    static std::size_t s_m_level;
    vector <Block *> m_vblocks;
};

class File : public Block
{
public:
    explicit File(const string& name);
    virtual ~File();
    virtual void DisplayName();
};
}//ilrd

#endif //ILRD_RD8788_OOD_HPP
