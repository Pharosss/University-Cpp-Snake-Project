#include <boost/test/unit_test.hpp>
#include "core/State.h" 
BOOST_AUTO_TEST_SUITE(StateTest)

BOOST_AUTO_TEST_CASE(Test_increment_score) {
    State s;
    BOOST_CHECK_EQUAL(s.get_score(), 0);
    s.increment_score();
    BOOST_CHECK_EQUAL(s.get_score(), 1);
    }

BOOST_AUTO_TEST_CASE(Test_get_speed__set_speed) {
    State s;
    s.set_speed(5.5f);
    BOOST_CHECK_EQUAL(s.get_speed(), 5.5f);
    try{
        s.set_speed(-1.0f);
        BOOST_FAIL("Negative speed test failed");
    }
    catch(const std::exception& e) {}
    }

BOOST_AUTO_TEST_CASE(Test_should_move) {
    State s;
    BOOST_CHECK_EQUAL(s.get_flag(SHOULD_MOVE), false);

    s.set_flag(SHOULD_MOVE, true);
    BOOST_CHECK_EQUAL(s.get_flag(SHOULD_MOVE), true);

    s.set_flag(SHOULD_MOVE, false);
    BOOST_CHECK_EQUAL(s.get_flag(SHOULD_MOVE), false);
    }

BOOST_AUTO_TEST_CASE(Test_finish_game__is_finished) {
    State s;
    BOOST_CHECK_EQUAL(s.get_flag(IS_FINISHED), false);

    s.set_flag(IS_FINISHED, true);
    BOOST_CHECK_EQUAL(s.get_flag(IS_FINISHED), true);
    }
BOOST_AUTO_TEST_SUITE_END()