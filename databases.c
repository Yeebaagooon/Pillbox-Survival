int dDestroyMe = 0;
int xDestroyName = 0;
int xDestroyTime = 0;

int spysearch = 0;
int spyreset = 0;
int spyProto = 0;
int spyUnit = 1;
int spyDest = 2;
int spyScale = 3;
int spyActive = 4;
int spyAnim = 5;

//PROJECTILE DB
int xUnitName = 0;
int xInTower = 0;

int dTowers = 0;
int xUnitPos = 0;
int xTowerPos = 0;
int xOwner = 0;

int dEnemies = 0;

int dMissiles = 0;
int xMissilePos = 0;
int xMissileDir = 0;
int xMissileCentre = 0;
int xMissileDmg = 0;
int xMissileTime = 0;
int xMissileStartTime = 0;
int xMissilePrevTime = 0;

int dIncomingMissiles = 0;
int xMissileDest = 0;
int xMissileSpyID = 0;
int xMissileSpyOfSpyID = 0;
int xMissileProto = 0;
int xMissileCarProto = 0;
int xMissileAnim = 0;
int SpyDone = 0;
int xIMissileDmg = 0;
int xIMissileTime = 0;


rule setup_first_databases
active
highFrequency
{
	dPlayerData = xInitDatabase("playerData");
	xUnitID = xInitAddInt(dPlayerData, "Unit id", -1);
	xSpyID = xInitAddInt(dPlayerData, "Spy id", -1);
	xUnitPos = xInitAddVector(dPlayerData, "pos", vector(0,0,0));
	xTarget = xInitAddInt(dPlayerData, "target id", -1);
	xInTower = xInitAddBool(dPlayerData, "In tower", false);
	xsDisableSelf();
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
	
	dTowers = xInitDatabase("towerdb");
	xUnitID = xInitAddInt(dTowers, "unit id", -1);
	xOwner = xInitAddInt(dTowers, "owner", 0);
	xTowerPos = xInitAddVector(dTowers, "pos", vector(0,0,0));
	
	dEnemies = xInitDatabase("enemy db");
	xUnitID = xInitAddInt(dEnemies, "unit id", -1);
	
	dMissiles = xInitDatabase("Missiles DB");
	xUnitID = xInitAddInt(dMissiles, "missile unit id", -1);
	xOwner = xInitAddInt(dMissiles, "missile owner", 0);
	xMissilePos = xInitAddVector(dMissiles, "position", vector(0,0,0));
	xMissileDir = xInitAddVector(dMissiles, "direction", vector(0,0,0));
	xMissileStartTime = xInitAddInt(dMissiles, "start time", -1);
	xMissilePrevTime = xInitAddInt(dMissiles, "start time", -1);
	
	dIncomingMissiles = xInitDatabase("Incoming DB");
	xUnitID = xInitAddInt(dIncomingMissiles, "missile unit id", -1);
	xOwner = xInitAddInt(dIncomingMissiles, "missile owner", -1);
	xMissilePos = xInitAddVector(dIncomingMissiles, "position", vector(0,0,0));
	xMissileDir = xInitAddVector(dIncomingMissiles, "direction", vector(0,0,0));
}


int dSpyRequests = 0;
int xSpyRequestProto = 0;
int xSpyRequestDest = 0;
int xSpyRequestScale = 0;
int xSpyRequestAnim = 0;
int xSpyRequestEvent = 0;
//int xSpyRequestExtra = 0;

rule initialise_spy_database
active
highFrequency
{
	xsDisableSelf();
	xsSetContextPlayer(0);
	dSpyRequests = xInitDatabase("spyRequests", 32);
	xSpyRequestProto = xInitAddInt(dSpyRequests, "proto");
	xSpyRequestAnim = xInitAddInt(dSpyRequests, "anim");
	xSpyRequestScale = xInitAddVector(dSpyRequests, "scale");
	xSpyRequestDest = xInitAddVector(dSpyRequests, "dest");
	xSpyRequestEvent = xInitAddInt(dSpyRequests, "event");
}

/*
Assumes that the target unit is already selected
*/
void spyEffect(int proto = 0, int anim = 0, vector dest = vector(0,0,0), vector scale = vector(1,1,1), int event = -1) {
	int newest = xAddDatabaseBlock(dSpyRequests);
	xSetInt(dSpyRequests, xSpyRequestProto, proto, newest);
	xSetInt(dSpyRequests, xSpyRequestAnim, anim, newest);
	xSetVector(dSpyRequests, xSpyRequestDest, dest, newest);
	xSetVector(dSpyRequests, xSpyRequestScale, scale, newest);
	xSetInt(dSpyRequests, xSpyRequestEvent, event, newest);
	trTechInvokeGodPower(0, "spy", vector(0,0,0), vector(0,0,0));
}
