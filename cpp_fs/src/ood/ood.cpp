/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : chanan komar     						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#include <cstddef>      //size_t
#include <dirent.h>     //opendir
#include <iostream>     //cout

#include "ood.hpp"

using namespace std;

namespace ilrd
{
size_t Directory::s_m_level = 0;
const string BLUE = "\x1B[34m";
const string UNBLUE = "\x1B[0m";

Block::Block(const string& name) : m_name(name)
{
    // empty
}

Block::~Block()
{
    // empty
}

Directory::Directory(const string& path) : Block(path.substr(path.find_last_of('/') + 1))
{
    DIR *dir = opendir(path.c_str());
    if (NULL == dir)
    {
        throw (runtime_error("invalid read"));
    }
    for (struct dirent *entry = readdir(dir); NULL != entry; 
         entry = readdir(dir))
    {
        if (*entry->d_name != '.')
        {
            try
            {
                if (DT_DIR == entry->d_type)
                {
                    m_vblocks.push_back(new Directory(path + "/" + entry->d_name));
                }
                else
                {
                    m_vblocks.push_back(new File(entry->d_name));
                }                
            }
            catch (exception&)
            {
                closedir(dir);
                this->~Directory();
                throw;
            }        
        }    
    }
    closedir(dir);
}   

Directory::~Directory()
{
    while (!m_vblocks.empty())
    {
        delete m_vblocks.back();
        m_vblocks.pop_back();
    }
}

void Directory::DisplayName()
{
    vector<Block *>::iterator i;
    cout << "├──" << BLUE
         << GetName() << UNBLUE << endl;
    ++s_m_level;
    for (i = m_vblocks.begin(); i != m_vblocks.end(); ++i)
    {
        for (size_t f =0; f < s_m_level; ++f)
        {
            cout << "│   ";
        }

        (*i)->DisplayName();
    }
    --s_m_level;
}

string Block::GetName() const
{
    return m_name;
}

File::File(const string& name) : Block(name)
{
    // empty
}

File::~File()
{
    // empty
}

void File::DisplayName()
{
    cout << "├──" << GetName() << endl;
}
}//ilrd


    
