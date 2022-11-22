#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "header.hpp"

#define length 400
#define width 200

sf::RenderWindow window (sf::VideoMode (500 , 500) , "Floating triangles");

struct Color
{
  std::array<sf::Uint8 , 4> data_;
  void r (sf::Uint8 x)
  {
    data_[0] = x;
  };
  void g (sf::Uint8 x)
  {
    data_[1] = x;
  };
  void b (sf::Uint8 x)
  {
    data_[2] = x;
  };
  void a (sf::Uint8 x) // прозрачность
  {
    data_[3] = x;
  };
};

std::array<std::array<Color , length> , length> dat;
sf::Uint8* pixels;
sf::Texture texture;
sf::Sprite sprite;

void init_window ()
{
  window.display ();
  for (int i = 0; i < length; ++i)
    for (int j = 0; j < length; ++j)
    {
      dat[i][j].r (255);
      dat[i][j].g (255);
      dat[i][j].b (255);
      dat[i][j].a (255);
    }

  texture.create (length , length);
  sprite.setTexture (texture); // needed to draw the texture on screen
  sprite.setPosition (60 , 60);
  texture.update ((sf::Uint8*)dat.data ()->data ());
}

int flush ()
{
  if (!window.isOpen ())
    return 1;
  window.clear ();

  texture.update ((sf::Uint8*)dat.data ()->data ());
  window.draw (sprite);

  sf::Event event;
  while (window.pollEvent (event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      return 1;
    case sf::Event::KeyPressed:
      if (event.key.code == sf::Keyboard::Escape)
        return 1;
    default:
      break;
    }
  }
  window.display ();
  return 0;
}

void put_pixel (int x, int y, int color)
{
  if (color == 3) // red
  {
    dat[x][y + 100].r (255);
    dat[x][y + 100].g (0);
    dat[x][y + 100].b (0);
    dat[x][y + 100].a (255);
  }
  else if (color == 2) // green
  {
    dat[x][y + 100].r (0);
    dat[x][y + 100].g (255);
    dat[x][y + 100].b (0);
    dat[x][y + 100].a (255);
  }
  else if (color == 1) // blue
  {
    dat[x][y + 100].r (0);
    dat[x][y + 100].g (0);
    dat[x][y + 100].b (255);
    dat[x][y + 100].a (255);
  }
  else if (color == 0) // white
  {
    dat[x][y + 100].r (255);
    dat[x][y + 100].g (255);
    dat[x][y + 100].b (255);
    dat[x][y + 100].a (255);
  }
}