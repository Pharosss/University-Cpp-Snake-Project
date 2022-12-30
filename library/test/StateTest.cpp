#include <boost/test/unit_test.hpp>
#include "State.h" 
BOOST_AUTO_TEST_SUITE(StateTest)

BOOST_AUTO_TEST_CASE(Test_increment_score) {
    State s;    
    BOOST_CHECK_EQUAL(s.get_score(), 0);
    s.increment_score();
    BOOST_CHECK_EQUAL(s.get_score(), 1);
    }

BOOST_AUTO_TEST_CASE(Test_get_speed__set_speed) {
    State s;
    BOOST_CHECK_EQUAL(s.get_speed(), 0.5f);
    s.set_speed(5.5f);
    BOOST_CHECK_EQUAL(s.get_speed(), 5.5f);
    try{
        s.set_speed(-1.0f);
        BOOST_FAIL();
    }
    catch(const std::exception& e) {}
    }

BOOST_AUTO_TEST_CASE(Test_should_move) {
    State s;
    BOOST_CHECK_EQUAL(s.should_move(), false);
    s.set_should_move(true);
    BOOST_CHECK_EQUAL(s.should_move(), true);
    s.set_should_move(false);
    BOOST_CHECK_EQUAL(s.should_move(), false);
    }

BOOST_AUTO_TEST_CASE(Test_set_pause__is_paused) {
    State s;
    BOOST_CHECK_EQUAL(s.is_paused(), false);
    s.set_pause(true);
    BOOST_CHECK_EQUAL(s.is_paused(), true);
    s.set_pause(false);
    BOOST_CHECK_EQUAL(s.is_paused(), false);
    }

BOOST_AUTO_TEST_CASE(Test_set_pause__is_paused) {
    State s;
    BOOST_CHECK_EQUAL(s.is_paused(), false);
    s.set_pause(true);
    BOOST_CHECK_EQUAL(s.is_paused(), true);
    s.set_pause(false);
    BOOST_CHECK_EQUAL(s.is_paused(), false);
    }

BOOST_AUTO_TEST_CASE(Test_finish_game__is_finished) {
    State s;
    BOOST_CHECK_EQUAL(s.is_finished(), false);
    s.finish_game();
    BOOST_CHECK_EQUAL(s.is_finished(), true);
    }
BOOST_AUTO_TEST_SUITE_END()