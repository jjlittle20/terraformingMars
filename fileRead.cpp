// testing read from file.
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;
class Card
{
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
  void listCardValues()
  {
    string productionMessage = "Production :\n";
    string bankMessage = "Bank :\n";
    string offsetMessage = "Cost Offset :\n";
    string tagMessage = "Tags :\n";
    int prodCount = 0;
    int bankCount = 0;
    int offsetCount = 0;
    int tagCount = 0;

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
    for (auto const &[key, val] : tags)
    {
      if (val == 0)
      {
        continue;
      }
      else
      {
        tagMessage = tagMessage + key + ": " + std::to_string(val) + "\n";
        tagCount++;
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
    if (tagCount > 0)
    {
      cout << tagMessage << endl;
    }
  }
};

vector<Card> createCards(string fileName)
{
  std::ifstream myfile;
  myfile.open(fileName);
  vector<Card> cards;
  if (myfile.is_open())
  {
    string myline;
    while (myfile)
    {
      std::getline(myfile, myline);
      bool createNewCard = false;
      if (myline == "##")
      {
        createNewCard = true;
        Card card;
        string title;
        string description;
        string type;
        string victoryPoints;
        std::getline(myfile, title);
        std::getline(myfile, description);
        std::getline(myfile, type);
        std::getline(myfile, victoryPoints);
        if (title == "fileEnd")
        {
          break;
        }

        card.title = title;
        card.description = description;
        card.type = type;
        card.victoryPoints = std::stoi(victoryPoints);
        cout << card.title << "\n"
             << card.description << "\n"
             << card.type << "\n";
        while (createNewCard)
        {
          string nextLine;
          std::getline(myfile, nextLine);
          // cout << nextLine << "\n";

          if (nextLine == "cardEnd")
          {
            createNewCard = false;
            break;
          }
          else if (nextLine == "production:")
          {
            bool getProdValues = true;
            while (getProdValues)
            {
              string key;
              std::getline(myfile, key);
              if (key == "end")
              {
                getProdValues = false;
                break;
              }
              else
              {
                string value;
                std::getline(myfile, value);
                card.production[key] = std::stoi(value);
              }
            }
          }
          else if (nextLine == "bank:")
          {
            bool getBankValues = true;
            while (getBankValues)
            {
              string key;
              std::getline(myfile, key);
              if (key == "end")
              {
                getBankValues = false;
                break;
              }
              else
              {
                string value;
                std::getline(myfile, value);
                card.bank[key] = std::stoi(value);
              }
            }
          }
          else if (nextLine == "costOffSet:")
          {
            bool getcostOffSetValues = true;
            while (getcostOffSetValues)
            {
              string key;
              std::getline(myfile, key);
              if (key == "end")
              {
                getcostOffSetValues = false;
                break;
              }
              else
              {
                string value;
                std::getline(myfile, value);
                card.costOffSet[key] = std::stoi(value);
              }
            }
          }
          else if (nextLine == "tags:")
          {
            bool getTagValues = true;
            while (getTagValues)
            {
              string key;
              std::getline(myfile, key);
              if (key == "end")
              {
                getTagValues = false;
                break;
              }
              else
              {
                string value;
                std::getline(myfile, value);
                card.tags[key] = std::stoi(value);
              }
            }
          }
          else if (nextLine == "creatures:")
          {

            bool getcreaturesValues = true;
            while (getcreaturesValues)
            {
              string key;
              std::getline(myfile, key);
              if (key == "end")
              {
                getcreaturesValues = false;
                break;
              }
              else
              {
                // string value;
                // std::getline(myfile, value);
                // card.creatures[key] = std::stoi(value);
              }
            }
          }
          else if (nextLine == "action:")
          {
            bool getactionValues = true;
            while (getactionValues)
            {
              string key;
              std::getline(myfile, key);
              if (key == "end")
              {
                getactionValues = false;
                break;
              }
              else
              {
                // string value;
                // std::getline(myfile, value);
                // card.creatures[key] = std::stoi(value);
              }
            }
          }
        }
        cards.push_back(card);
      }
    }
  }
  return cards;
}
int main()
{

  vector<Card> projectCards = createCards("projectCards.txt");
  for (size_t i = 0; i < projectCards.size(); i++)
  {
    projectCards[i].listCardValues();
  }

  cout << "------" << endl;
  vector<Card> corporationCards = createCards("corporationCards.txt");
  for (size_t i = 0; i < corporationCards.size(); i++)
  {
    corporationCards[i].listCardValues();
  }

  return 0;
}
