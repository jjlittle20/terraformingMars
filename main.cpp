#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "cards.h"

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;
void createDeck();
enum CardType
{
  event,
  corporate,
  active,
  project
};
class CardBase
{
private:
  /* data */
public:
  string title;
  string description;
  CardType type;
  int victoryPoints = 0;
  map<string, int> tags = {
      {"science", 0}, {"building", 0}, {"space", 0}, {"earth", 0}, {"jovian", 0}, {"plant", 0}, {"animal", 0}, {"microbe", 0}

  };
  map<string, int> production = {
      {"megaCredits", 0}, {"steel", 0}, {"titanium", 0}, {"plants", 0}, {"energy", 0}, {"heat", 0}

  };
  map<string, int> bank = {
      {"megaCredits", 0}, {"steel", 0}, {"titanium", 0}, {"plants", 0}, {"energy", 0}, {"heat", 0}

  };
  map<string, int> costOffSet = {
      {"megaCredits", 0}, {"steel", 0}, {"titanium", 0}, {"plants", 0}, {"energy", 0}, {"heat", 0}

  };

  CardBase(map<string, vector<pair<string, int>>> &cardConfig)
  {
    for (unsigned short i = 0; auto const &[key, value] : cardConfig)
    {

      if (key == "production")
      {
        for (unsigned short i = 0; auto const &[inKey, inValue] : cardConfig[key])
        {
          production[inKey] = production[inKey] + inValue;
        }
      }
      else if (key == "bank")
      {
        for (unsigned short i = 0; auto const &[inKey, inValue] : cardConfig[key])
        {
          bank[inKey] = bank[inKey] + inValue;
        }
      }
      else if (key == "costOffset")
      {
        for (unsigned short i = 0; auto const &[inKey, inValue] : cardConfig[key])
        {
          costOffSet[inKey] = costOffSet[inKey] + inValue;
        }
      }

      ++i;
    }
  };
  void listCardValues()
  {
    for (auto const &[key, val] : production)
    {
      cout << "Production " << key // string (key)
           << ": "
           << val // string's value
           << endl;
    }
    for (auto const &[key, val] : bank)
    {
      cout << "Bank " << key // string (key)
           << ": "
           << val // string's value
           << endl;
    }
    for (auto const &[key, val] : costOffSet)
    {
      cout << "OffSet " << key // string (key)
           << ": "
           << val // string's value
           << endl;
    }
  }
};

class Bank
{
private:
public:
  map<string, pair<string, int>> bankMap = {
      {"megaCredits", {"Mega Credits", 0}},
      {"energy", {"Energy", 0}},
      {"steel", {"Steel", 0}},
      {"titanium", {"Titanium", 0}},
      {"plants", {"Plants", 0}},
      {"heat", {"Heat", 0}},

  };
  void updateBank(vector<pair<string, int>> value)
  {
    for (size_t i = 0; i < value.size(); i++)
    {

      bankMap[value[i].first].second = value[i].second;
    }
  };
  void listBank()
  {
    for (auto const &[key, val] : bankMap)
    {
      cout << val.first // string (key)
           << ": "
           << val.second // string's value
           << endl;
    }
  }
};

class Production
{
private:
public:
  map<string, pair<string, int>> productionMap = {
      {"megaCredits", {"Mega Credits", 0}},
      {"energy", {"Energy", 0}},
      {"steel", {"Steel", 0}},
      {"titanium", {"Titanium", 0}},
      {"plants", {"Plants", 0}},
      {"heat", {"Heat", 0}},
  };
  void updateProduction(vector<pair<string, int>> value)
  {

    for (size_t i = 0; i < value.size(); i++)
    {

      productionMap[value[i].first].second = value[i].second;
    }
  }

  void listProducion()
  {
    for (auto const &[key, val] : productionMap)
    {
      cout << val.first // string (key)
           << ": "
           << val.second // string's value
           << endl;
    }
  }
};

class CostOffset
{
private:
  /* data */
public:
  map<string, pair<string, int>> offsetMap = {
      {"megaCredits", {"Mega Credits", 0}},
      {"energy", {"Energy", 0}},
      {"steel", {"Steel", 0}},
      {"titanium", {"Titanium", 0}},
      {"plants", {"Plants", 0}},
      {"heat", {"Heat", 0}},
  };

  void updateCostOffset(vector<pair<string, int>> value)
  {

    for (size_t i = 0; i < value.size(); i++)
    {

      offsetMap[value[i].first].second = value[i].second;
    }
  }
  void listOffset()
  {
    for (auto const &[key, val] : offsetMap)
    {
      cout << val.first // string (key)
           << ": "
           << val.second // string's value
           << endl;
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
  CostOffset costOffset;
  vector<CardBase> playerHand;
  vector<CardBase> activeEffectCards;
  vector<CardBase> eventDiscard;
  vector<CardBase> playedProjects;
  map<string, int> tags = {
      {"science", 0}, {"building", 0}, {"space", 0}, {"earth", 0}, {"jovian", 0}, {"plant", 0}, {"animal", 0}, {"microbe", 0}

  };
  int victoryPoints = 0;

  Player(map<string, vector<pair<string, int>>> &corp)
  {
    for (unsigned short i = 0; auto const &[key, value] : corp)
    {

      if (key == "production")
      {
        production.updateProduction(value);
      }
      else if (key == "bank")
      {
        bank.updateBank(value);
      }
      else if (key == "costOffset")
      {
        costOffset.updateCostOffset(value);
      }

      ++i;
    }
  }
};
vector<CardBase> mainDeck;
vector<CardBase> corporationDeck;
vector<CardBase> discardDeck;

int main(int argc, char const *argv[])
{

  map<string, vector<pair<string, int>>> testCorporation = {{"production", {{"megaCredits", 2}}}, {"bank", {{"megaCredits", 42}}}, {"costOffset", {{"megaCredits", 1}}}};
  Player player(testCorporation);
  createDeck();
  for (size_t i = 0; i < mainDeck.size(); i++)
  {
    mainDeck[i].listCardValues();
  }
  for (size_t i = 0; i < corporationDeck.size(); i++)
  {
    corporationDeck[i].listCardValues();
  }

  // CardBase cardTest(testCorporation);
  // cardTest.listCardValues();
  // player.production.listProducion();
  // player.bank.listBank();
  // player.costOffset.listOffset();

  return 0;
}

void createDeck()
{

  for (size_t i = 0; i < mainCards.size(); i++)
  {
    CardBase newCard(mainCards[i]);
    mainDeck.push_back(newCard);
  }
  for (size_t i = 0; i < corporationCards.size(); i++)
  {
    CardBase newCard(corporationCards[i]);
    corporationDeck.push_back(newCard);
  }
}
