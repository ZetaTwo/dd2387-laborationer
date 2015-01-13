#include <random>

#include "actors/human.h"
#include "game.h"

using std::random_device;
using std::uniform_int_distribution;

namespace lab3 {

  Human::Human(const WorldCoord& initial_position) : Actor(initial_position) {}

  Human::Human(const WorldCoord& initial_position, const string& name) : Actor(initial_position), name(name) {}

  void Human::do_tick(Game& game) {
  }

  const vector<string> Human::FIRST_NAMES = {
    "Alexander"
   ,"Amanda"
   ,"Bert"
   ,"Bodil"
   ,"Calle"
   ,"Carolina"
   ,"Diana"
   ,"Didrik"
   ,"Embla"
   ,"Emil"
   ,"Feffe"
   ,"Fredrik"
   ,"Gustav"
   ,"Gabriella"
  };

  const vector<string> Human::LAST_NAMES = {
    "Baltatzis"
   ,"Behm"
   ,"Diez"
   ,"Eriksson"
   ,"Hulterström"
   ,"Johnsson"
   ,"Lemne"
   ,"Lundberg"
   ,"Morast"
   ,"Renström"
   ,"Svensson"
  };

  random_device random;
  uniform_int_distribution<size_t> first_names_number_generator{0, Human::FIRST_NAMES.size() - 1};
  uniform_int_distribution<size_t> last_names_number_generator{0, Human::LAST_NAMES.size() - 1};

  string Human::new_name() {
    return easyss()
      << FIRST_NAMES[first_names_number_generator(random)]
      << " "
      << LAST_NAMES[last_names_number_generator(random)]
    ;
  }

}
