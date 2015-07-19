#ifndef MESSAGEIDGENERATOR_HPP
#define MESSAGEIDGENERATOR_HPP

#include <string>
#include <atomic>


class MessageIdGenerator
{
private:
    static std::atomic<uint64_t> id;

public:
    static std::string get();
};


#endif