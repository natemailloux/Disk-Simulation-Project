//
//

#ifndef QUEUE_HPP
#define QUEUE_HPP
class Request;

class Queue {

public:
    virtual void addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector) = 0;
    virtual Request *getRequest() = 0;
    virtual bool empty() = 0;
    virtual void print() = 0;
    virtual ~Queue() {}
    virtual int size() = 0;
    virtual int headTrack() = 0;
    virtual int headSector() = 0;
    virtual Request *headReq() = 0;
    virtual int headNum() = 0;

};

#endif // QUEUE_HPP
