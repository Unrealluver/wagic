#ifndef _RULES_H_
#define _RULES_H_

#include <string>
#include <vector>
#include "MTGDefinitions.h"

using namespace std;
class ManaCost;
class Player;
class MTGPlayerCards;
class MTGDeck;
class MTGCardInstance;
class GameObserver;

#define MAX_RULES_CARDS 4096;

class RulesPlayerData
{
public:
    vector<string> extraRules;
    Player* player;
    RulesPlayerData();
    ~RulesPlayerData();
    void cleanup();

};

class RulesState
{
public:
    GamePhase phase;
    int player;
    void parsePlayerState(int playerId, string s);
    RulesState();
    RulesPlayerData playerData[2];
    void cleanup();
};

class Rules
{
protected:
    Player * loadPlayerMomir(GameObserver* observer, int isAI);
    Player * loadPlayerRandom(GameObserver* observer, int isAI, int mode);
    Player * loadPlayerRandomThree(GameObserver* observer, int isAI);
	 Player * loadPlayerRandomFive(GameObserver* observer, int isAI);
	 Player * loadPlayerHorde(GameObserver* observer, int isAI);
	 Player * loadRandomSetLimited(GameObserver* observer, int isAI);
    Player * initPlayer(GameObserver *observer, int playerId);
    MTGDeck * buildDeck(int playerId);
    GameType strToGameMode(string s);
    bool postUpdateInitDone;
public:
    enum
    {
        PARSE_UNDEFINED,
        PARSE_INIT,
        PARSE_PLAYER1,
        PARSE_PLAYER2,
        PARSE_PLAYERS
    };

    string bg;
    string filename;
    GameType gamemode;
    bool hidden;
    string displayName;
    int unlockOption;
    string mUnlockOptionString;
    static vector<Rules *> RulesList;

    Rules(string bg = "");
    int load(string _filename);
    static int loadAllRules();
    static void unloadAllRules();
    static Rules * getRulesByFilename(string _filename);
    void initPlayers(GameObserver *observer);
    bool canChooseDeck(); //True if the players get to select their decks, false if the decks are automatically generated by the mode
    void addExtraRules(GameObserver *observer);
    void initGame(GameObserver* observer, bool currentPlayerSet = false);
    //second part of the initialization, needs to happen after the first update call
    void postUpdateInit(GameObserver* observer);
    void cleanup();
    vector<string> extraRules;
    RulesState initState;
    static int getMTGId(string name);
    static MTGCardInstance * getCardByMTGId(GameObserver* observer, int mtgid);

};



#endif
