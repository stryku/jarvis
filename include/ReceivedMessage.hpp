#ifndef RECEIVEDMESSAGE_HPP
#define RECEIVEDMESSAGE_HPP

#include <vector>

class ReceivedMessage
{
private:
    static const size_t defaultVectorLength = 5 * 1024;

    std::array<char, defaultVectorLength> data;
    size_t length;
public:
    ReceivedMessage() : length( 0 ) {}
    ~ReceivedMessage() {}

    char* data() const
    {
        return data.data( );
    }

    size_t maxLength() const
    {
        return defaultVectorLength;
    }
};

#endif // RECEIVEDMESSAGE_HPP