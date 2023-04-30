//---Controls
//\Yeebaagooon\Agricultural Madness\Test sound.mp3
int QuickStart = 0;
string MapVersion = "Test Version";
string MapName = "Pillbox Survival";


//---BUGS
/*
playerIsPlaying - currently allows computers to exist ingame

CATAPULT SHOT TAKEN
CHICKEN BLOOD TAKEN
tEMPLE DISABLED

200k gold available
700k wood available

Oracle = Human HP
Auto = Building HP
Satyr = Sky passage damage
Argus = Human speed

*/

//---Launch Codes
bool Visible = true;
bool AllowEnemies = true;
bool CineChoice = false;
int TestRelic = 45;
bool Helpers = false;

//---Game Data
int MapSkin = 0;
//1, greek, 2 is eggy, 3 is norse, 4 is hades
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
int Difficulty = 0;
float yc = 0.1;
bool TempleUnlocked = false;
int SkipRequired = 0;
int PlayersActive = 0;

//SKIN DATA
string TreeType = "";
string TreeTerrain = "";
string TreeBorderTerrain = "";
string Terrain1 = "";
string Terrain2 = "";
string Terrain3 = "";
string Terrain4 = "";
string Terrain5 = "";
string RoadTerrain = "";

string Huntable = "";
string Berry = "";
string Bird = "";

//---Enemy skin
string Enemy0 = "";
string Enemy1 = "";
string Enemy2 = "";
string Enemy3 = "";
string Enemy4 = "";
string Enemy5 = "";
string Enemy6 = "";
string Enemy7 = "";
string Enemy8 = "";
string TowerAnim = "0,0,0,0,0,0,0";

//---City skin
string City1Building = "";
string City2Building = "";

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
