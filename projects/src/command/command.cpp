/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#include "command.hpp"
#include "logger.hpp"           //LOG_..

namespace ilrd
{
namespace project
{
//
///* -------------------------------Read Methods------------------------------ */
//ReplyPtr Read::Execute(Storage<BLOCK_SIZE> *storage, RequestPtr request)
//{
//    ReplyPtr reply = CreateReplyPtr();
//    reply->requestType = request->requestType;
//    reply->requestUID = request->requestUID;
//    reply->errorStatus = SUCCESS;
//
//    try
//    {
//        storage->Read(reply->block, request->blockIndex);
//    }
//    catch (std::exception&)
//    {
//        LOG_ERROR("Read fail to read from storage");
//        reply->errorStatus = READ_ERROR;
//    }
//
//    return reply;
//}
//
//Command *Read::Create()
//{
//    return (new Read);
//}
//
//Read::~Read()
//{
////empty
//}
//
///* -------------------------------Write Methods----------------------------- */
//ReplyPtr Write::Execute(Storage<BLOCK_SIZE> *storage, RequestPtr request)
//{
//    ReplyPtr reply = CreateReplyPtr();
//    reply->requestType = request->requestType;
//    reply->requestUID = request->requestUID;
//    reply->errorStatus = SUCCESS;
//
//    try
//    {
//        storage->Write(request->block, request->blockIndex);
//    }
//    catch (std::exception&)
//    {
//        LOG_ERROR("Write fail to write to storage");
//        reply->errorStatus = WRITE_ERROR;
//    }
//
//    return reply;
//}
//
//Command *Write::Create()
//{
//    return (new Write);
//}
//
//Write::~Write()
//{
////empty
//}

/* -------------------------------Command Dtor------------------------------ */
Command::~Command()
{
//empty
}


} //project
} //ilrd

