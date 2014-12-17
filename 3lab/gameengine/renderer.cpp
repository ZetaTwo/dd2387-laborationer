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
    list<World::physicals_t::value_type> entities_on_map;
    const World::physicals_t& entities = game.get_world().get_physicals();
    copy_if(
      entities.begin(),
      entities.end(),
      back_inserter(entities_on_map),
      [&map](const World::physicals_t::value_type& p) -> bool {
        return p.second->get_position().map_id == map.get_id();
      }
    );

    size_t prev_row = 0;
    for(const Coord& xy : map.range()) {
      if(xy.y > prev_row) {
        prev_row = xy.y;
        os << endl;
      }

      auto entity_on_xy_it = find_if(
        entities_on_map.begin(),
        entities_on_map.end(),
        [&xy](const World::physicals_t::value_type& p) {
          return xy == p.second->get_position();
        }
      );

      if(entity_on_xy_it != entities_on_map.end()) {
        os << entity_on_xy_it->second->get_id();
      } else {
        os << ".";
      }
    }

    return os;
  }

}
