#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::pair;
using std::string;
using std::vector;

class Bank
{
private:
public:
  map<string, pair<string, int>> bankMap = {
      {"megaCredits", {"Mega Credits", 0}},
      // {"Steel", 0},
      // {"Titanium", 0},
      // {"Plants", 0},
      // {"Power", 0},
      // {"Heat", 0}
  };
};

class Production
{
private:
public:
  map<string, pair<string, int>> productionMap = {
      {"megaCredits", {"Mega Credits", 0}},
      // {"Steel", 0},
      // {"Titanium", 0},
      // {"Plants", 0},
      // {"Power", 0},
      // {"Heat", 0}
  };
  void initProduction(vector<pair<string, int>> corporation)
  {

    for (size_t i = 0; i < corporation.size(); i++)
    {

      productionMap[corporation[i].first].second = corporation[i].second;
    }
  }

  void listProducion()
  {
    for (auto const &[key, val] : productionMap)
    {
      std::cout << val.first // string (key)
                << ": "
                << val.second // string's value
                << std::endl;
    }
  }
};
class Player
{
private:
public:
  string name = "";
  Production production;
  Bank bank;
};

int main(int argc, char const *argv[])
{
  using std::cout;
  Player player;
  vector<pair<string, int>> testCorporation = {{"megaCredits", 42}};
  player.production.initProduction(testCorporation);
  player.production.listProducion();

  return 0;
}
