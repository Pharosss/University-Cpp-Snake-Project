#include <boost/test/unit_test.hpp>
#include "Body.h" 
#include <memory>

BOOST_AUTO_TEST_SUITE(BodyTest)

BOOST_AUTO_TEST_CASE(Test_is_tail__attach) {
    //Body b(1, 1);
    Body body(1, 1);
    BOOST_CHECK_EQUAL(body.is_tail(), true);

    body.attach(std::make_shared<Body>(2,7));
    BOOST_CHECK_EQUAL(body.is_tail(), false);
}

BOOST_AUTO_TEST_CASE(Test_recursive) {
    
    // Snake orientation

    // 0 1 2 3 4
    // _ _ # # # before
    // _ # # # _ after

    auto seg1 = std::make_shared<Body>(2,0);
    auto seg2 = std::make_shared<Body>(3,0);    seg1->attach(seg2);
    auto seg3 = std::make_shared<Body>(4,0);    seg2->attach(seg3);

    BOOST_CHECK_EQUAL(seg1->is_at_recursive(1, 0), false);
    BOOST_CHECK_EQUAL(seg1->is_at_recursive(4, 0), true);

    seg1 -> move_recursive(1, 0);

    BOOST_CHECK_EQUAL(seg1->is_at_recursive(1,0), true);
    BOOST_CHECK_EQUAL(seg1->is_at_recursive(4,0), false);

    Body* body = new Body(0, 0);
    BOOST_CHECK_EQUAL(body->get_tail_recursive(), body);
    delete body;
}
    
BOOST_AUTO_TEST_SUITE_END()