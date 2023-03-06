#include <iostream>
#include <sstream>
#include <exception>
#include <vector>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/Simple_window.h>

#include "logic.h"
#include "logic_shapes.h"


int main ()
try
{
  int win_w = 1700;
  int win_h = 450;
  Graph_lib::Point lt{ Graph_lib::x_max()/2 - win_w/2, Graph_lib::y_max()/2 - win_h/2 };
  Simple_window win{ lt, win_w, win_h, "Scheme of Logic Elements" };

  using namespace Logic;

  Graph_lib::Vector_ref <Or> Ors;
  for (int i = 0; i < 4; i++) Ors.push_back(new Or());

  Graph_lib::Vector_ref <Source> Sources;
  for (int i = 0; i < 9; i++) Sources.push_back(new Source());

  Graph_lib::Vector_ref <And> Ands;
  Graph_lib::Vector_ref <Xor> Xors;
  for (int i = 0; i < 8; i++) {
    Ands.push_back(new And());
    Xors.push_back(new Xor());
  }

  Sources[0] >> Xors[1];
  Sources[0] >> Ands[0];

  for (int i = 0; i < 4; i++){
    Xors[2 * i] >> Xors[2 * i + 1];
    //Sources[1 + 2 * i] >> Xors[i * 2 + 1];
    Sources[i * 2 + 1] >> Xors[i * 2] >> Ands[2 * i] >> Ors[i]; //A1
    Sources[i * 2 + 1] >> Ands[i * 2 + 1] >> Ors[i];
    Sources[i * 2 + 2] >> Xors[i * 2];
    Sources[i * 2 + 2] >> Ands[i * 2 + 1];
    if (i != 0) {
      Ors[i - 1] >> Xors[2 * i + 1];
      Ors[i - 1] >> Ands[2 * i];
    }
  }

  SchemeShape scheme{ Graph_lib::Point{5, 5}, win_w - 80, win_h - 10 };
  win.attach(scheme);

  auto column_x = [] (double c) -> int
  {
    return int(30 + 100 * c);
  };

  auto line_y = [] (double l) -> int
  {
    return int(40 + 75 * l);
  };


  Graph_lib::Vector_ref <SourceShape> SourcesShape; 
  Graph_lib::Vector_ref <AndShape> AndsShape; 
  Graph_lib::Vector_ref <OrShape> OrsShape; 
  Graph_lib::Vector_ref <XorShape> XorsShape; 

  SourcesShape.push_back(new SourceShape{scheme, Sources[0], "Cin", Graph_lib::Point{ column_x(0), line_y(2) }});

  for (int i = 0; i < 4; i++){

    SourcesShape.push_back(new SourceShape{scheme, Sources[2 * i + 1], "A" + std::to_string(2 * i  +1), Graph_lib::Point{ column_x(i * 4), line_y(0) + 50 * i}});
    SourcesShape.push_back(new SourceShape{scheme, Sources[2 * i + 2], "B" + std::to_string(2 * i  +1), Graph_lib::Point{ column_x(i * 4), line_y(1) + 50 * i}}); 

    XorsShape.push_back(new XorShape{scheme, Xors[2 * i], "Xor" + std::to_string(2 * i + 1), Graph_lib::Point{ column_x(1 + i * 4), line_y(0) + 15 + 50 * i}});
    XorsShape.push_back(new XorShape{scheme, Xors[2 * i + 1], "Xor" + std::to_string(2 * i + 2), Graph_lib::Point{ column_x(2 + i * 4), line_y(0) + 20 + 50 * i}}); 

    AndsShape.push_back(new AndShape{scheme, Ands[2 * i], "And" + std::to_string(2 * i + 1), Graph_lib::Point{ column_x(2 + i * 4), line_y(1) + 15 + 50 * i}});
    AndsShape.push_back(new AndShape{scheme, Ands[2 * i + 1], "And" + std::to_string(2 * i + 2), Graph_lib::Point{ column_x(2 + i * 4), line_y(2) + 20 + 50 * i}}); 

    OrsShape.push_back(new OrShape{scheme, Ors[i], "Or" + std::to_string(i), Graph_lib::Point{ column_x(3 + i * 4), line_y(3 + i) - 30 * i}});
  }

  scheme.update_connections();
  int counter = 1;
  std::cin >> counter;

  //first signal is control
  for (int i = 0; i < counter; i ++){
    std::string data;
    std::cin >> data;
    for (int i = 0; i < 9; i++) Sources[i] = int(data[i] - '0');
    win.wait_for_button();
  }
  return 0;
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr <<"Oops, something went wrong..."<< std::endl;
  return 2;
}
