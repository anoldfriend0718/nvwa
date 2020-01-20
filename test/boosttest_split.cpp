#include "nvwa/split.h"
#include <string_view>
#include <boost/test/unit_test.hpp>

constexpr std::string_view str{
    "&grant_type=client_credential&appid=&secret=APPSECRET"};

std::vector<std::string> split_result_expected{
    "",
    "grant_type=client_credential",
    "appid=",
    "secret=APPSECRET"
};

BOOST_AUTO_TEST_CASE(split_test)
{
    constexpr auto result = nvwa::split(str, '&');
    constexpr auto end = result.end();
    auto result_s = result.to_vector();
    auto result_sv = result.to_vector_sv();
    BOOST_CHECK(result_s == split_result_expected);
    BOOST_CHECK_EQUAL(result_s.size(), result_sv.size());
    if (result_s.size() == result_sv.size()) {
        auto it = result_sv.begin();
        for (auto& s : result_s) {
            BOOST_CHECK_EQUAL(s, *it);
            ++it;
        }
    }
    size_t i = 0;
    auto it = result.begin();
    for (; it != end && i < result_s.size(); ++it) {
        BOOST_CHECK_EQUAL(*it, result_s[i]);
        if (!result_s[i].empty()) {
            BOOST_CHECK_EQUAL(nvwa::split(*it, '=').to_vector_sv().size(),
                              2U);
        }
        ++i;
    }
    BOOST_CHECK(it == end);
}
