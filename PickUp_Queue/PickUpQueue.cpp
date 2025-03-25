#include "PickUpQueue.hpp"
#include "../CommonFiles/Request.hpp"
#include "../FCFS_Queue/FCFSQueue.hpp"


/***
 * This checks if a queue is empty
 * @return true if it is empty (head node is null), false if not
 */
bool PickUpQueue::empty() {
    return head == nullptr;
}


/***
 * De-constructor for the pick-up queue
 */
PickUpQueue::~PickUpQueue() {

    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = head->next();
        delete node;
    }

}

/***
 *  This func determines if you are inserting a node that is before the cur head node
 *  based off where the R/W head is and the head node
 *  for the sake of readability, this was split into two if statements instead of one
 * @param rNode the given node
 * @param headTrack the track where the RW head is
 * @return
 */
bool PickUpQueue::beforeHead(FCFSQueueNode * rNode, int headTrack) {

    if ( headTrack == rNode->request()->track() && rNode->request()->track() != head->request()->track())
        return true;
    if (( headTrack < head->request()->track() && rNode->request()->track() > headTrack && rNode->request()->track() < head->request()->track() )
         || ( headTrack > head->request()->track() && rNode->request()->track() < headTrack && rNode->request()->track() > head->request()->track()))
        return true;
    return false;

}


/***
 * this func finds the last node of a set track, this ensures that duplicate
 * track nodes are ordered by First Come First Serve
 * @param node the node to be inserted
 * @param rNode the current node in the queue
 */
void PickUpQueue::findLastDuplicate(FCFSQueueNode * node, FCFSQueueNode * rNode) {

    while (node->next() && node->next()->request()->track() == rNode->request()->track() )
        node = node->next();
    // checks to see if you will be inserting a new node as the tail
    if (node == tail) {
        tail->next(rNode);
        tail = rNode;
    }
    else {
        rNode->next(node->next());
        node->next(rNode);
    }

}


/***
 * this checks if the node (rNode) is between the current two nodes in either increasing/decreasing fashion
 * @param iter the current node in the queue
 * @param rNode the node to be inserted
 * @return true if it is between two requests, false if not
 */
bool PickUpQueue::betweenNodes(FCFSQueueNode* iter, FCFSQueueNode* rNode) {

    if ((iter->request()->track() <= rNode->request()->track() && rNode->request()->track() <= iter->next()->request()->track() )
        || (iter->request()->track() >=rNode->request()->track() && iter->next()->request()->track() <= rNode->request()->track() )) {
        return true;
    }
    return false;

}


/***
 * This function inserts a request into the queue
 * @param orderValue the value of the request
 * @param request the request to be added
 * @param cRWHeadTrack current track of the RW head
 * @param cRWHeadSector current sector of the RW head
 */
void PickUpQueue::addRequest(int orderValue, Request *request, int cRWHeadTrack, int cRWHeadSector) {

    // create a new request node
    auto *rNode = new FCFSQueueNode(orderValue, request);
    if( empty() ) {
        head = tail = rNode;
    }
    else {
        // if the node will become the new head node
        if (beforeHead(rNode, cRWHeadTrack)) {
            rNode->next(head);
            head = rNode;
        }
        else {

            FCFSQueueNode *iter = head;
            while (iter->next()) {

                // if the node is between the current two nodes ( increase/decrease )
                if (betweenNodes(iter, rNode)) {

                    if (iter->next()->request()->track() == rNode->request()->track() && iter->next())
                        findLastDuplicate(iter, rNode);
                    else {
                        rNode->next(iter->next());
                        iter->next(rNode);
                    }
                    return;
                }
                iter = iter->next();
            }
            tail->next(rNode);
            tail = rNode;
        }


    }



}


/***
 * This retrieves a request from the queue and deletes it after return the request
 * @return the request from the head node
 */
Request *PickUpQueue::getRequest() {
    if( empty()  ) {
        std::cout << "Calling PickUpQueue::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    FCFSQueueNode *pickNode = head;
    Request *request = pickNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete pickNode;
    return request;

}

/***
 * This prints the contents of the queue
 */
void PickUpQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}


/***
 * This function counts the amt of the nodes in a queue
 * @return the count
 */
int PickUpQueue::size() {

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


int PickUpQueue::headTrack() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD TRACK\n";
        exit(10);
    }
    return head->request()->track();

}


int PickUpQueue::headSector() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD SECTOR\n";
        exit(10);
    }
    return head->request()->sector();

}


Request *PickUpQueue::headReq() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    return head->request();

}


int PickUpQueue::headNum() {

    if (empty()) {
        std::cout << "ERROR WITH HEAD REQ\n";
        exit(10);
    }
    return head->num();

}