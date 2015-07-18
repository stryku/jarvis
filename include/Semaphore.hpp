#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    using native_handle_type = std::condition_variable::native_handle_type;

    explicit Semaphore( size_t n = 0 )
        : count{ n }
    {}
    Semaphore( const Semaphore& ) = delete;
    Semaphore& operator=( const Semaphore& ) = delete;

    void notify( )
    {
        std::lock_guard<std::mutex> lock{ mutex };
        ++count;
        cv.notify_one();
    }

    void wait( )
    {
        std::unique_lock<std::mutex> lock{ mutex };
        cv.wait( lock, [&] { return count > 0; } );
        --count;
    }

    template<class Rep, class Period>
    bool wait_for( const std::chrono::duration<Rep, Period>& d )
    {
        std::unique_lock<std::mutex> lock{ mutex };
        auto finished = cv.wait_for( lock, d, [&] { return count > 0; } );

        if( finished )
            --count;

        return finished;
    }

    template<class Clock, class Duration>
    bool wait_until( const std::chrono::time_point<Clock, Duration>& t )
    {
        std::unique_lock<std::mutex> lock{ mutex };
        auto finished = cv.wait_until( lock, t, [&] { return count > 0; } );

        if( finished )
            --count;

        return finished;
    }

    native_handle_type native_handle( )
    {
        return cv.native_handle( );
    }

private:
    size_t                  count;
    std::mutex              mutex;
    std::condition_variable cv;
};

#endif