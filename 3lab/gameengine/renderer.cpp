#include <algorithm>
#include <iostream>
#include <list>

#include "game.h"
#include "renderer.h"
#include "world.h"

using std::back_inserter;
using std::copy_if;
using std::cout;
using std::endl;
using std::find;
using std::list;
using std::pair;

namespace lab3 {

  Renderer::Renderer(ostream& out) :
    out(out) {}

  void Renderer::render(const Game& game) {
    const WorldCoord& player_position = game.get_camera().get_position();
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

      const shared_ptr<Tile> tile = map.get_tile(xy);
      const shared_ptr<PhysicalEntity> ent = tile->get_entity();

      if (ent == nullptr) {
        cout << tile->to_char();
      }
      else {
        cout << ent->to_char();
      }

      
    }

    return os;
  }

}
