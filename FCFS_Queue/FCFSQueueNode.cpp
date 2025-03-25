#include "FCFSQueueNode.hpp"

class Request;

FCFSQueueNode::FCFSQueueNode(int orderValue, Request *req) : _request(req), _next(nullptr), _num(orderValue) {}

FCFSQueueNode *FCFSQueueNode::next() {
    return _next;
}

void FCFSQueueNode::next(FCFSQueueNode *node) {
    _next = node;
}

Request *FCFSQueueNode::request() {
    return _request;
}
