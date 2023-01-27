#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "cards.h"
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;
void createDeck();
void actionPhase();
void productionPhase();
void gameLoop();
void checkWinner();
void reserchPhase();

class CardBase
{
private:
  /* data */
public:
  string title;
  string description;
  string type;
  bool hasCreatures;
  int creatures;
  int creaturesDivision;
  string creatureName;

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
          if (inKey == "self")
          {
          }
          else if (inKey == "other")
          {
          }
          else
          {
            production[inKey] = production[inKey] + inValue;
          }
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
      else if (key == "metaData")
      {
        for (unsigned short i = 0; auto const &[inKey, inValue] : cardConfig[key])
        {

          if (inValue == 1)
          {
            title = inKey;
          }
          else if (inValue == 0)
          {
            description = inKey;
          }
          else if (inValue == 3)
          {
            type = inKey;
          }
        }
      }
      else if (key == "creatures")
      {
        creatures = 0;
        creatureName = cardConfig[key][0].first;
        creaturesDivision = cardConfig[key][0].second;
      }

      ++i;
    }
  };
  void listCardValues()
  {
    string productionMessage = "Production :\n";
    string bankMessage = "Bank :\n";
    string offsetMessage = "Cost Offset :\n";
    int prodCount = 0;
    int bankCount = 0;
    int offsetCount = 0;

    for (auto const &[key, val] : production)
    {
      if (val == 0)
      {
        continue;
      }
      else
      {
        productionMessage = productionMessage + key + ": " + std::to_string(val) + "\n";
        prodCount++;
      }
    }

    for (auto const &[key, val] : bank)
    {
      if (val == 0)
      {
        continue;
      }
      else
      {
        bankMessage = bankMessage + key + ": " + std::to_string(val) + "\n";
        bankCount++;
      }
    }

    for (auto const &[key, val] : costOffSet)
    {
      if (val == 0)
      {
        continue;
      }
      else
      {
        offsetMessage = offsetMessage + key + ": " + std::to_string(val) + "\n";
        offsetCount++;
      }
    }
    if (prodCount > 0)
    {
      cout << productionMessage << endl;
    }
    if (bankCount > 0)
    {
      cout << bankMessage << endl;
    }
    if (offsetCount > 0)
    {
      cout << offsetMessage << endl;
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
struct GlobalParams
{
  int currentOxygen = 0;
  int maxOxygen = 14;
  int currentTemp = -30;
  int maxTemp = 8;
  int currentOceanTiles = 0;
  int maxOceanTiles = 9;
};

class Player
{
private:
public:
  string name = "";
  int terraformRating = 20;
  int victoryPoints = 0;
  Production production;
  Bank bank;
  CostOffset costOffset;
  vector<CardBase> playerHand;
  vector<CardBase> activeEffectCards;
  vector<CardBase> eventDiscard;
  vector<CardBase> playedProjects;
  vector<CardBase> corporation;
  vector<CardBase> projectCards;
  bool hasPassed = false;
  map<string, int> tags = {
      {"science", 0}, {"building", 0}, {"space", 0}, {"earth", 0}, {"jovian", 0}, {"plant", 0}, {"animal", 0}, {"microbe", 0}

  };

  void updatePlayer(map<string, vector<pair<string, int>>> &corp)
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
  };
  void playCard(CardBase &card)
  {

    for (auto const &[key, val] : card.tags)
    {
      tags[key] = tags[key] + val;
    }
    map<string, vector<pair<string, int>>> newPlayerValues = {{"production", {}}, {"bank", {}}, {"costOffset", {}}};

    for (auto const &[key, val] : newPlayerValues)
    {

      if (key == "production")
      {
        for (auto const &[inKey, inVal] : card.production)
        {
          newPlayerValues[key].push_back({inKey, inVal});
        }
      }
      if (key == "bank")
      {
        for (auto const &[inKey, inVal] : card.bank)
        {
          newPlayerValues[key].push_back({inKey, inVal});
        }
      }
      if (key == "costOffest")
      {
        for (auto const &[inKey, inVal] : card.costOffSet)
        {
          newPlayerValues[key].push_back({inKey, inVal});
        }
      }
    }
    updatePlayer(newPlayerValues);
  };
};
vector<CardBase> mainDeck;
vector<CardBase> corporationDeck;
vector<CardBase> discardDeck;
vector<Player> players;
int currentGeneration = 0;
GlobalParams globalParams;
bool isNotGameOver = true;

int main(int argc, char const *argv[])
{

  map<string, vector<pair<string, int>>>
      testCorporation = {{"production", {{"megaCredits", 2}}}, {"bank", {{"megaCredits", 42}}}, {"costOffset", {{"megaCredits", 1}}}};

  int playerCount = 0;
  createDeck();
  cout << "How many players? ";
  cin >> playerCount;

  for (size_t i = 0; i < playerCount; i++)
  {
    Player player;
    cout << "What is Player " << i + 1 << "'s name?";
    string playerName = "";
    cin >> playerName;
    player.name = playerName;
    players.push_back(player);
  }

  for (size_t i = 0; i < players.size(); i++)
  {
    // need to std::random_shuffle() on corp cards then select random
    Player player = players[i];
    player.corporation.insert(player.corporation.end(), {corporationDeck[0], corporationDeck[0]});
    player.projectCards.insert(player.projectCards.end(), {corporationDeck[0], corporationDeck[0], corporationDeck[0], corporationDeck[0], corporationDeck[0], corporationDeck[0], corporationDeck[0], corporationDeck[0]});
    cout << "Choose your corporation: \n"
         << endl;
    for (size_t i = 0; i < player.corporation.size(); i++)
    {
      CardBase corporationCard = player.corporation[i];
      cout << "[" << i << "] : " << corporationCard.title << endl;
      cout << corporationCard.description << endl;
      corporationCard.listCardValues();
    }
    int corpCardToKeep = 0;
    cout << "Card to keep: ";
    cin >> corpCardToKeep;
    cout << "Your have chosen " << player.corporation[corpCardToKeep].title << "coporation!" << endl;
    player.corporation.erase(player.corporation.begin() + corpCardToKeep);
    // need to std::random_shuffle() on project cards then select random
    cout << "Now draw 10 project cards. Either buy cards (3Mc ea.) or discard the card" << endl;
    for (size_t i = 0; i < player.projectCards.size(); i++)
    {
      CardBase projectCard = player.projectCards[i];
      cout << "[" << i << "] : " << projectCard.title << endl;
      cout << projectCard.description << endl;
      projectCard.listCardValues();
    }

    vector<int> cardsToDiscard = {};
    for (size_t i = 0; i < player.projectCards.size(); i++)
    {
      CardBase projectCard = player.projectCards[i];
      cout << "[" << i << "] : " << projectCard.title << endl;
      string choice = "";
      bool isChoiceInvalid = true;
      while (isChoiceInvalid)
      {
        cout << "Buy or discard? " << endl;
        cin >> choice;
        if (choice == "b" || choice == "buy" || choice == "Buy" || choice == "d" || choice == "discard" || choice == "Discard")
        {
          isChoiceInvalid = false;
        }
        else
        {
          cout << "Invalid choice - type 'buy' or 'discard'";
        }
      }
      if (choice == "b" || choice == "buy" || choice == "Buy")
      {
        player.playerHand.push_back(projectCard);
      }
      else if (choice == "d" || choice == "discard" || choice == "Discard")
      {
        discardDeck.push_back(projectCard);
      }
      cardsToDiscard.push_back(i);
    }

    player.projectCards.clear();
  }
  actionPhase();
  productionPhase();
  gameLoop();
  return 0;
}

void gameLoop()
{

  while (isNotGameOver)
  {
    if (globalParams.currentOceanTiles == globalParams.maxOceanTiles && globalParams.currentOxygen == globalParams.maxOxygen && globalParams.currentTemp == globalParams.maxTemp)
    {
      isNotGameOver = false;
      break;
    }
    players.push_back(players[0]);
    players.erase(players.begin());
    researchPhase();

    actionPhase();

    productionPhase();
    currentGeneration++;
  }
  checkWinner();
}
void researchPhase()
{
  // draw 4 cards decide to buy or not
  for (size_t i = 0; i < players.size(); i++)
  {
    // need to std::random_shuffle() on project then select random
    Player player = players[i];
    player.projectCards.insert(player.projectCards.end(), {corporationDeck[0], corporationDeck[0], corporationDeck[0], corporationDeck[0]});
    vector<int> cardsToDiscard = {};
    for (size_t i = 0; i < player.projectCards.size(); i++)
    {
      CardBase projectCard = player.projectCards[i];
      cout << "[" << i << "] : " << projectCard.title << endl;
      string choice = "";
      bool isChoiceInvalid = true;
      while (isChoiceInvalid)
      {
        cout << "Buy or discard? " << endl;
        cin >> choice;
        if (choice == "b" || choice == "buy" || choice == "Buy" || choice == "d" || choice == "discard" || choice == "Discard")
        {
          isChoiceInvalid = false;
        }
        else
        {
          cout << "Invalid choice - type 'buy' or 'discard'";
        }
      }
      if (choice == "b" || choice == "buy" || choice == "Buy")
      {
        player.playerHand.push_back(projectCard);
      }
      else if (choice == "d" || choice == "discard" || choice == "Discard")
      {
        discardDeck.push_back(projectCard);
      }
      cardsToDiscard.push_back(i);
    }
  }
}
vector<bool> havePassed;
vector<string> actionChoices{"Play Card", "Use Action", "Build Standard Project", "Claim milestone", "Fund award", "Place greenary tile", "Increase tempreture", "pass"};
void actionPhase()
{
  for (size_t i = 0; i < players.size(); i++)
  {
    if (players[i].hasPassed)
    {
      havePassed.push_back(true);
      continue;
    }
    int maxActions = 2;
    int currentActions;
    cout << "What action would you like to take?" << endl;
    for (size_t i = 0; i < actionChoices.size(); i++)
    {
      cout << "[" << i << "]" << actionChoices[i] << endl;
    }
    int choice;
    bool isChoiceinValid = true;
    while (isChoiceinValid)
    {
      cout << "Choice - " << endl;
      cin >> choice;
      if (choice >= actionChoices.size())
      {

        cout << "Choice is invalid please select fromt he list" << endl;
      }
      else
      {
        isChoiceinValid = false;
      }
    }
    switch (choice)
    {
    case 0:
      // Playcard
      for (size_t i = 0; i < players[i].playerHand.size(); i++)
      {
        CardBase card = players[i].playerHand[i];
        cout << "[" << i << "] : " << card.title << endl;
        cout << card.description << endl;
        card.listCardValues();
      }
      cout << "Which card would you like to play?" << endl;
      int cardChoice;
      bool isCardChoiceinValid = true;
      while (isCardChoiceinValid)
      {
        cout << "Choice - " << endl;
        cin >> cardChoice;
        if (cardChoice >= players[i].playerHand.size())
        {

          cout << "Choice is invalid please select fromt he list" << endl;
        }
        else
        {
          isCardChoiceinValid = false;
        }
      }
      players[i].playCard(players[i].playerHand[cardChoice]);

    case 1:
      // use action
      break;
    default:
      cout << "not a valid action" << endl;
    }
  }
  if (havePassed.size() == players.size())
  {
    return;
  }
  else
  {
    havePassed.clear();
    actionPhase();
  }

  // 1-2 actions or pass
  //-----
  // A) Play a card from your hand (see page 9).
  // check card requirements- pay for card and add values to player
  //-------
  // B) Use a standard project (see page 10).
  // 1) Sell patents: You may discard a number of cards from hand to gain the same number of M€.
  // 2) Power plant: For 11 M€ you get to increase your energy production 1 step.
  // 3) Asteroid: For 14 M€ you get to increase temperature 1 step (and your TR).
  // 4) Aquifer: For 18 M€ you get to place an ocean tile (you also get 1 TR and collect any placement bonus for the tile, see page 5).
  // 5) Greenery: For 23 M€ you get to place a greenery tile, which increases oxygen level (and your TR) 1 step, and collect any placement bonus for the tile. Put a player marker on the tile. (See page 5)
  // 6) City: For 25 M€ you get to place a city tile (collect any placement bonus for the tile, and place a player marker on it). You also get to increase your M€ production 1 step. (See page 5)
  //--------
  // C) Claim a milestone (see page 10).
  // pay 8 mc each - each worth 5vp - max 3
  // 1) Terraformer: Having a terraform rating of at least 35.
  // 2) Mayor: Owning at least 3 city tiles.
  // 3) Gardener: Owning at least 3 greenery tiles.
  // 4) Builder: Having at least 8 building tags in play.
  // 5) Planner: Having at least 16 cards in your hand when you claim this milestone.
  //---------
  // D) Fund an award (page 11).
  // max 3- only counted at end of game - cost 8/14/20 mc respectively.
  // 1) Landlord: Owning the most tiles in play.
  // 2) Banker: Having the highest M€ production.
  // 3) Scientist: Having the most science tags in play.
  // 4) Thermalist: Having the most heat resource cubes.
  // 5) Miner: Having the most steel and titanium resource
  // cubes.
  //--------
  // E) Use the action on a blue card (see page 11).
  // pay costs on card add values to player.
  //------
  // F) Convert 8 plants into a greenery tile (which gives an oxy- gen increase) as described on the player board (see page 11).
  // take 8 plants from palyer add green tile to map
  // G) Convert 8 heat into a temperature increase as described on the player board (see page 11).
  // pay 8 heat - increase heat by 1 increase terraform rating by 1.
}
void productionPhase()
{ // mc according to terraform rating
  // all production values added to bank
  // all banked energy converted to heat bank
  for (size_t i = 0; i < players.size(); i++)
  {
    Player player = players[i];
    player.bank.bankMap["heat"].second = player.bank.bankMap["heat"].second + player.bank.bankMap["energy"].second;
    player.bank.bankMap["energy"].second = 0;

    vector<pair<string, int>> newBankValues;
    for (auto const &[key, val] : player.production.productionMap)
    {
      newBankValues.push_back({key, val.second});
    }
    player.bank.bankMap["megaCredits"].second = player.bank.bankMap["megaCredits"].second + player.terraformRating;
    player.bank.updateBank(newBankValues);
  }
}
void checkWinner()
{
  // add terraform rating
  // add awards
  // add milestone
  // check cards with variable victory points
  // add green tiles
  // add city and adjacent green tiles.
  // add spent event victory poiints
  // add active and played project card victory points.
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
