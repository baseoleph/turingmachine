#ifndef ACTION_H
#define ACTION_H

struct Action
{
    Action(): a(-1), q(-1), d(0) {}
    // new letter under machine
    int a = -1;
    // new machine's state
    int q = -1;
    // direct
    int d = 0;
};

#endif // ACTION_H
