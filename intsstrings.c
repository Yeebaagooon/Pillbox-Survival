//---Controls
//\Yeebaagooon\Agricultural Madness\Test sound.mp3
int QuickStart = 0;
string MapVersion = "Test Version";
string MapName = "Pillbox Survival";


//---BUGS
/*
playerIsPlaying - currently allows computers to exist ingame

cine garrison relic

?chicken kill player vills

AGGRO
you could have some code that when enemy takes damage it moves towards nearest ally unit?
you could make it only trigger agro if the unit is idle?

Have attached pheonix egg for bomber unit

CATAPULT SHOT TAKEN
CHICKEN BLOOD TAKEN
*/

//---Launch Codes
bool Visible = false;
bool AllowEnemies = true;
bool CineChoice = true;
int TestRelic = 2;
bool Helpers = true;

//---Game Data
int MapSkin = 0;
bool Day = true;
int Date = 0;
int NextDay = 1000;
int NextNight = 1000;
int LunchTime = 1000;
int TeaTime = 1000;
int myPerlin = 0;
int DontDestroyBelow = 0;
int CitiesToMake = 0;
int CitiesCaptured = 0;
int CartsCaptured = 0;
int PlayersDead = 0;
int NightInterval = 0;
int NextNightAttack = 0;
int Part = 0;
int WonderHP = 9999;

string TreeType = "";
string ForestTerrain = "";
string UnderForestTerrain = "";
string LowestTerrain = "";

//---
int timelast = 0;
int timelastfire = 0;
int DefaultMissilePointer = 0;
int firetimediff = 0;
int firetimelast = 0;
int citychecktime = 0;

//---Player Data
int dPlayerData = 0;
int xSpyID = 0;
int xUnitID = 0;
int xTarget = 0;
int xPlayerActive = 0;

//---Events
const int EVENT_REMOVE_CAM_TRACKS = 26;
