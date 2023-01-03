#include <boost/test/unit_test.hpp>
#include "Body.h" 
#include <memory>
BOOST_AUTO_TEST_SUITE(BodyTest)

BOOST_AUTO_TEST_CASE(Test_is_tail__attach) {
    //Body b(1, 1);
    Body body(1, 1);
    BOOST_CHECK_EQUAL(body.is_tail(), false);

    body.attach(std::make_shared<Body>(2,7));
    BOOST_CHECK_EQUAL(body.is_tail(), true);

    /* Body* b;
    BOOST_CHECK_EQUAL(b.is_at_recursive(b.get_x(), b.get_y()), true);
    //BOOST_CHECK_EQUAL(next.is_at_recursive(b.get_x, b.get_y), true);
    Body body;
    body.move_recursive(1, 2);
    BOOST_CHECK_EQUAL(b.is_at_recursive(b.get_x(), b.get_y()), true);
    */}

   BOOST_AUTO_TEST_CASE(Test_recursive) {
    std::shared_ptr<Body>next;

    next->move_recursive(1, 2);
    BOOST_CHECK_EQUAL(next->is_at_recursive(next->get_x()-1, next->get_y()-2), true);

    Body* body;    
    BOOST_CHECK_EQUAL(body->get_tail_recursive(), body);
    }
    
BOOST_AUTO_TEST_SUITE_END()