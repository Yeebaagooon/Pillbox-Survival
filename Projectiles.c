//Missile

void ProjSetClass(int class = 0){
	xSetInt(dProjectiles, xProjClass, class);
}

void ProjSetProto(string proto = ""){
	xSetString(dProjectiles, xProjProto, proto);
}

void ProjSetDamage(int dmg = 0){
	xSetInt(dProjectiles, xProjDamage, dmg);
}

void ProjSetAnim(int anim = 2){
	xSetInt(dProjectiles, xProjAnim, anim);
}

void ProjSetAnimPath(string path = ""){
	xSetString(dProjectiles, xProjAnimPath, path);
}

void ProjSetFireRate(int num = 1000){
	xSetInt(dProjectiles, xProjFireRate, num);
}

void ProjSetCount(int num = 1){
	xSetInt(dProjectiles, xProjCount, num);
	if(num == 1){
		xSetFloat(dProjectiles, xProjBaseCos, 0.0);
		xSetFloat(dProjectiles, xProjBaseSin, 0.0);
		xSetFloat(dProjectiles, xProjMoveCos, 0.0);
		xSetFloat(dProjectiles, xProjMoveSin, 0.0);
	}
}

void ProjSetAngle(int num = 0){
	xSetInt(dProjectiles, xProjAngle, num);
}

void ProjSetSpeed(float num = 0.0){
	xSetFloat(dProjectiles, xProjSpeed, num);
}

void ProjSetSize(float num = 0.0){
	xSetFloat(dProjectiles, xProjSize, num);
}

void ProjSetSpecial(int num = 0){
	xSetInt(dProjectiles, xProjSpecial, num);
}

void ProjSetSound(string texts = ""){
	xSetString(dProjectiles, xProjSound, texts);
}

void ProjSetName(string texts = ""){
	xSetString(dProjectiles, xProjName, texts);
}

void ProjSetDesc(string texts = ""){
	xSetString(dProjectiles, xProjDesc, texts);
}

void ProjSetAmmoCost(int num = 1){
	xSetInt(dProjectiles, xProjAmmoCost, num);
}

void ProjSetBaseCosSin(float num = 0.0, float other = 0.0){
	xSetFloat(dProjectiles, xProjBaseCos, num);
	xSetFloat(dProjectiles, xProjBaseSin, other);
}

void ProjSetMoveCosSin(float num = 0.0, float other = 0.0){
	xSetFloat(dProjectiles, xProjMoveCos, num);
	xSetFloat(dProjectiles, xProjMoveSin, other);
}

void ProjAllowPassThrough(){
	xSetBool(dProjectiles, xProjPassthrough, true);
}

void ProjDeathEffect(){
	xSetBool(dProjectiles, xProjDeathSpecial, true);
}

void ProjNoShoot(){
	xSetBool(dProjectiles, xProjUse, false);
}

void ProjRelicDecorate(string proto = "", int special = 0, string path = "0,0,0,0,0,0"){
	xSetString(dProjectiles, xProjRelicSFX, proto);
	xSetInt(dProjectiles, xProjRelicSpecial, special);
	//1 = refresh every 2000ms
	xSetString(dProjectiles, xProjRelicAnimPath, path);
}

void ProjTowerDecor(string proto = ""){
	xSetString(dProjectiles, xProjTowerProto, proto);
}

rule SetupProjTypes
inactive
highFrequency
{
	//--BUILD MISSILE --- 0
	int index = 0;
	index = xAddDatabaseBlock(dProjectiles, true);
	DefaultMissilePointer = index;
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(0);
	ProjSetName("Standard bullet");
	ProjSetDesc("Default projectile");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(10);
	ProjSetAmmoCost(1);
	ProjSetFireRate(1000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("arrow" + iModulo(4, (trTime())+1) + ".wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	//ProjRelicDecorate("")
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 1
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(1);
	ProjSetName("Rapid fire");
	ProjSetDesc("Shoots standard bullets at a faster rate");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(10);
	ProjSetAmmoCost(1);
	ProjSetFireRate(800);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("arrow" + iModulo(4, (trTime())+1) + ".wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Arkantos Boost SFX", 1);
	ProjTowerDecor("Cinematic Block");
	
	
	//--BUILD MISSILE --- 2
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(2);
	ProjSetName("Triple shot");
	ProjSetDesc("Shoots 3 standard bullets at once with 5 degrees offset");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(5);
	ProjSetAmmoCost(3);
	ProjSetFireRate(1000);
	ProjSetCount(3);
	ProjSetAngle(5);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("arrow" + iModulo(4, (trTime())+1) + ".wav");
	ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Arkantos Boost SFX", 1);
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 3
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(3);
	ProjSetName("Bolter");
	ProjSetDesc("Rains lightning down on targets");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(250);
	ProjSetAmmoCost(5);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("lightningstrike" + iModulo(4, (trTime())+1) + ".wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Lightning Sparks Ground", 1);
	ProjTowerDecor("Lightning Cloud");
	
	//--BUILD MISSILE --- 4
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(4);
	ProjSetName("Burner");
	ProjSetDesc("Sets nearby units ablaze");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(150);
	ProjSetAmmoCost(5);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("inferno.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Inferno Unit Flame", 1);
	ProjTowerDecor("Inferno Fire Ground");
	
	//SET INDEX FOR ALL PLAYERS TO DEFAULT MISSILE
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		xSetInt(dPlayerData, xMissileClass, index);
		xSetInt(dPlayerData, xAmmo, 100);
	}
	//END
	xsDisableSelf();
}

/*


Class
Protounit
Damage
Anim Override (2 default)
Anim path override
Fire time
Proj count
Speed
Size
Special properties
How does player equip them?
Relics

?LOS/Range

*/


//NOTTUD DEPLOY OUT OF LOS
/*
int deployRandomLocOutOfLOS(string unit = "", int p = 0){
	while(true){
		int nextUnitName = trGetNextUnitScenarioNameNumber();
		vector deployLocation = pickRandomUnblockedLocation();
		deployLoc(xsVectorGetX(deployLocation), xsVectorGetZ(deployLocation), unit, p);
		if(trGetNextUnitScenarioNameNumber() == nextUnitName){
			continue;
		}
		trUnitSelectClear();
		trUnitSelect(""+nextUnitName);
		bool inLOS = false;
		for(q = 1; <= "+h+"){
			if(trUnitHasLOS(q) && getPlayerDead(q) == false){
				trUnitDestroy();
				inLOS = true;
				break;
			}
		}
		if(inLOS == false){
			return (nextUnitName);
		}
	}
}
*/
