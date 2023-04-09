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

void ProjRangeandLOS(int range = 10, int LOS = 10){
	xSetInt(dProjectiles, xProjRange, range);
	xSetInt(dProjectiles, xProjLOS, LOS);
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

void ProjRelicDecorate(string proto = "", int special = 0, string path = "0,0,0,0,0,0", float size = 1.0){
	xSetString(dProjectiles, xProjRelicSFX, proto);
	xSetInt(dProjectiles, xProjRelicSpecial, special);
	//1 = refresh every 2000ms
	xSetString(dProjectiles, xProjRelicAnimPath, path);
	xSetFloat(dProjectiles, xProjRelicSize, size);
}

void ProjTowerDecor(string proto = "" ,string path = "0,0,0,0,0,0", float size = 1.0){
	xSetString(dProjectiles, xProjTowerProto, proto);
	xSetString(dProjectiles, xProjTowerProtoAnimPath, path);
	xSetFloat(dProjectiles, xProjTowerProtoSize, size);
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
	ProjRangeandLOS(20,22);
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
	ProjRangeandLOS(20,22);
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
	ProjSetDamage(10);
	ProjRangeandLOS(20,22);
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
	ProjRangeandLOS(25,26);
	ProjSetAmmoCost(25);
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
	ProjRangeandLOS(16,18);
	ProjSetAmmoCost(15);
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
	
	//--BUILD MISSILE --- 5
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(5);
	ProjSetName("Justice bullet");
	ProjSetDesc("Kills a human if it has less than half HP");
	ProjSetProto("Relic");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetDamage(15);
	ProjRangeandLOS(20,22);
	ProjSetAmmoCost(5);
	ProjSetFireRate(1000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(2);
	ProjSetSound("arrow" + iModulo(4, (trTime())+1) + ".wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Hero Birth", 0, "0,1,0,0,0,0");
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 6
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(6);
	ProjSetName("Rapture Tower");
	ProjSetDesc("Raptures humans nearby, no effect on stronger units");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetDamage(0);
	ProjRangeandLOS(20,22);
	ProjSetAmmoCost(50);
	ProjSetFireRate(1000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("\xpack\xcinematics\8_in\krioschange.mp3");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Ragnorok SFX", 1,);
	ProjTowerDecor("Vortex Landing", "0,1,0,0,0,0");
	
	//--BUILD MISSILE --- 7
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(7);
	ProjSetName("Mini grenade");
	ProjSetDesc("Deals explosive damage on impact");
	ProjSetProto("Implode Sphere");
	ProjSetAnim(2);
	ProjSetSize(0.5);
	ProjSetDamage(100);
	ProjRangeandLOS(25,26);
	ProjSetAmmoCost(20);
	ProjSetFireRate(4000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(1);
	ProjSetSound("catapultattack.wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Meteor Impact Ground", 1, "0,1,1,0,0,0");
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 8
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(8);
	ProjSetName("Mini grenade triple");
	ProjSetDesc("Fires three mini grenades");
	ProjSetProto("Implode Sphere");
	ProjSetAnim(2);
	ProjSetSize(0.5);
	ProjSetDamage(100);
	ProjRangeandLOS(25,26);
	ProjSetAmmoCost(50);
	ProjSetFireRate(4000);
	ProjSetCount(3);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(1);
	ProjSetSound("catapultattack.wav");
	ProjSetBaseCosSin(0.984808, 0.173648); //the initial +cos/sin (+10)
	ProjSetMoveCosSin(0.984808, -0.173648); //the incremental -cos/sin (-10 for +5,0,-5)
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Meteor Impact Ground", 1, "0,1,1,0,0,0");
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 9
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(9);
	ProjSetName("Flammenwerfer");
	ProjSetDesc("Werfs flammen");
	ProjSetProto("Fire Giant");
	ProjSetAnim(6);
	ProjSetSize(0);
	ProjSetDamage(100);
	ProjRangeandLOS(30,32);
	ProjSetAmmoCost(50);
	ProjSetFireRate(4000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(3);
	ProjSetSound("firegiantdie.wav");
	//ProjSetBaseCosSin(0.984808, 0.173648); //the initial +cos/sin (+10)
	//ProjSetMoveCosSin(0.984808, -0.173648); //the incremental -cos/sin (-10 for +5,0,-5)
	ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Oak Tree Burning", 0, "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Oak Tree Burning", "0,0,0,0,0,0", 0.0);
	
	//--BUILD MISSILE --- 10
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(10);
	ProjSetName("Flammenwerfer Plus");
	ProjSetDesc("Werfs more flammen");
	ProjSetProto("Fire Giant");
	ProjSetAnim(6);
	ProjSetSize(0);
	ProjSetDamage(100);
	ProjRangeandLOS(30,32);
	ProjSetAmmoCost(200);
	ProjSetFireRate(4000);
	ProjSetCount(5);
	ProjSetAngle(10);
	ProjSetSpeed(30.0);
	ProjSetSpecial(3);
	ProjSetSound("firegiantdie.wav");
	ProjSetBaseCosSin(0.939693, 0.342020); //the initial +cos/sin (+20)
	ProjSetMoveCosSin(0.984808, -0.173648); //the incremental -cos/sin (-10 for +5,0,-5)
	ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Oak Tree Burning", 0, "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Oak Tree Burning", "0,0,0,0,0,0", 0.0);
	
	//--BUILD MISSILE --- 11
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(11);
	ProjSetName("Taser");
	ProjSetDesc("Deals damage and stuns for 1 second");
	ProjSetProto("Lightning Sparks");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(30);
	ProjRangeandLOS(22,22);
	ProjSetAmmoCost(3);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(4);
	ProjSetSound("implodehit" + iModulo(2, (trTime())+1) + ".wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Shockwave stun effect");
	ProjTowerDecor("Cinematic Block");
	
	//END
	
	//SET INDEX FOR ALL PLAYERS TO DEFAULT MISSILE
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		xSetInt(dPlayerData, xCurrentMissile, DefaultMissilePointer);
		xSetInt(dPlayerData, xAmmo, 100);
	}
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
