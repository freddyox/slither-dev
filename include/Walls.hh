#ifndef WALLS_HH
#define WALLS_HH

#include <SFML/Graphics.hpp>
#include <vector>

class Walls : public sf::Drawable, public sf::Transformable {

private:
  float displayx, displayy;
  float width;
  sf::RectangleShape Wall;
  sf::Color WallColor;
  std::vector<sf::RectangleShape> WallVec;

  sf::VertexArray lines;
  std::vector<sf::VertexArray> grid;

  sf::Texture texture;
  sf::Sprite bg;

public:
  Walls(float,float); 
  ~Walls() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  float getWallWidth() { return width; }
  void makegrid();
};
#endif
