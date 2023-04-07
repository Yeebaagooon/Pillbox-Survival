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
int xCurrentMissile = 0;
int xUnitName = 0;
int xInTower = 0;
int xAmmo = 0;
int xLastShotTime = 0;

int dTowers = 0;
int xUnitPos = 0;
int xTowerPos = 0;
int xOwner = 0;
int xTowerSFXID = 0;

int dEnemies = 0;
int xStationary = 0;

int dMissiles = 0;
int xMissilePos = 0;
int xMissileDir = 0;
int xMissileCentre = 0;
int xMissileDmg = 0;
int xMissileTime = 0;
int xMissileStartTime = 0;
int xMissilePrevTime = 0;
int xMissileClass = 0;

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

//RELICS
int dHeldRelics = 0;
int dFreeRelics = 0;
int xProjType = 0;
int xSFXID = 0;
int xSFXProto = 0;
int xSFXExtra = 0;
int xProjPointer = 0;

//PROJ PROPERTIES
int dProjectiles = 0;
int xProjClass = 0;
int xProjProto = 0;
int xProjDamage = 0;
int xProjAnim = 0;
int xProjAnimPath = 0;
int xProjFireRate = 0;
int xProjCount = 0;
int xProjAngle = 0;
int xProjSpeed = 0;
int xProjSize = 0;
int xProjSpecial = 0;
int xProjSound = 0;
int xProjName = 0;
int xProjDesc = 0;
int xPointer = 0;
int xProjAmmoCost = 0;
int xProjBaseCos = 0;
int xProjBaseSin = 0;
int xProjMoveCos = 0;
int xProjMoveSin = 0;
int xProjPassthrough = 0;
int xProjDeathSpecial = 0;
int xProjUse = 0;
int xProjRelicSFX = 0;
int xProjRelicSpecial = 0;
int xProjRelicAnimPath = 0;
int xProjTowerProto = 0;


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
	xCurrentMissile = xInitAddInt(dPlayerData, "current missile", 0);
	xAmmo = xInitAddInt(dPlayerData, "ammo count", 0);
	xLastShotTime = xInitAddInt(dPlayerData, "shoot time", 0);
	xsDisableSelf();
	xsEnableRule("SetupProjTypes");
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
	
	dTowers = xInitDatabase("towerdb");
	xUnitID = xInitAddInt(dTowers, "unit id", -1);
	xOwner = xInitAddInt(dTowers, "owner", 0);
	xTowerPos = xInitAddVector(dTowers, "pos", vector(0,0,0));
	xTowerSFXID = xInitAddInt(dTowers, "special unit id", -1);
	
	dEnemies = xInitDatabase("enemy db");
	xUnitID = xInitAddInt(dEnemies, "unit id", -1);
	xStationary = xInitAddBool(dEnemies, "no movement", false);
	
	dMissiles = xInitDatabase("Missiles DB");
	xUnitID = xInitAddInt(dMissiles, "missile unit id", -1);
	xOwner = xInitAddInt(dMissiles, "missile owner", 0);
	xMissilePos = xInitAddVector(dMissiles, "position", vector(0,0,0));
	xMissileDir = xInitAddVector(dMissiles, "direction", vector(0,0,0));
	xMissileStartTime = xInitAddInt(dMissiles, "start time", -1);
	xMissilePrevTime = xInitAddInt(dMissiles, "start time", -1);
	xMissileClass = xInitAddInt(dMissiles, "class pointer", 0);
	
	dIncomingMissiles = xInitDatabase("Incoming DB");
	xUnitID = xInitAddInt(dIncomingMissiles, "missile unit id", -1);
	xOwner = xInitAddInt(dIncomingMissiles, "missile owner", -1);
	xMissilePos = xInitAddVector(dIncomingMissiles, "position", vector(0,0,0));
	xMissileDir = xInitAddVector(dIncomingMissiles, "direction", vector(0,0,0));
	
	dProjectiles = xInitDatabase("ProjPropers");
	xProjClass = xInitAddInt(dProjectiles, "class", 0);
	xProjProto = xInitAddString(dProjectiles, "proto", "Pharaoh Of Osiris XP");
	xProjDamage = xInitAddInt(dProjectiles, "dmg", 0);
	xProjAnim = xInitAddInt(dProjectiles, "anim", 0);
	xProjAnimPath = xInitAddString(dProjectiles, "animpath", "0,0,0,0,0,0");
	xProjFireRate = xInitAddInt(dProjectiles, "rate", 0);
	xProjCount = xInitAddInt(dProjectiles, "count", 0);
	xProjAngle = xInitAddInt(dProjectiles, "angle", 0);
	xProjSpeed = xInitAddFloat(dProjectiles, "speed", 30.0);
	xProjSize = xInitAddFloat(dProjectiles, "size", 0.0);
	xProjSpecial = xInitAddInt(dProjectiles, "special", 0);
	xProjSound = xInitAddString(dProjectiles, "desc", "cantdothat.wav");
	xProjName = xInitAddString(dProjectiles, "desc", "Error");
	xProjDesc = xInitAddString(dProjectiles, "desc", "Error");
	xPointer = xInitAddInt(dProjectiles, "pointer", 0);
	xProjAmmoCost = xInitAddInt(dProjectiles, "ammo cost", 1);
	xProjBaseCos = xInitAddFloat(dProjectiles, "circle stuff", 0.0);
	xProjBaseSin = xInitAddFloat(dProjectiles, "circle stuff", 0.0);
	xProjMoveCos = xInitAddFloat(dProjectiles, "circle stuff", 0.0);
	xProjMoveSin = xInitAddFloat(dProjectiles, "circle stuff", 0.0);
	xProjPassthrough = xInitAddBool(dProjectiles, "passthrough", false);
	xProjDeathSpecial = xInitAddBool(dProjectiles, "death effect", false);
	xProjUse = xInitAddBool(dProjectiles, "use proj", true);
	xProjRelicSFX = xInitAddString(dProjectiles, "relicproto", "Error");
	xProjRelicSpecial = xInitAddInt(dProjectiles, "specialrelic", 0);
	xProjRelicAnimPath = xInitAddString(dProjectiles, "ranimpath", "0,0,0,0,0,0");
	xProjTowerProto  = xInitAddString(dProjectiles, "towerdecor", "Cinematic Block");
	
	dHeldRelics = xInitDatabase("held relics");
	xUnitID = xInitAddInt(dHeldRelics, "relic id", -1);
	xProjType = xInitAddInt(dHeldRelics, "missile type", -1);
	xSFXID = xInitAddInt(dHeldRelics, "id of unit", -1);
	xSFXProto = xInitAddString(dHeldRelics, "proto of", "error");
	xSFXExtra = xInitAddInt(dHeldRelics, "protoanim", -1);
	xProjPointer = xInitAddInt(dHeldRelics, "m pointer", 0);
	
	dFreeRelics = xInitDatabase("Free relics");
	xUnitID = xInitAddInt(dFreeRelics, "relic id", -1);
	xProjType = xInitAddInt(dFreeRelics, "missile type", -1);
	xSFXID = xInitAddInt(dFreeRelics, "id of unit", -1);
	xSFXProto = xInitAddString(dFreeRelics, "proto of", "error");
	xSFXExtra = xInitAddInt(dFreeRelics, "protoanim", -1);
	xProjPointer = xInitAddInt(dFreeRelics, "m pointer", 0);
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
