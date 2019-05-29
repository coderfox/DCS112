#include <algorithm>

using std::swap;

namespace myNamespace
{
template <typename T>
void swap(T &v1, T &v2)
{
    ::swap(v1, v2);
}
}; // namespace myNamespace