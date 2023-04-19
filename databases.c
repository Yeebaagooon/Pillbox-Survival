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
int xSpyBurn = 0;
int xSpyStun = 0;
int xAggro = 0;

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
int xClassOverride = 0;

//RELICS
int dHeldRelics = 0;
int dFreeRelics = 0;
int xProjType = 0;
int xSFXID = 0;
int xSFXProto = 0;
int xSFXExtra = 0;
int xProjPointer = 0;
int xHeldBy = 0;

//PROJ PROPERTIES
int dProjectiles = 0;
int xProjClass = 0;
int xProjProto = 0;
int xProjDamage = 0;
int xProjAnim = 0;
int xProjAnimPath = 0;
int xProjFireRate = 0;
int xProjRange = 0;
int xProjLOS = 0;
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
int xProjTowerProtoAnimPath = 0;
int xProjRelicSize = 0;
int xProjTowerProtoSize = 0;

//STATUS DB
int dOnFire = 0;
int xTimeToBurn =0;
int xTotalBurnDamage = 0;
int xDamagePerTick = 0;
int xBurnSpyID = 0;

int dStunned = 0;
int xTimeStunned = 0;
int xStunSpyID = 0;
int xStunMutate = 0;

//TERRAIN DB
int dLowTerrain = 0;
int xDeployLoc = 0;

//CITY DB
int dCity = 0;
int xNumber = 0;
int xDistance = 0;
int xLocation = 0;
int xDifficultyStat = 0;
int xPopulation = 0;
int xCityFlagID = 0;
int xCityChestID = 0;
int xCityGuard = 0;
int xCitySFXID = 0;
int xCityAlive = 0;
int xCityLOSID = 0;

//CITY EYECANDY DB
int dCityBuildings = 0;
int xCity = 0;

//CART DB
int dCarts = 0;
int xFromCity = 0;
int xHomeLocation = 0;

//P Tower DB
int dBuildTowers = 0;

//Rocket unit DB
int dRocket = 0;

//Manor DB
int dManor = 0;
int xComplete = 0;
int xHosting = 0;
int xManorSFXID = 0;

//Car DB
int dCar = 0;
int xCarOwner = 0;

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
	xPlayerActive = xInitAddBool(dPlayerData, "active", true);
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
	xSpyBurn = xInitAddInt(dEnemies, "spy id for burn", -1);
	xSpyStun = xInitAddInt(dEnemies, "spy id for stun", -1);
	xCityGuard = xInitAddInt(dEnemies, "guard of city num", 0);
	xAggro = xInitAddBool(dEnemies, "aggro", false);
	
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
	xClassOverride = xInitAddInt(dIncomingMissiles, "class override", -1);
	
	dProjectiles = xInitDatabase("ProjPropers");
	xProjClass = xInitAddInt(dProjectiles, "class", 0);
	xProjProto = xInitAddString(dProjectiles, "proto", "Pharaoh Of Osiris XP");
	xProjDamage = xInitAddInt(dProjectiles, "dmg", 0);
	xProjAnim = xInitAddInt(dProjectiles, "anim", 0);
	xProjAnimPath = xInitAddString(dProjectiles, "animpath", "0,0,0,0,0,0");
	xProjFireRate = xInitAddInt(dProjectiles, "rate", 0);
	xProjRange = xInitAddInt(dProjectiles, "range", 10);
	xProjLOS = xInitAddInt(dProjectiles, "los", 10);
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
	xProjTowerProtoAnimPath = xInitAddString(dProjectiles, "towerdecorpath", "0,0,0,0,0,0");
	xProjRelicSize = xInitAddFloat(dProjectiles, "relic decor scale", 1.0);
	xProjTowerProtoSize = xInitAddFloat(dProjectiles, "tower sfx size", 1.0);
	
	dHeldRelics = xInitDatabase("held relics");
	xUnitID = xInitAddInt(dHeldRelics, "relic id", -1);
	xProjType = xInitAddInt(dHeldRelics, "missile type", -1);
	xSFXID = xInitAddInt(dHeldRelics, "id of unit", -1);
	xSFXProto = xInitAddString(dHeldRelics, "proto of", "error");
	xSFXExtra = xInitAddInt(dHeldRelics, "protoanim", -1);
	xProjPointer = xInitAddInt(dHeldRelics, "m pointer", 0);
	xHeldBy = xInitAddInt(dHeldRelics, "holder", 0);
	
	dFreeRelics = xInitDatabase("Free relics");
	xUnitID = xInitAddInt(dFreeRelics, "relic id", -1);
	xProjType = xInitAddInt(dFreeRelics, "missile type", -1);
	xSFXID = xInitAddInt(dFreeRelics, "id of unit", -1);
	xSFXProto = xInitAddString(dFreeRelics, "proto of", "error");
	xSFXExtra = xInitAddInt(dFreeRelics, "protoanim", -1);
	xProjPointer = xInitAddInt(dFreeRelics, "m pointer", 0);
	
	dOnFire = xInitDatabase("units on fire");
	xUnitID = xInitAddInt(dOnFire, "unit id", -1);
	xTimeToBurn = xInitAddFloat(dOnFire, "burn time", 0.0);
	xTotalBurnDamage = xInitAddFloat(dOnFire, "burn time", 0.0);
	xDamagePerTick = xInitAddFloat(dOnFire, "burn tick", 0.0);
	xBurnSpyID = xInitAddInt(dOnFire, "burn spy id", -1);
	
	dLowTerrain = xInitDatabase("tiledeployset");
	xDeployLoc = xInitAddVector(dLowTerrain, "location", vector(0,0,0));
	
	dCity = xInitDatabase("citydb");
	xNumber = xInitAddInt(dCity, "number", 0);
	xDistance = xInitAddFloat(dCity, "distance to mid", 0.0);
	xLocation = xInitAddVector(dCity, "location", vector(0,0,0));
	xDifficultyStat = xInitAddInt(dCity, "difficultyflag", 0);
	xPopulation = xInitAddInt(dCity, "population", 0);
	xCityFlagID = xInitAddInt(dCity, "idflag", -1);
	xCityChestID = xInitAddInt(dCity, "idchest", -1);
	xCitySFXID = xInitAddInt(dCity, "sfxid", -1);
	xCityAlive = xInitAddBool(dCity, "alive", true);
	xCityLOSID = xInitAddInt(dCity, "revealerid", -1);
	
	dCityBuildings = xInitDatabase("citybuildingdb");
	xUnitID = xInitAddInt(dCityBuildings, "unit id", -1);
	xCity = xInitAddInt(dCityBuildings, "of city", 0);
	
	dCarts = xInitDatabase("carts");
	xUnitID = xInitAddInt(dCarts, "unit id", -1);
	xFromCity = xInitAddInt(dCarts, "came from city", 0);
	xHomeLocation = xInitAddVector(dCarts, "home loc", vector(0,0,0));
	
	dStunned = xInitDatabase("stunned");
	xUnitID = xInitAddInt(dStunned, "unit id", -1);
	xTimeStunned = xInitAddFloat(dStunned, "stuntime", 0.0);
	xStunSpyID = xInitAddInt(dStunned, "stun spyunit id", -1);
	xStunMutate = xInitAddInt(dStunned, "mutate to", -1);
	
	dBuildTowers = xInitDatabase("buildtowers");
	xUnitID = xInitAddInt(dBuildTowers, "unitid", -1);
	
	dRocket = xInitDatabase("rocketdb");
	xUnitID = xInitAddInt(dRocket, "unitid", -1);
	
	dManor = xInitDatabase("manordb");
	xUnitID = xInitAddInt(dManor, "unitid", -1);
	xComplete = xInitAddBool(dManor, "completed", false);
	xHosting = xInitAddBool(dManor, "hosting", false);
	xManorSFXID = xInitAddInt(dManor, "sfxid", -1);
	
	dCar = xInitDatabase("manordb");
	xUnitID = xInitAddInt(dCar, "unitid", -1);
	xComplete = xInitAddBool(dCar, "completed", false);
	xHosting = xInitAddBool(dCar, "hosting", false);
	xCarOwner = xInitAddInt(dCar, "owner", 0);
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
