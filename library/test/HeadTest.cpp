#include <boost/test/unit_test.hpp>
#include "Head.h"
#include <memory>
BOOST_AUTO_TEST_SUITE(HeadTest)

BOOST_AUTO_TEST_CASE(Test_attach) {
    Game *game;
    Head head(1, 1, game);
    std::shared_ptr<Body>a=head.get_next();
    std::shared_ptr<Body>b=std::make_shared<Body>(2, 2, game);
    head.attach(b);
    //BOOST_CHECK_PREDICATE(a, head.attach(a));
    BOOST_CHECK_EQUAL(a, head.attach(a));
    BOOST_CHECK_PREDICATE(a, b);
    }

    /* BOOST_AUTO_TEST_CASE(Test_attach) {
    Game* game;
    Head h;
    std::shared_ptr<Body>head;
    //std::shared_ptr<Body>head=std::make_shared<Body>(1, 1, game);
    //std::shared_ptr<Body>head2=std::make_shared<Body>(1, 1, game);
    //std::shared_ptr<Body>next=head.get_next();
    head=h.get_next();
    head2==h.get_next();
    //BOOST_CHECK_EQUAL(h.get_next(), );
    BOOST_CHECK_EQUAL(head, head2);
    h.attach(head);
    BOOST_CHECK_PREDICATE(head, head2);
    } */
   
BOOST_AUTO_TEST_SUITE_END()