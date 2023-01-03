#include <boost/test/unit_test.hpp>
#include "Game.h"
#include <vector>
#include <memory>
BOOST_AUTO_TEST_SUITE(GameTest)

BOOST_AUTO_TEST_CASE(Test_attach_entity__detach_entity) {
    Game game(Board(10, 10), State());
    //std::vector<std::shared_ptr<Entity>> entities;
    std::shared_ptr<Entity> entity;
    game.attach_entity(entity);
    try{
        game.attach_entity(entity);
        BOOST_FAIL();
    }
    catch(const std::exception& e) {}
    //BOOST_CHECK_EQUAL(entities.size(), 1);
   
    game.detach_entity(entity);
    try{
        game.detach_entity(entity);
        BOOST_FAIL();
    }
    catch(const std::exception& e) {}
    //BOOST_CHECK_EQUAL(entities.size(), 0);
    }
   
BOOST_AUTO_TEST_SUITE_END()