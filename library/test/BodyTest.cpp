#include <boost/test/unit_test.hpp>
#include "Body.h" 
#include <memory>
BOOST_AUTO_TEST_SUITE(BodyTest)

BOOST_AUTO_TEST_CASE(Test_) {
    //Body b(1, 1);
    std::shared_ptr<Body>next;
    BOOST_CHECK_EQUAL(next.is_tail(), false);
    next.attach(next);
    BOOST_CHECK_EQUAL(next.is_tail(), true);
    Body* b;
    BOOST_CHECK_EQUAL(b.is_at_recursive(b.get_x, b.get_y), true);
    //BOOST_CHECK_EQUAL(next.is_at_recursive(b.get_x, b.get_y), true);
    Body body;
    body.move_recursive(1, 2);
    BOOST_CHECK_EQUAL(b.is_at_recursive(b.get_x, b.get_y), true);
   }


   BOOST_AUTO_TEST_CASE(Test_) {

    std::shared_ptr<Body>next;

    next.move_recursive(1, 2);
    BOOST_CHECK_EQUAL(next.is_at_recursive(next.get_x, next.get_y), true);
    }
    
BOOST_AUTO_TEST_SUITE_END()