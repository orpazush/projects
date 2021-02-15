/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						                     *
 * 					Last update : 15.9.20									 *
 ****************************************************************************/

#ifndef ILRD_RD8788_DEMULTIPLEXER_HPP
#define ILRD_RD8788_DEMULTIPLEXER_HPP

#include <vector> // vector

namespace ilrd
{

class Demultiplexer
{
public:
    enum MODE
    {
        READ = 0,
        WRITE,
        EXCEPT
    };

//    explicit Demultiplexer(); //default
//    ~Demultiplexer();         //default

    std::vector<std::pair<int, MODE> > MonitorEvents(
            const std::vector<std::pair<int, MODE> > &pair_vector);

//private:
//    void setReadysVector(*)
//
};

namespace demultiplexer_details
{
    typedef std::pair<int, Demultiplexer::MODE> key_t;
    typedef std::vector<key_t> vector_pair_t;
} //demultiplexer_details

}//ilrd
#endif //ILRD_RD8788_DemULTIPLEXER_HPP
