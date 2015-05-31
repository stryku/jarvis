#ifndef RECEIVEDMESSAGE_HPP
#define RECEIVEDMESSAGE_HPP

#include <vector>

class ReceivedMessage
{
private:
    static const size_t defaultVectorLength = 5 * 1024;

public:
    ReceivedMessage() : length( 0 )
    {
        message.resize( defaultVectorLength );
    }
    ~ReceivedMessage() {}

    std::vector<char> message;
    size_t length;
};

#endif // RECEIVEDMESSAGE_HPP