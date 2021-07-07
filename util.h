#ifndef UTIL
#define UTIL

template<typename T>
inline void UNUSED_VAR(T const& var)
{
    static_cast<void>(var);
}

#endif /* UTIL */
