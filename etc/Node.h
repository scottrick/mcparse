#ifndef _NODE_
#define _NODE_

class PosQuat;

class Node
{
public:
    Node();
    virtual ~Node();

protected:


private:

    PosQuat pq;
};

#endif