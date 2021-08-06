template <class T>
inline const T& Max(const T& a, const T& b)
{
    return a < b ? b : a;
}