#include <boost/test/unit_test.hpp>
#include "Head.h"
#include <memory>
BOOST_AUTO_TEST_SUITE(HeadTest)

BOOST_AUTO_TEST_CASE(Test_attach) {
    Game* game;
    std::shared_ptr<Body>head=std::make_shared<Body>(1, 1, game);
    std::shared_ptr<Body>next=head.get_next();
    head.attach();
    //BOOST_CHECK_EQUAL(head.get_next(), ;
    }

    BOOST_AUTO_TEST_CASE(Test_attach) {
    Game* game;
    Head h;
    std::shared_ptr<Body>head=std::make_shared<Body>(1, 1, game);
    //std::shared_ptr<Body>next=head.get_next();
    h.attach(head);
    BOOST_CHECK_EQUAL(head.get_next(), !head);
    }
   
BOOST_AUTO_TEST_SUITE_END()