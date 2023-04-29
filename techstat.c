rule Technologies
active
highFrequency
{
	for(p = 1; <= cNumberNonGaiaPlayers){
		trTechSetStatus(p, 1, 4);
		trTechSetStatus(p, 2, 4);
		trTechSetStatus(p, 116, 4);
		trTechSetStatus(p, 126, 0);
		trTechSetStatus(p, 29, 4);
		trTechSetStatus(p, 353, 0);
		trTechSetStatus(p, 394, 0);
		trTechSetStatus(p, 510, 0);
		trTechSetStatus(p, 145, 0);
		trTechSetStatus(p, 144, 0);
		trTechSetStatus(p, 143, 0);
		trTechSetStatus(p, 379, 0);
		trTechSetStatus(p, 28, 4);
		trTechSetStatus(p, 30, 4);
		trTechSetStatus(p, 350, 4);
		trTechSetStatus(p, 27, 4);
		trTechSetStatus(p, 447, 4);
		trTechSetStatus(0, 304, 0);
		trTechSetStatus(p, 9, 0);
		trTechSetStatus(p, 101, 0);
		trTechSetStatus(p, 34, 0);
		trTechSetStatus(p, 10, 0);
		trTechSetStatus(p, 35, 0);
		
		for(n=930; > 0) {
			trForbidProtounit(p,kbGetProtoUnitName(n));
		}
	}
	//      trUnforbidProtounit(p, "Outpost");
	//  trUnforbidProtounit(1*p, "Oracle Hero");
	trTechSetStatus(0, 91, 4);
	xsDisableSelf();
}

void modifyBuildableProto(string proto = "", int p = 0) {
	trModifyProtounit(proto, p, 55, 4);
	trModifyProtounit(proto, p, 2, 9999999999999999999.0);
	trModifyProtounit(proto, p, 2, -9999999999999999999.0);
	trModifyProtounit(proto, p, 2, 0.0);
	for(i=16; <= 19) {
		trModifyProtounit(proto, p, i, 9999999999999999999.0);
		trModifyProtounit(proto, p, i, -9999999999999999999.0);
		trModifyProtounit(proto, p, i, 0.0);
	}
}

void SetEnemy(string proto = "", int hp = 1, float speed = 4.0, int attack = 1, int LOS = 0, int range = 1){
	modifyProtounitAbsolute(proto, cNumberNonGaiaPlayers, 0, hp);
	modifyProtounitAbsolute(proto, cNumberNonGaiaPlayers, 1, speed);
	modifyProtounitAbsolute(proto, cNumberNonGaiaPlayers, 2, LOS);
	modifyProtounitAbsolute(proto, cNumberNonGaiaPlayers, 11, range);
	modifyProtounitAbsolute(proto, cNumberNonGaiaPlayers, 27, attack);
	modifyProtounitAbsolute(proto, cNumberNonGaiaPlayers, 30, attack);
}

rule Stats
inactive
highFrequency
{
	trModifyProtounit("Dwarf", 0, 55, 4);
	//SKIN 1
	//---Class 1
	for(p = 1; <= cNumberNonGaiaPlayers){
		trModifyProtounit("Dwarf", p, 55, 4);
		trModifyProtounit("Animal Attractor", p, 55, 4);
		trModifyProtounit(""+YesChoiceUnitName, p, 55, 4);
		trModifyProtounit(""+YesChoiceUnitName, p, 1, -10);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, 0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, 0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 6, -100);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 16, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 17, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 18, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 19, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 16, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 17, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 18, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 19, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 55, 4);
		trModifyProtounit(""+NoChoiceUnitName, p, 1, -10);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, 0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, 0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 6, -100);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 16, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 17, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 18, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 19, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 16, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 17, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 18, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 19, -9999999999999999999.0);
	}
	for(p = 0; <= cNumberNonGaiaPlayers){
		modifyProtounitAbsolute("Tower", p, 5, 1);
		modifyProtounitAbsolute("Tower", p, 12, 0);
		modifyProtounitAbsolute("Tower", p, 13, 0);
		modifyProtounitAbsolute("Kronny Flying", p, 1, 30);
		modifyProtounitAbsolute("Farm", p, 16, 0);
		modifyProtounitAbsolute("Farm", p, 17, 0);
		modifyProtounitAbsolute("Farm", p, 18, Difficulty+2*25);
		modifyProtounitAbsolute("Farm", p, 19, 0);
		modifyProtounitAbsolute("Guild", p, 16, 0);
		modifyProtounitAbsolute("Guild", p, 17, Difficulty+2*250);
		modifyProtounitAbsolute("Guild", p, 18, 0);
		modifyProtounitAbsolute("Guild", p, 19, 0);
		modifyProtounitAbsolute("Tower", p, 16, 0);
		modifyProtounitAbsolute("Tower", p, 17, 1000-(Difficulty*200));
		modifyProtounitAbsolute("Tower", p, 18, 0);
		modifyProtounitAbsolute("Tower", p, 19, 0);
		modifyProtounitAbsolute("Temple", p, 16, 0);
		modifyProtounitAbsolute("Temple", p, 17, Difficulty+2*250);
		modifyProtounitAbsolute("Temple", p, 18, 0);
		modifyProtounitAbsolute("Temple", p, 19, 0);
		modifyProtounitAbsolute("Temple", p, 10, 1);
		modifyProtounitAbsolute("Sky Passage", p, 16, 0);
		modifyProtounitAbsolute("Sky Passage", p, 17, Difficulty+2*250);
		modifyProtounitAbsolute("Sky Passage", p, 18, 0);
		modifyProtounitAbsolute("Sky Passage", p, 19, 0);
		modifyProtounitAbsolute("Sky Passage", p, 12, 0);
		modifyProtounitAbsolute("Sky Passage", p, 31, 20);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 0, 1000-(Difficulty*200));
		modifyProtounitAbsolute("Manor", p, 16, 0);
		modifyProtounitAbsolute("Manor", p, 17, 100);
		modifyProtounitAbsolute("Manor", p, 18, 0);
		modifyProtounitAbsolute("Manor", p, 19, 0);
		modifyProtounitAbsolute("Manor", p, 5, 10);
		modifyProtounitAbsolute("Dock", p, 16, 0);
		modifyProtounitAbsolute("Dock", p, 17, 0);
		modifyProtounitAbsolute("Dock", p, 18, 0);
		modifyProtounitAbsolute("Dock", p, 19, 0);
		modifyProtounitAbsolute("Dock", p, 4, -1);
		modifyProtounitAbsolute("Dock", p, 55, 4);
		modifyProtounitAbsolute("Dock", p, 2, 0.0);
		modifyProtounitAbsolute("Helepolis", p, 0, 2000);
		modifyProtounitAbsolute("Helepolis", p, 1, 6);
		modifyProtounitAbsolute("Helepolis", p, 5, 1);
		modifyProtounitAbsolute("Helepolis", p, 13, 0);
		modifyProtounitAbsolute("Palace", p, 16, 0);
		modifyProtounitAbsolute("Palace", p, 17, Difficulty+2*1000);
		modifyProtounitAbsolute("Palace", p, 18, 0);
		modifyProtounitAbsolute("Palace", p, 19, 0);
		modifyProtounitAbsolute("Palace", p, 5, 0);
		modifyProtounitAbsolute("Villager Atlantean", p, 1, 4);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 1, 4);
		modifyProtounitAbsolute("Great Box Cart", p, 1, 4);
		modifyProtounitAbsolute("Palace", p, 4, 10);
		modifyProtounitAbsolute("Manor", p, 4, 10);
		modifyProtounitAbsolute("Farm", p, 4, 1);
		modifyProtounitAbsolute("Guild", p, 4, 10);
		trUnforbidProtounit(p, "Dock");
		modifyProtounitAbsolute("Oracle Scout", p, 16, 0);
		modifyProtounitAbsolute("Oracle Scout", p, 17, Difficulty+1*500);
		modifyProtounitAbsolute("Oracle Scout", p, 18, 0);
		modifyProtounitAbsolute("Oracle Scout", p, 19, 0);
		modifyProtounitAbsolute("Automaton", p, 16, 0);
		modifyProtounitAbsolute("Automaton", p, 17, Difficulty+1*500);
		modifyProtounitAbsolute("Automaton", p, 18, 0);
		modifyProtounitAbsolute("Automaton", p, 19, 0);
		modifyProtounitAbsolute("Satyr", p, 16, 0);
		modifyProtounitAbsolute("Satyr", p, 17, Difficulty+1*500);
		modifyProtounitAbsolute("Satyr", p, 18, 0);
		modifyProtounitAbsolute("Satyr", p, 19, 0);
		modifyProtounitAbsolute("Argus", p, 16, 0);
		modifyProtounitAbsolute("Argus", p, 17, Difficulty+1*500);
		modifyProtounitAbsolute("Argus", p, 18, 0);
		modifyProtounitAbsolute("Argus", p, 19, 0);
		modifyProtounitAbsolute("Oracle Scout", p, 6, 0);
		modifyProtounitAbsolute("Automaton", p, 6, 0);
		modifyProtounitAbsolute("Satyr", p, 6, 0);
		modifyProtounitAbsolute("Argus", p, 6, 0);
	}
	modifyProtounitAbsolute("Bolt Strike", 0, 27, 0);
	modifyProtounitAbsolute("Bolt Strike", 0, 28, 0);
	modifyProtounitAbsolute("Bolt Strike", 0, 29, 0);
	modifyProtounitAbsolute("Fortress", 0, 13, 0);
	modifyProtounitAbsolute("Migdol Stronghold", 0, 13, 0);
	modifyProtounitAbsolute("Hill Fort", 0, 13, 0);
	modifyProtounitAbsolute("Titan Atlantean", 0, 2, 1);
	modifyProtounitAbsolute("Meteor", 0, 2, 0);
	modifyProtounitAbsolute("Helepolis", 0, 1, 0);
	modifyProtounitAbsolute("Helepolis", 0, 2, 0);
	modifyProtounitAbsolute("Helepolis", 0, 0, 2000);
	modifyProtounitAbsolute("Helepolis", 0, 5, 1);
	modifyProtounitAbsolute("Helepolis", 0, 13, 0);
	modifyProtounitAbsolute("Catapult", cNumberNonGaiaPlayers, 32, 100);
	modifyProtounitAbsolute("Catapult", cNumberNonGaiaPlayers, 0, 1000);
	modifyProtounitAbsolute("Catapult", cNumberNonGaiaPlayers, 2, 30);
	modifyProtounitAbsolute("Catapult", cNumberNonGaiaPlayers, 11, 30);
	trModifyProtounit("Hero Greek Jason", cNumberNonGaiaPlayers, 0, 200);
	trModifyProtounit("Hero Greek Jason", cNumberNonGaiaPlayers, 27, 20);
	trModifyProtounit("Hero Greek Jason", cNumberNonGaiaPlayers, 29, 20);
	trModifyProtounit("Hero Greek Odysseus", cNumberNonGaiaPlayers, 0, 250);
	trModifyProtounit("Hero Greek Odysseus", cNumberNonGaiaPlayers, 31, 20);
	trModifyProtounit("Hero Greek Odysseus", cNumberNonGaiaPlayers, 32, 30);
	trModifyProtounit("Hero Greek Bellerophon", cNumberNonGaiaPlayers, 0, 400);
	trModifyProtounit("Hero Greek Bellerophon", cNumberNonGaiaPlayers, 27, 40);
	trModifyProtounit("Hero Greek Bellerophon", cNumberNonGaiaPlayers, 29, 40);
	trModifyProtounit("Hero Greek Hippolyta", cNumberNonGaiaPlayers, 0, 500);
	trModifyProtounit("Hero Greek Hippolyta", cNumberNonGaiaPlayers, 31, 50);
	trModifyProtounit("Hero Greek Hippolyta", cNumberNonGaiaPlayers, 32, 50);
	trModifyProtounit("Hero Greek Polyphemus", cNumberNonGaiaPlayers, 0, 750);
	trModifyProtounit("Hero Greek Polyphemus", cNumberNonGaiaPlayers, 27, 100);
	trModifyProtounit("Hero Greek Polyphemus", cNumberNonGaiaPlayers, 29, 100);
	trModifyProtounit("Circe", cNumberNonGaiaPlayers, 0, 750);
	trModifyProtounit("Minion", cNumberNonGaiaPlayers,8, 1000);
	trRateConstruction(5);
	modifyProtounitAbsolute("Minion", cNumberNonGaiaPlayers, 0, 100);
	modifyProtounitAbsolute("Ulfsark", cNumberNonGaiaPlayers, 0, 100);
	modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 0, 100);
	xsDisableSelf();
	xsEnableRule("ChickenBlood");
}

rule ChickenBlood
inactive
highFrequency
{
	for(a = 1; < 100){
		trTechSetStatus(cNumberNonGaiaPlayers, 451, 4);
	}
}



/*
The field ids are as follows:
Hitpoints=0
Speed=1
LOS=2
Train Points=3
Build Points=4
Max Contained=5
Population Count=6
Pop Cap Addition=7
Lifespan=8
Recharge Time=9
Build Limit=10
Range=11
Minimum Range=12
Num Projectiles=13
Healing Rate=14
Healing Range=15
Cost Gold=16
Cost Wood=17
Cost Food=18
Cost Favor=19
Carry Capacity Gold=20
Carry Capacity Wood=21
Carry Capacity Food=22
Carry Capacity Favor=23
Armor Hack=24
Armor Pierce=25
Armor Crush=26
Hand Attack Hack=27
Hand Attack Pierce=28
Hand Attack Crush=29
Ranged Attack Hack=30
Ranged Attack Pierce=31
Ranged Attack Crush=32
Movetype = 55
*/
