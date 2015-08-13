#include <MessageIdGenerator.hpp>
std::atomic<uint64_t> MessageIdGenerator::id;


std::string MessageIdGenerator::get( )
{
    return "SERVER." + std::to_string( id++ );
}