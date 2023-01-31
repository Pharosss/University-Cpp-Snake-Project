#include <boost/test/unit_test.hpp>
#include "entities/Head.h"
#include <memory>

#include "entities/Body.h"
BOOST_AUTO_TEST_SUITE(HeadTest)

BOOST_AUTO_TEST_CASE(Test_attach) {
    
    Game *game;
    Head head(uvec2(1, 1), game);
    auto a = std::make_shared<Body>(uvec2(2, 2));

    BOOST_CHECK_EQUAL(head.get_next(), nullptr);

    head.attach(a);

    BOOST_CHECK_EQUAL(head.get_next(), a);

    }

   
BOOST_AUTO_TEST_SUITE_END()