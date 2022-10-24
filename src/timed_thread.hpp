#include <condition_variable>
#include <thread>

class ThreadFlag {
    mutable std::mutex flag_mutex;
    mutable std::condition_variable flag_change;
    bool flag;

public:
    ThreadFlag();

    bool is_true() const;

    /// @return Previous value of flag.
    bool set_true();

    /**
     * Blocks the thread until the flag is 'set_true' or when the absolute
     * time point (timeout_time_point) is reached.
     * @return Value of flag.
     */
    template <typename Clock, typename Period>
    bool wait_until_true(const std::chrono::time_point<Clock, Period>& timeout_time_point) const;
};

ThreadFlag::ThreadFlag()
    : flag(false)
{
}

bool ThreadFlag::is_true() const
{
    std::lock_guard<std::mutex> lock(flag_mutex);
    return flag;
}

bool ThreadFlag::set_true()
{
    bool previous_flag;
    
    {
        std::lock_guard<std::mutex> lock(flag_mutex);
        previous_flag = flag;
        flag = true;
    }
    
    flag_change.notify_all();
    
    return previous_flag;
}

template <typename Clock, typename Period>
bool ThreadFlag::wait_until_true(const std::chrono::time_point<Clock, Period>& timeout_time_point) const
{
    std::unique_lock<std::mutex> lock(flag_mutex);
    return flag_change.wait_until(lock, timeout_time_point, [this] { return flag; });
}
