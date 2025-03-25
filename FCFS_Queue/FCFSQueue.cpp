#include "FCFSQueue.hpp"
#include "../CommonFiles/Request.hpp"

void FCFSQueue::addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector) {
    FCFSQueueNode *rNode = new FCFSQueueNode(orderValue, request);
    if( empty() ) {
        head = tail = rNode;
    } else {
        tail->next(rNode);
        tail = rNode;
    }
}

Request *FCFSQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling FCFSQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    FCFSQueueNode *fcfsNode = head;
    Request *request = fcfsNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete fcfsNode;
    return request;
}


bool FCFSQueue::empty() {
    return head == nullptr;
}

void FCFSQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

FCFSQueue::~FCFSQueue() {
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}

int FCFSQueue::size() {

    if ( empty() )
        return 0;

    FCFSQueueNode * iter = head;
    int count = 0;
    while ( iter ) {
        count++;
        iter = iter->next();
    }
    return count;

}


int FCFSQueue::headTrack() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD TRACK\n";
        exit(10);
    }
    return head->request()->track();

}


int FCFSQueue::headSector() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD SECTOR\n";
        exit(10);
    }
    return head->request()->sector();

}


Request *FCFSQueue::headReq() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    return head->request();

}

int FCFSQueue::headNum() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    return head->num();

}
