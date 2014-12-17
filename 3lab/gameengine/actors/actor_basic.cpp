#include <random>
#include <sstream>

#include "actors/actor_basic.h"
#include "game.h"

using std::random_device;
using std::stringstream;
using std::uniform_int_distribution;

namespace lab3 {

  Human::Human(const WorldCoord& initial_position) : Actor(initial_position) {}

  Human::Human(const WorldCoord& initial_position, const string& name) : Actor(initial_position), name(name) {}

  void Human::do_tick(Game& game) {
  }

  void Human::activated_by(Entity& activator) {
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
    stringstream name;

    name << FIRST_NAMES[first_names_number_generator(random)];
    name << " ";
    name << LAST_NAMES[last_names_number_generator(random)];

    return name.str();
  }

  void Human::input(Game &game) {
    last_command = game.get_input();
  }

}
