#include <boost/test/unit_test.hpp>
#include "Food.h"
BOOST_AUTO_TEST_SUITE(FoodTest)

BOOST_AUTO_TEST_CASE(Test_is_food) {
    Food food = Food(1, 1);
    BOOST_CHECK_EQUAL(food.is_food(), true);
    }
   
BOOST_AUTO_TEST_SUITE_END()