#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include "buffer.h"
#include "hokuyoaist.h"

void buffer::put(hokuyoaist::ScanData& data)
{
    scoped_lock lock(mutex);
    if(full == BUF_SIZE)
    {
        p = 0;
        c = 0;
        full = 0;
    }
    buf[p] = data;
    p = (p + 1) % BUF_SIZE;
    full++;
    cond.notify_one();
}

hokuyoaist::ScanData buffer::get()
{
    scoped_lock lk(mutex);
    if(full == 0)
    {
        while(full == 0)
        cond.wait(lk);
    }
    hokuyoaist::ScanData result = buf[c];
    c = (c + 1) % BUF_SIZE;
    full--;
    return result;
}