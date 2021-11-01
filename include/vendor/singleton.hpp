#pragma once

template<typename T>
class c_singleton
{
protected:
    c_singleton() {}
    ~c_singleton() {}

    c_singleton(const c_singleton&) = delete;
    c_singleton& operator=(const c_singleton&) = delete;

    c_singleton(c_singleton&&) = delete;
    c_singleton& operator=(c_singleton&&) = delete;

public:
    static T& get()
    {
        static T instance{};
        return instance;
    }
};