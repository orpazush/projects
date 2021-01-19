//
// Created by orpaz on 07/12/2020.
//

//You run an e-commerce website and want to record the last N order ids in a log. Implement a
//data structure to accomplish this, with the following API:
//• record(order_id): adds the order_id to the log
//• get_last(i): gets the ith last element from the log. i is guaranteed to be smaller than or
//equal to N.
//You should be as efficient with time and space as possible.


#include <cstddef>                 //size_t
#include <boost/noncopyable.hpp>   //boost::noncopyable

typedef size_t order_id_t;

template <size_t NUM_OF_RECORDS>
class OrdersLog : private boost::noncopyable
{
public:
    explicit OrdersLog();//default
 //   ~OrdersLog();//default

    void Record(order_id_t order_id);
    order_id_t GetLast(size_t idx) const;

private:
    order_id_t m_orders[NUM_OF_RECORDS];
    size_t m_lastOrderIdx;
};

template<size_t NUM_OF_RECORDS>
void OrdersLog<NUM_OF_RECORDS>::Record(order_id_t order_id)
{
    m_orders[m_lastOrderIdx] = order_id;
    m_lastOrderIdx = (m_lastOrderIdx+1) % NUM_OF_RECORDS;
}

template<size_t NUM_OF_RECORDS>
order_id_t OrdersLog<NUM_OF_RECORDS>::GetLast(size_t idx) const
{
    return m_orders[(m_lastOrderIdx - idx) % NUM_OF_RECORDS];
}

template<size_t NUM_OF_RECORDS>
OrdersLog<NUM_OF_RECORDS>::OrdersLog() : m_lastOrderIdx(0)
{
//    empty
}

int main()
{
    OrdersLog<10> test;

    return 0;
}
