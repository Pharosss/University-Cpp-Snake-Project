#include <boost/test/unit_test.hpp>
#include "Head.h"
#include <memory>

#include "Body.h"
BOOST_AUTO_TEST_SUITE(HeadTest)

BOOST_AUTO_TEST_CASE(Test_attach) {
    
    
    /*
    Game *game;
    Head head(1, 1, game);  // <- Tworzysz głowę, ale po niej nic nie ma
    std::shared_ptr<Body> a = head.get_next();  // <- Bierzesz adres 'segmentu' węża po jego głowie (którego nie ma, więc a = nullptr) 
    std::shared_ptr<Body> b = std::make_shared<Body>(2, 2, game);   // <- Tworzysz segment, no problemo mi amiga
    head.attach(b); // <- dołączasz segment do głowy

    // teraz masz Głowę i head.get_next() powinien zwracać b
    // Ale a jest wciąż = nullptr

    BOOST_CHECK_EQUAL(a, head.attach(a));   // ( nie mówiąc o tym, że attach() zwraca void, więc to nie ma sensu )
    BOOST_CHECK_PREDICATE(a, b);

    */


    // Więc zamiast tego ^, masz:

    Game *game;
    Head head(1, 1, game);
    auto a = std::make_shared<Body>(2, 2); // auto bywa przydatne, łatwiej odczytać kod

    // W tym momencie Head jest 'sam'

    BOOST_CHECK_EQUAL(head.get_next(), nullptr);

    head.attach(a);

    // Teraz Head ma dołączony segment

    BOOST_CHECK_EQUAL(head.get_next(), a);

    }

   
BOOST_AUTO_TEST_SUITE_END()