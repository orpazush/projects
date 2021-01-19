/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Elimelech Billet            					 *
 * 					Last update : 30.9.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_MINION_HPP
#define ILRD_RD8788_MINION_HPP

#include <cstddef>               // size_t
#include <boost/noncopyable.hpp> // noncopyable

#include "vdr_protocol.hpp"      //ReplyPtr, RequestPtr..
#include "reactor.hpp"           //m_reactor
#include "storage.hpp"           //m_storage
#include "communicator.hpp"      //m_communicator
#include "factory.hpp"           //m_factory
#include "command.hpp"           //Command

namespace ilrd
{
namespace project
{


class Minion : private boost::noncopyable
{
public:
    explicit Minion(int minion_port, size_t num_of_blocks, const char *ip, int port);
    ~Minion();//default

	template<typename COMMAND>
    void AddCommand(uint8_t key);

	void Run();
    void Stop();//TODO

private:
    void OnRequest();
    void ExtractIndex(RequestPtr req) const;
    ReplyPtr ExecuteReq(RequestPtr req);
    void Ack(ReplyPtr req) noexcept;

    Communicator m_communicator;
    Reactor m_reactor;
    Storage<BLOCK_SIZE> *m_storage;
    Factory<Command, uint8_t>m_commandsFactory;
    size_t m_numOfBlocks;
};

template<typename COMMAND>
void Minion::AddCommand(uint8_t key)
{
    m_commandsFactory.Add(key, &COMMAND::Create);
}

/////////////////////////////////Minion Commands////////////////////////////////
class Read : public Command
{
public:
    // Read(); //default
    ~Read();

    ReplyPtr Execute(Storage<BLOCK_SIZE> *storage, RequestPtr req);
    static Command *Create();
};//Read

class Write : public Command
{
public:
    // Write(); //default
    ~Write();

    ReplyPtr Execute(Storage<BLOCK_SIZE> *storage, RequestPtr req);
    static Command *Create();
};//Write

}// namespace ilrd
} // namespace minion

#endif //ILRD_RD8788_MINION_HPP