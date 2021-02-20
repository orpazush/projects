/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :                 						         *
 * 					Last update : 12.10.20									 *
 ****************************************************************************/

#ifndef ILRD_RD8788_COMMAND_HPP
#define ILRD_RD8788_COMMAND_HPP

#include <boost/noncopyable.hpp>        //noncopyable

#include "vdr_protocol.hpp"
#include "storage.hpp"

//#include "ilrd_details.hpp"


namespace ilrd
{
namespace project
{


class Command: private boost::noncopyable
{
public:
    // Command(); //default
    //virtual ~Command()=0;//TODO

    // who ever inherit this class, must declare static func Create()
    // static Command *Create();
    virtual ReplyPtr Execute(Storage<BLOCK_SIZE> *storage, RequestPtr req) =0;
};


//command (interface)
//
//class Read : public Command
//{
//public:
//    // Command(); //default
//    ~Read();
//
//    virtual ReplyPtr Execute(Storage<BLOCK_SIZE> *storage, RequestPtr req);
//    static Command *Create();
//};//Read
//
//class Write : public Command
//{
//public:
//    // Command(); //default
//    ~Write();
//
//    ReplyPtr Execute(Storage<BLOCK_SIZE> *storage, RequestPtr req);
//    static Command *Create();
//};//Write


} //project
} //ilrd

#endif // ifdef ILRD_RD8788_COMMAND_HPP
