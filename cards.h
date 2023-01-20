#include <string>
#include <vector>
#include <map>
using std::map;
using std::pair;
using std::string;
using std::tuple;
using std::vector;

class Action
{
public:
  string description;     // action description
  string type;            // production||self||other||draw
  vector<string> subType; // megacredits||tag match
  int drawDiscard;
  int drawKeep;
  int drawBuy;
  int amount;
};
class CardConfig
{
public:
  vector<pair<string, int>> production;
  vector<pair<string, int>> bank;
  vector<pair<string, int>> costOffset;
  vector<pair<string, int>> tags;
  string title;
  string description;
  string type;
  vector<tuple<string, int, int>> creatures;
  vector<Action> action;
  bool hasAction = false;
  CardConfig(string w)
  {
    title = w;
  };
};
CardConfig cr("s");

// build a card creater cli function to save to a file.

vector<CardConfig> cards = {};

vector<map<string, vector<pair<string, int>>>> mainCards = {

    {{"creatures", {{"animals", 3}}}, {"metaData", {{"this is card title", 1}, {"This is the card description", 0}}}, {"production", {{"megaCredits", 2}}}, {"bank", {{"megaCredits", 2}}}, {"costOffSet", {{"megaCredits", 2}}}}

};
vector<map<string, vector<pair<string, int>>>> corporationCards = {{{"metaData", {{"this is card title", 1}, {"This is the card description", 0}}}, {"production", {{"megaCredits", 2}}}, {"bank", {{"megaCredits", 2}}}, {"costOffSet", {{"megaCredits", 2}}}}};