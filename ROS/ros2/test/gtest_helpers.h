#include <gtest/gtest.h>
#include <sstream>

namespace testing
{
    namespace internal
    {
        extern void ColoredPrintf(GTestColor color, const char* fmt, ...);
    }
}
#define PRINTF(...)  do { testing::internal::ColoredPrintf(testing::internal::COLOR_GREEN, "[          ] "); testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, __VA_ARGS__); } while (0)

// C++ stream interface
class TestCout : public std::stringstream
{
public:
    ~TestCout()
    {
        printf("%s",str().c_str());
    }
};

#define TEST_COUT  TestCout()
