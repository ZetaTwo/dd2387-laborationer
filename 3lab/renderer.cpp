#include <iostream>

#include "renderer.h"

using std::cout;
using std::endl;

namespace lab3 {

  Renderer::Renderer(ostream& out) :
    out(out) {}

  void Renderer::render(const Game& game) {
    const Player& player = game.get_player();
    const shared_ptr<Actor> player_actor = player.get_actor();

    const WorldCoord& player_position = player_actor->get_position();

    const Map& player_map = game.get_world().get_map(player_position.map_id);

    out << endl << endl << endl << endl << endl;

    render_map(out, game, player_map) << endl;

    out << endl;

    for(const string& message : game.get_messages()) {
      out << message << endl;
    }

  };

  ostream& Renderer::render_map(ostream& os, const Game& game, const Map& map) {

    size_t prev_row = 0;
    for(const Coord& xy : map.range()) {
      if(xy.y > prev_row) {
        prev_row = xy.y;
        os << endl;
      }
      os << ".";
    }

    return os;
  }

}
