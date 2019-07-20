#include <iostream>
#include "literal_str.hpp"
#define MESS_BUF 20
#include "mess.h"

using namespace std;

constexpr literal_str hello = "Hello ";
constexpr literal_str world = "World!";
constexpr literal_str lit_str = hello + "World!";
constexpr literal_str lit_str2 = hello + world;
constexpr char c1 = lit_str[5];

void rest_tests();

int main()
{
  cout << "Hello World!" << endl;
  cout << literal_str::to_str(hello) << endl;
  cout << literal_str::to_str(lit_str) << endl;
  cout << literal_str::to_str(lit_str2) << endl;
  static_assert (c1 == ' ', "lit_str[5]");
  rest_tests();

  cout << literal_str::to_str(messy("Simple")) << endl;
  cout << unmess("foo") << endl;
  cout << mess("foo") << endl;
  cout << endl;
  cout << mess("Dummy messed string") << endl;
  return 0;
}

void rest_tests() {
  char hello_[6+1] = { [6]='\00' };
  hello.copy_to(&hello_[0], &hello_[5]);
  cout << hello_ << endl;

  cout << lit_str[5] << lit_str[6] << endl;
  cout << lit_str[0] << ".." << lit_str[6] << "..." << lit_str[11] << endl;
  cout << lit_str.last_idx() << '/' << lit_str.size() << endl;

  literal_str crazy = "Concatencation of: ";
  literal_str crazy1 = crazy + "a b";
  literal_str crazy2 = crazy1 + " ";
  literal_str crazy3 = crazy2 + "c d";
  literal_str crazy4 = crazy3 + ".";

  auto crazied = literal_str::to_str(crazy4);
  cout << crazied << endl;
  for (size_t i = 0; i < crazy4.size(); ++i) {
    cout << crazy4[i];
  }
  cout << endl;
}
