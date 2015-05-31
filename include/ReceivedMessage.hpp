#ifndef RECEIVEDMESSAGE_HPP
#define RECEIVEDMESSAGE_HPP

#include <vector>

struct ReceivedMessage
{
public:
    std::vector<char> message;
    size_t length;
};

#endif // RECEIVEDMESSAGE_HPP