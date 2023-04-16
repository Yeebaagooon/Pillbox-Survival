//---Controls
//\Yeebaagooon\Agricultural Madness\Test sound.mp3
int QuickStart = 0;
string MapVersion = "Test Version";
string MapName = "Pillbox Survival";


//---BUGS
/*
playerIsPlaying - currently allows computers to exist ingame

Enemies need more LOS and aggro
*/

//---Launch Codes
bool Visible = true;
bool AllowEnemies = true;
bool CineChoice = true;
int TestRelic = 1;
bool Helpers = false;

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