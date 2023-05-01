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
	/*if(num != 10){
		num = num*1.5;
	}*/
	xSetInt(dProjectiles, xProjAmmoCost, num*((Difficulty*0.5)+1));
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
	//2> - anim
	xSetString(dProjectiles, xProjRelicAnimPath, path);
	xSetFloat(dProjectiles, xProjRelicSize, size);
}

void ProjTowerDecor(string proto = "" ,string path = "0,0,0,0,0,0", float size = 1.0, int anim = 2){
	xSetString(dProjectiles, xProjTowerProto, proto);
	xSetString(dProjectiles, xProjTowerProtoAnimPath, path);
	xSetFloat(dProjectiles, xProjTowerProtoSize, size);
	xSetInt(dProjectiles, xProjTowerAnim, anim);
}

//ORDERING FOR PROJECTILES
const int PROJ_Default = 0;
//---CLASS 1
const int PROJ_Default_Rapid1 = 1;
const int PROJ_Default_C3A5 = 2;
const int PROJ_Taser = 3;
const int PROJ_Stun = 4;
const int PROJ_MiniGrenade = 5;
const int PROJ_Blue = 6;
const int PROJ_Bolter = 7;
const int PROJ_Burner = 8;
const int PROJ_Justice = 9;
const int PROJ_Spider = 10;
const int PROJ_Convert = 11;
const int PROJ_Fast = 12;
const int PROJ_Fart = 13;
//---CLASS 2
const int PROJ_BolterClose = 14;
const int PROJ_Rapture = 15;
const int PROJ_MiniGrenade_C3A10 = 16;
const int PROJ_Flammenwerfer = 17;
const int PROJ_FlammenwerferC5A10 = 18;
const int PROJ_BlueC2A5 = 19;
const int PROJ_BlueC3A5 = 20;
const int PROJ_Curse = 21;
const int PROJ_CurseFast = 22;
const int PROJ_Homo = 23;
const int PROJ_100Dmg = 24;
const int PROJ_Tremor = 25;
//---CLASS 3
const int PROJ_ChickenGrenade = 26;
const int PROJ_Acid = 27;
const int PROJ_Sniper = 28;
const int PROJ_RaptureMyth = 29;
const int PROJ_JusticeMyth = 30;
const int PROJ_Dimensional = 31;
const int PROJ_Explosion = 32;
const int PROJ_ConvertDeluxe = 33;
//---CLASS 4
const int PROJ_SniperExplode = 34;
const int PROJ_Sunstrike = 35;
const int PROJ_Tesla = 36;
const int PROJ_BolterDeluxe = 37;
const int PROJ_Purple = 38;
const int PROJ_Tsunami = 39;
const int PROJ_Nottud = 40;
const int PROJ_RaptureDeluxe = 41;
const int PROJ_Ten = 42;
const int PROJ_ChickenGrenadeTriple = 43;
const int PROJ_LiquidFire = 44;
const int PROJ_SandStorm = 45;
const int PROJ_Freezer = 46;
const int PROJ_Kronos = 47;
//---new ones
const int PROJ_Hellfire = 48;
const int PROJ_FrostBlast = 49;
const int PROJ_EarthShatter = 50;
const int PROJ_TimeFreeze = 51;
const int PROJ_Zombie = 52;
const int PROJ_Barrage = 53;


//Purple deluxe for Hades only
//Sandstorm for eggy
//
//4 levels, maybe 5 if there's a reward only


rule SetupProjTypes
inactive
highFrequency
{
	//--BUILD MISSILE --- 0
	int index = 0;
	index = xAddDatabaseBlock(dProjectiles, true);
	DefaultMissilePointer = index;
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Default);
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
	ProjSetClass(PROJ_Default_Rapid1);
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
	ProjSetClass(PROJ_Default_C3A5);
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
	ProjSetClass(PROJ_Bolter);
	ProjSetName("Bolter");
	ProjSetDesc("Rains lightning down on targets");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(250);
	ProjRangeandLOS(20,22);
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
	ProjSetClass(PROJ_Burner);
	ProjSetName("Burner");
	ProjSetDesc("Sets nearby units ablaze");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(150);
	ProjRangeandLOS(14,16);
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
	ProjSetClass(PROJ_Justice);
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
	ProjSetClass(PROJ_Rapture);
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
	ProjSetClass(PROJ_MiniGrenade);
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
	ProjRelicDecorate("Meteor Impact Ground", 1, "0,0,1,0,1,0");
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 8
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_MiniGrenade_C3A10);
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
	ProjRelicDecorate("Meteor Impact Ground", 1, "0,0,1,0,1,0");
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 9
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Flammenwerfer);
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
	ProjSetClass(PROJ_FlammenwerferC5A10);
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
	ProjSetClass(PROJ_Taser);
	ProjSetName("Taser");
	ProjSetDesc("Deals damage and stuns humans for 1 second");
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
	
	//--BUILD MISSILE --- 12
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Stun);
	ProjSetName("Stun Gun");
	ProjSetDesc("Stuns human units for 1 second");
	ProjSetProto("Lightning Sparks");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(0);
	ProjRangeandLOS(22,22);
	ProjSetAmmoCost(1);
	ProjSetFireRate(750);
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
	
	//--BUILD MISSILE --- 13
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Blue);
	ProjSetName("Blue bullet");
	ProjSetDesc("50 damage with the passthrough ability");
	ProjSetProto("Outpost");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetDamage(50);
	ProjRangeandLOS(22,22);
	ProjSetAmmoCost(5);
	ProjSetFireRate(1500);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("hitpointsmax.wav");
	ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Outpost" ,0, "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Guardian XP", "0,0,0,0,0,0", 0);
	
	//--BUILD MISSILE --- 14
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_BlueC2A5);
	ProjSetName("Double blue");
	ProjSetDesc("Shoots 2 passthrough blue missiles");
	ProjSetProto("Outpost");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetDamage(50);
	ProjRangeandLOS(22,22);
	ProjSetAmmoCost(6);
	ProjSetFireRate(1500);
	ProjSetCount(2);
	ProjSetAngle(5);
	ProjSetBaseCosSin(0.996195, 0.087156);
	ProjSetMoveCosSin(0.984808, -0.173648); //the incremental -cos/sin (-10 for +5,0,-5)
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("hitpointsmax.wav");
	ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Outpost" ,0, "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Guardian XP", "0,0,0,0,0,0", 0);
	
	//--BUILD MISSILE --- 15
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_BlueC3A5);
	ProjSetName("Triple blue");
	ProjSetDesc("Shoots 3 passthrough blue missiles");
	ProjSetProto("Outpost");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetDamage(50);
	ProjRangeandLOS(22,22);
	ProjSetAmmoCost(15);
	ProjSetFireRate(1500);
	ProjSetCount(3);
	ProjSetAngle(5);
	ProjSetBaseCosSin(0.996195, 0.087156);
	ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-10 for +5,0,-5)
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("hitpointsmax.wav");
	ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Outpost" ,0, "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Guardian XP", "0,0,0,0,0,0", 0);
	
	//--BUILD MISSILE --- 16
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Curse);
	ProjSetName("Cursey");
	ProjSetDesc("Turns nearby humans into pigs");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0);
	ProjSetDamage(0);
	ProjRangeandLOS(16,18);
	ProjSetAmmoCost(20);
	ProjSetFireRate(5000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("pigpower.wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Pig");
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 17
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_CurseFast);
	ProjSetName("Cursey Fast");
	ProjSetDesc("A faster human curser");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0);
	ProjSetDamage(0);
	ProjRangeandLOS(16,18);
	ProjSetAmmoCost(30);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("pigpower.wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Pig");
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 18
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_100Dmg);
	ProjSetName("Zen Shot");
	ProjSetDesc("Higher damage projectile");
	ProjSetProto("Qilin");
	ProjSetAnim(18);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.0);
	ProjSetDamage(100);
	ProjRangeandLOS(20,22);
	ProjSetAmmoCost(10);
	ProjSetFireRate(900);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("sentinelbirth.wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Qilin", 3, "", 0.0);
	ProjTowerDecor("Gaia Forest effect");
	
	//--BUILD MISSILE --- 19
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_BolterClose);
	ProjSetName("Close Bolter");
	ProjSetDesc("A fast but low range bolt attack");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(250);
	ProjRangeandLOS(6,6);
	ProjSetAmmoCost(30);
	ProjSetFireRate(300);
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
	
	//--BUILD MISSILE --- 20
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_ChickenGrenade);
	ProjSetName("Chicken Grenade");
	ProjSetDesc("Fires exploding chickens");
	ProjSetProto("Chicken Exploding");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(1);
	ProjSetDamage(200);
	ProjRangeandLOS(24,24);
	ProjSetAmmoCost(35);
	ProjSetFireRate(1800);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(5);
	ProjSetSound("chickenambient.wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Chicken", 0 , "1,0,0,0,0,0", 2);
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 21
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Acid);
	ProjSetName("Acidifier");
	ProjSetDesc("Launches acid attacks, dealing 400 bonus damage to nearby units");
	ProjSetProto("Poison SFX");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(2);
	ProjSetDamage(100);
	ProjRangeandLOS(18,20);
	ProjSetAmmoCost(70);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(6);
	ProjSetSound("argusfreezeattack.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Acid Pool",0, "0,0,1,0,0,0,0");
	ProjTowerDecor("Acid Pool");
	
	//--BUILD MISSILE --- 22
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Tremor);
	ProjSetName("Earth blaster");
	ProjSetDesc("Creates shockwaves on enemies");
	ProjSetProto("Poison SFX");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(2);
	ProjSetDamage(100);
	ProjRangeandLOS(30,20);
	ProjSetAmmoCost(20);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("shockwave.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Tremor",1);
	ProjTowerDecor("Tremor");
	
	//--BUILD MISSILE --- 23
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Sniper);
	ProjSetName("Sniper");
	ProjSetDesc("Fast moving with a large range");
	ProjSetProto("Lampades");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0);
	ProjSetDamage(100);
	ProjRangeandLOS(45,44);
	ProjSetAmmoCost(30);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(45.0);
	ProjSetSpecial(0);
	ProjSetSound("genericheavyfall1.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Mist");
	ProjTowerDecor("Mist");
	
	//--BUILD MISSILE --- 24
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_RaptureMyth);
	ProjSetName("Rapture Tower (myth)");
	ProjSetDesc("Raptures humans and myth units nearby, no effect on stronger units");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetDamage(0);
	ProjRangeandLOS(20,22);
	ProjSetAmmoCost(100);
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
	
	//--BUILD MISSILE --- 25
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_JusticeMyth);
	ProjSetName("Golden bullet");
	ProjSetDesc("Kills a myth if it has less than half HP");
	ProjSetProto("Petosuchus projectile");
	ProjSetAnim(2);
	ProjSetSize(1.5);
	ProjSetDamage(75);
	ProjRangeandLOS(18,20);
	ProjSetAmmoCost(40);
	ProjSetFireRate(1000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(40.0);
	ProjSetSpecial(7);
	ProjSetSound("arrow" + iModulo(4, (trTime())+1) + ".wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Lighthouse", 0, "0,1,1,1,1,0,0", 0.0);
	ProjTowerDecor("Increase Prosperity Small");
	
	//--BUILD MISSILE --- 26
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Homo);
	ProjSetName("Rainbow bullet");
	ProjSetDesc("Explodes any units killed by the projectile");
	ProjSetProto("Flying Purple Hippo");
	ProjSetAnim(15);
	ProjSetSize(0);
	ProjSetDamage(75);
	ProjRangeandLOS(20,20);
	ProjSetAmmoCost(9);
	ProjSetFireRate(1000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(40.0);
	ProjSetSpecial(8);
	ProjSetSound("restorationbirth.wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Valkyrie", 0, "", 0.0);
	ProjTowerDecor("Valkyrie");
	
	//--BUILD MISSILE --- 27
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Dimensional);
	ProjSetName("Dimensional bullet");
	ProjSetDesc("Does random dimensional damage to myth and human units");
	ProjSetProto("Timeshift In");
	ProjSetAnim(2);
	ProjSetAnimPath("0,1,1,0,0,0,0");
	ProjSetSize(0);
	ProjSetDamage(0);
	ProjRangeandLOS(26,26);
	ProjSetAmmoCost(90);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(9);
	ProjSetSound("vulturedeath.wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Timeshift In", 0, "0,1,1,0,0,0,0", 0.0);
	ProjTowerDecor("Timeshift Out", "0,1,0,0,0,0,0");
	
	//--BUILD MISSILE --- 28
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Explosion);
	ProjSetName("Explosion tower");
	ProjSetDesc("Does damage to all units near tower");
	ProjSetProto("Implode Shockwave");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetDamage(150);
	ProjRangeandLOS(14,13);
	ProjSetAmmoCost(250);
	ProjSetFireRate(7500);
	ProjSetCount(8);
	ProjSetAngle(45);
	ProjSetSpeed(1.0);
	ProjSetSpecial(10);
	ProjSetSound("implode explode.wav");
	ProjSetBaseCosSin(1, 0); //the initial +cos/sin (0)
	ProjSetMoveCosSin(0.707107, 0.707107); //the incremental -cos/sin (+45)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Oracle Hero", 52 , "0,0,0,0,0,0", 0.25);
	ProjTowerDecor("Osiris Box Glow", "0,1,0,0,0,0,0");
	
	//--BUILD MISSILE --- 29
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_SniperExplode);
	ProjSetName("Sniper Grenade");
	ProjSetDesc("Exploding sniper shot");
	ProjSetProto("Lampades");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0);
	ProjSetDamage(200);
	ProjRangeandLOS(45,44);
	ProjSetAmmoCost(125);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(45.0);
	ProjSetSpecial(10);
	ProjSetSound("genericheavyfall2.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Mist");
	ProjTowerDecor("Mist");
	
	//--BUILD MISSILE --- 30
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Sunstrike);
	ProjSetName("Sun Smiter");
	ProjSetDesc("Rains holy fire down to purify enemies");
	ProjSetProto("Poison SFX");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(2);
	ProjSetDamage(500);
	ProjRangeandLOS(20,20);
	ProjSetAmmoCost(120);
	ProjSetFireRate(1600);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("restorationbirth.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Hero Birth",1, "0,0,0,0,0,0,0");
	ProjTowerDecor("Hero Birth");
	
	//--BUILD MISSILE --- 31
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Tesla);
	ProjSetName("Tesla gun");
	ProjSetDesc("Bolts enemies in a line");
	ProjSetProto("Arkantosman");
	ProjSetAnim(18);
	ProjSetSize(0);
	ProjSetDamage(400);
	ProjRangeandLOS(22,22);
	ProjSetAmmoCost(200);
	ProjSetFireRate(1500);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(11);
	ProjSetSound("sonofosirisbolt.wav");
	ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Arkantos God" ,0, "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Arkantosman", "0,0,0,0,0,0", 0);
	
	//--BUILD MISSILE --- 32
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_BolterDeluxe);
	ProjSetName("Bolter Deluxe");
	ProjSetDesc("Stronger rapid bolting");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(400);
	ProjRangeandLOS(25,26);
	ProjSetAmmoCost(75);
	ProjSetFireRate(250);
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
	
	//--BUILD MISSILE --- 33
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Purple);
	ProjSetName("Purple cloud of doom");
	ProjSetDesc("Fires a purple cloud");
	ProjSetProto("Kronny Birth SFX");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetAnimPath("0,0,1,0,0,0,0");
	ProjSetDamage(400);
	ProjRangeandLOS(22,22);
	ProjSetAmmoCost(200);
	ProjSetFireRate(1500);
	ProjSetCount(5);
	ProjSetAngle(5);
	ProjSetBaseCosSin(0.984808, 0.173648); //the initial +cos/sin (+10)
	ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5)
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("\cinematics\31_in\sound 1.mp3");
	ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Kronny Birth SFX" ,1, "0,0,1,0,0,0", 0.0);
	ProjTowerDecor("Kronny Birth SFX", "0,0,1,0,0,0", 0);
	
	//--BUILD MISSILE --- 34
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Tsunami);
	ProjSetName("Tsunami");
	ProjSetDesc("Launches a tsunami at the target - long cooldown");
	ProjSetProto("Tsunami");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(900);
	ProjRangeandLOS(24,24);
	ProjSetAmmoCost(300);
	ProjSetFireRate(5000);
	ProjSetCount(1);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("meteorsplash.wav");
	ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Splash",1, "", 0.1);
	ProjTowerDecor("Kronny Birth");
	
	//--BUILD MISSILE --- 35
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Nottud);
	ProjSetName("Meteor Tower");
	ProjSetDesc("Rains SPC meteors down for huge damage on stationary enemies");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(2000);
	ProjRangeandLOS(40,40);
	ProjSetAmmoCost(400);
	ProjSetFireRate(5000);
	ProjSetCount(1);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("meteorapproach.wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Phoenix Egg",1, "", 0.8);
	ProjTowerDecor("Meteor");
	
	//--BUILD MISSILE --- 36
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_RaptureDeluxe);
	ProjSetName("Rapture Tower Deluxe");
	ProjSetDesc("Raptures any units, but reduced range and expensive");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetDamage(0);
	ProjRangeandLOS(15,16);
	ProjSetAmmoCost(250);
	ProjSetFireRate(1250);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("\xpack\xcinematics\8_in\krioschange.mp3");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Rain Small", 0, "0,1,1,0,0,0");
	ProjTowerDecor("Vortex Landing", "0,1,0,0,0,0");
	
	//--BUILD MISSILE --- 37
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Kronos);
	ProjSetName("Purple cloud of doom Deluxe");
	ProjSetDesc("Fires an even bigger deadlier purple cloud");
	ProjSetProto("Titan Kronos");
	ProjSetAnim(2);
	ProjSetSize(0);
	ProjSetAnimPath("0,0,0,0,0,0,0");
	ProjSetDamage(800);
	ProjRangeandLOS(26,26);
	ProjSetAmmoCost(400);
	ProjSetFireRate(1500);
	ProjSetCount(9);
	ProjSetAngle(5);
	ProjSetBaseCosSin(0.939693, 0.342020); //the initial +cos/sin (+20)
	ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5)
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("\cinematics\31_in\sound 1.mp3");
	ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Kronny Birth SFX" ,1, "0,1,0,0,0,0", 0.0);
	ProjTowerDecor("Titan Kronos", "0,0,0,0,0,0", 0);
	
	//--BUILD MISSILE --- 38
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Spider);
	ProjSetName("Spider Summoner");
	ProjSetDesc("Does no damage but summons spider eggs");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(0);
	ProjRangeandLOS(40,40);
	ProjSetAmmoCost(70);
	ProjSetFireRate(4000);
	ProjSetCount(1);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("spiders2.wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Spider Door",0, "", 0.8);
	ProjTowerDecor("Spider Egg", "0,0,0,0,0,0",2.5);
	
	//--BUILD MISSILE --- 39
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Ten);
	ProjSetName("Death Pact of Ten");
	ProjSetDesc("When 10 enemies are highlighted, kills them all");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(0);
	ProjRangeandLOS(40,40);
	ProjSetAmmoCost(40);
	ProjSetFireRate(500);
	ProjSetCount(1);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("underminebirth.wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Vortex finish linked",1, "0,0,1,0,0,0", 1);
	ProjTowerDecor("Vortex start linked", "0,0,1,0,0,0",2.5);
	
	//--BUILD MISSILE --- 40
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_ChickenGrenadeTriple);
	ProjSetName("Chicken Grenade Triple");
	ProjSetDesc("Fires exploding chickens");
	ProjSetProto("Chicken Exploding");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(1);
	ProjSetDamage(200);
	ProjRangeandLOS(24,24);
	ProjSetAmmoCost(70);
	ProjSetFireRate(1800);
	ProjSetCount(3);
	ProjSetAngle(20);
	ProjSetBaseCosSin(0.939693, 0.342020); //the initial +cos/sin (+20)
	ProjSetMoveCosSin(0.939693, -0.342020); //the incremental -cos/sin (-20)
	ProjSetSpeed(30.0);
	ProjSetSpecial(5);
	ProjSetSound("chickenambient.wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Chicken", 0 , "0,0,0,0,0,0", 3);
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 41
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_LiquidFire);
	ProjSetName("Greek fire");
	ProjSetDesc("Launches liquid fire, dealing additional burn damage");
	ProjSetProto("Meteorite");
	ProjSetAnim(6);
	ProjSetSize(1);
	ProjSetDamage(500);
	ProjRangeandLOS(24,24);
	ProjSetAmmoCost(200);
	ProjSetFireRate(2000);
	ProjSetCount(1);
	ProjSetSpeed(30.0);
	ProjSetSpecial(12);
	ProjSetSound("fireball launch.wav");
	ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Meteorite",2, "", 1);
	ProjTowerDecor("Fire Hades");
	
	//--BUILD MISSILE --- 42
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_SandStorm);
	ProjSetName("Sandstorm");
	ProjSetDesc("Fires sandstorms, chance of tornado");
	ProjSetProto("Heka Shockwave SFX");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(500);
	ProjRangeandLOS(28,24);
	ProjSetAmmoCost(300);
	ProjSetFireRate(500);
	ProjSetCount(3);
	ProjSetAngle(20);
	ProjSetBaseCosSin(0.939693, 0.342020); //the initial +cos/sin (+20)
	ProjSetMoveCosSin(0.939693, -0.342020); //the incremental -cos/sin (-20)
	ProjSetSpeed(30.0);
	ProjSetSpecial(11);
	ProjSetSound("sphinxspecialattack.wav");
	//ProjAllowPassThrough();
	ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Sphinx", 47 , "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Shifting Sands Out");
	
	//--BUILD MISSILE --- 43
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Freezer);
	ProjSetName("Freezer");
	ProjSetDesc("Freezes units for 10 seconds");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(500);
	ProjRangeandLOS(40,40);
	ProjSetAmmoCost(200);
	ProjSetFireRate(1000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(12);
	ProjSetSound("frostwindloop.wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("King Folstag", 40 , "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Ice Sheet");
	
	//--BUILD MISSILE --- 44
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Convert);
	ProjSetName("Conversion Tower");
	ProjSetDesc("Converts human units and " + Enemy3);
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(0);
	ProjRangeandLOS(30,30);
	ProjSetAmmoCost(55);
	ProjSetFireRate(5000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(12);
	ProjSetSound("converted.wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Conversion SFX", 1 , "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Summoning Tree 2", "", 0.0, 18);
	
	//--BUILD MISSILE --- 45
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_ConvertDeluxe);
	ProjSetName("Conversion Tower Deluxe");
	ProjSetDesc("Converts anything weaker than " + Enemy4);
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetSize(1);
	ProjSetDamage(0);
	ProjRangeandLOS(26,26);
	ProjSetAmmoCost(90);
	ProjSetFireRate(3800);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(12);
	ProjSetSound("converted.wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Conversion SFX", 1 , "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Summoning Tree 2", "", 0.0, 18);
	
	//--BUILD MISSILE --- 46
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Fast);
	ProjSetName("Machine tower");
	ProjSetDesc("Fast firing weapon");
	ProjSetProto("Promethean");
	ProjSetAnim(6);
	ProjSetSize(0.0);
	ProjSetDamage(25);
	ProjRangeandLOS(18,18);
	ProjSetAmmoCost(3);
	ProjSetFireRate(300);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("arrow" + iModulo(4, (trTime())+1) + ".wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Anubite", 3 , "0,0,0,0,0,0", 0.0);
	ProjTowerDecor("Cinematic Block");
	
	//--BUILD MISSILE --- 47
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Fart);
	ProjSetName("Gas tower");
	ProjSetDesc("Fires farts");
	ProjSetProto("Mummy");
	ProjSetAnim(2);
	ProjSetSize(0.0);
	ProjSetDamage(40);
	ProjRangeandLOS(18,18);
	ProjSetAmmoCost(4);
	ProjSetFireRate(1300);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("qilin_grunt" + iModulo(2, (trTime())+1) + ".wav");
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	//ProjNoShoot();
	ProjRelicDecorate("Pestilence SFX1", 0 , "0,1,0,0,0,0", 0.0);
	ProjTowerDecor("Pestilence SFX2");
	
	//--BUILD MISSILE --- 48
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Hellfire);
	ProjSetName("Hellfire");
	ProjSetDesc("Burns all units near the tower");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(100);
	ProjRangeandLOS(14,16);
	ProjSetAmmoCost(80);
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
	ProjRelicDecorate("Tartarian Gate", 2, "", 0.0);
	ProjTowerDecor("Inferno Fire Ground");
	
	//--BUILD MISSILE --- 49
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_FrostBlast);
	ProjSetName("Frost Blast");
	ProjSetDesc("Freezes all units near the tower for 2 seconds");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(75);
	ProjRangeandLOS(19,19);
	ProjSetAmmoCost(100);
	ProjSetFireRate(5000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("frostgiantattack.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Frost Drift", 0, "", 1.0);
	ProjTowerDecor("Ice Sheet");
	
	//--BUILD MISSILE --- 50
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_EarthShatter);
	ProjSetName("Earth Shatter");
	ProjSetDesc("Tremors all units near the tower");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(50);
	ProjRangeandLOS(20,20);
	ProjSetAmmoCost(100);
	ProjSetFireRate(5000);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("implode start.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Cyclops", 3, "", 0.0);
	ProjTowerDecor("Tremor");
	
	//--BUILD MISSILE --- 50
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_TimeFreeze);
	ProjSetName("Time Freeze");
	ProjSetDesc("Freezes time in a large area, expensive to maintain");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(0);
	ProjRangeandLOS(28,28);
	ProjSetAmmoCost(100);
	ProjSetFireRate(1500);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("timeshift.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Osiris SFX", 1, "", 0.0);
	ProjTowerDecor("Deconstruct Building", "0,1,0,0,0,0");
	
	//--BUILD MISSILE --- 51
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Zombie);
	ProjSetName("Death Monument");
	ProjSetDesc("Summons the dead to attack any enemies nearby");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(9);
	ProjRangeandLOS(22,22);
	ProjSetAmmoCost(110);
	ProjSetFireRate(7500);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("ancestorsbirth.wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Skeleton", 0, "", 1.0);
	ProjTowerDecor("Wall Connector", "3,1,0,0,0,0", 1.5);
	
	//--BUILD MISSILE --- 52
	index = xAddDatabaseBlock(dProjectiles, true);
	xSetInt(dProjectiles, xPointer, index);
	ProjSetClass(PROJ_Barrage);
	ProjSetName("Volley tower");
	ProjSetDesc("Fires arrows down on the target, damaging nearby units");
	ProjSetProto("Spear");
	ProjSetAnim(2);
	ProjSetAnimPath("0,0,0,0,0,0");
	ProjSetSize(0.4);
	ProjSetDamage(50);
	ProjRangeandLOS(28,28);
	ProjSetAmmoCost(12);
	ProjSetFireRate(1800);
	ProjSetCount(1);
	ProjSetAngle(0);
	ProjSetSpeed(30.0);
	ProjSetSpecial(0);
	ProjSetSound("rainofarrows" + iModulo(3, (trTime())+1) + ".wav");
	//ProjSetBaseCosSin(0.996195, 0.087156); //the initial +cos/sin (+5)
	//ProjSetMoveCosSin(0.996195, -0.087156); //the incremental -cos/sin (-5 for +5,0,-5)
	//ProjAllowPassThrough();
	//ProjDeathEffect();
	ProjNoShoot();
	ProjRelicDecorate("Barrage", 1, "", 1.0);
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
