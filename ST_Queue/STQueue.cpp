#include "STQueue.hpp"
#include "../CommonFiles/Request.hpp"
#include "STQueueNode.hpp"

STQueueNode * STQueue::createNewQ(int orderValue, Request* request, int cRWHeadTrack, int cRWHeadSector) {

    auto * q = new FCFSQueue;
    q->addRequest(orderValue, request, cRWHeadTrack, cRWHeadSector);
    auto * rNode = new STQueueNode(request->track(), q);
    return rNode;

}


void STQueue::addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector) {

    if( empty() ) {
        STQueueNode * rNode = createNewQ(orderValue, request, cRWHeadTrack, cRWHeadSector);
        head = tail = rNode;
    }
    else if (request->track() == cRWHeadTrack && head->track() != cRWHeadTrack){
        STQueueNode * rNode = createNewQ(orderValue, request, cRWHeadTrack, cRWHeadSector);
        rNode->next(head);
        head = rNode;
    }
    else {

        STQueueNode * iter = head;
        while ( iter->next() ) {
            if ( iter->track() == request->track()) {
                iter->getQ()->addRequest(orderValue, request, cRWHeadTrack, cRWHeadSector);
                return;
            }
            iter = iter->next();

        }
        STQueueNode * rNode = createNewQ(orderValue, request, cRWHeadTrack, cRWHeadSector);
        tail->next(rNode);
        tail = rNode;

    }
}


Request *STQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    STQueueNode *STNode = head;
    Request *request = STNode->getQ()->getRequest();
    if (STNode->getQ()->empty()) {
        head = head->next();
        delete STNode;
    }
    if ( head == nullptr)
        tail = nullptr;
    return request;
}


bool STQueue::empty() {
    return head == nullptr;
}


void STQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->getQ()->print();
}


STQueue::~STQueue() {

    while( head != nullptr ) {
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}


int STQueue::size() {

    if (!head)
        return 0;

    STQueueNode * iter = head;
    int count = 0;

    while (iter) {
        count += iter->getQ()->size();
        iter = iter->next();
    }

    return count;

}

int STQueue::headTrack() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD TRACK\n";
        exit(10);
    }
    return head->getQ()->headTrack();

}


int STQueue::headSector() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD SECTOR\n";
        exit(10);
    }
    return head->getQ()->headSector();

}

Request *STQueue::headReq() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    return head->getQ()->headReq();

}


int STQueue::headNum() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    return head->getQ()->headNum();

}