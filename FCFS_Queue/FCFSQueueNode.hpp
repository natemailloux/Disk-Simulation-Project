//
//

#ifndef FCFS_QUEUE_FCFSQUEUENODE_HPP
#define FCFS_QUEUE_FCFSQUEUENODE_HPP


class Request;

class FCFSQueueNode {
public:
    FCFSQueueNode(int orderValue, Request *req);
    FCFSQueueNode *next();
    void next(FCFSQueueNode *node);
    Request *request();

    int num() { return _num; }

private:
    FCFSQueueNode *_next;
    Request *_request;
    int _num;
};


#endif //FCFS_QUEUE_FCFSQUEUENODE_HPP
