#include <boost/test/unit_test.hpp>
#include "Board.h" 
BOOST_AUTO_TEST_SUITE(BoardTest)

BOOST_AUTO_TEST_CASE(Test_position_valid) {
    Board b=Board(10, 10);
    BOOST_CHECK_EQUAL(b.is_position_valid(9, 9), true);
    BOOST_CHECK_EQUAL(b.is_position_valid(8, 6), true);
    BOOST_CHECK_EQUAL(b.is_position_valid(11, 13), false);
    /* Board b;
    BOOST_CHECK_EQUAL(b.is_position_valid(b.get_width(), b.get_height()), 1);
    BOOST_CHECK_EQUAL(b.is_position_valid(b.get_width()-1, b.get_height()-1), 1);
    BOOST_CHECK_EQUAL(b.is_position_valid(b.get_width()+1, b.get_height()+1), 0);*/
    }

BOOST_AUTO_TEST_SUITE_END()