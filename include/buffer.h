#ifndef _BUFFER_
#define _BUFFER_

#include "hokuyoaist.h"

typedef boost::mutex::scoped_lock scoped_lock;
const int BUF_SIZE = 5;

class buffer
{
public:
    buffer(): p(0), c(0), full(0){}

    void put(hokuyoaist::ScanData& data);

    hokuyoaist::ScanData get();

private:
    boost::mutex mutex;
    boost::condition cond;
    unsigned int p, c, full;
    hokuyoaist::ScanData buf[BUF_SIZE];
};

#endif