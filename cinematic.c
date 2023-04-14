rule CineJunction
highFrequency
inactive
{
	if((trTime()-cActivationTime) >= 1){
		PlayerChoice(1, "Play cinematic?", "Yes", 1, "No", 2);
		xsDisableSelf();
	}
}

rule SetupCine
highFrequency
inactive
{
	DontDestroyBelow = 1*(trGetNextUnitScenarioNameNumber()-1);
	AddCineText("You will need to defend yourself when night comes", 3000);
	AddCineText("Right click to garrison in a gaia tower", 3000);
	AddCineText("Once inside you will fire missiles at enemies", 3000);
	AddCineText("Different missiles are relics scattered throughout the map", 4000);
	AddCineText("Pick them up to use them, click them to find out more information", 5000);
	AddCineText("Firing missiles costs ammo, you'll need to mine gold to increase ammo", 5000);
	AddCineText("Capture cities in the day by killing all stationed guards", 5000);
	AddCineText("Then bring the rocket piece back to the rocket", 4000);
	AddCineText("You'll gain rewards as you bring more pieces back", 3500);
	AddCineText("It's best to do the cities in numerical order", 3500);
	AddCineText("If your citizen or the rocket dies - you lose", 3000);
	PlayCineDialogue();
	CreateRocket(20,20);
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(1, "Villager Atlantean Hero", 30, 30, 0);
	xSetPointer(dPlayerData, 1);
	xSetInt(dPlayerData, xUnitID, temp);
	CreatePillBox(40,40);
	xsDisableSelf();
	xsEnableRule("Cut1");
	xsEnableRule("Cut2");
	xsEnableRule("Cut3");
	xsEnableRule("Cut4");
	xsEnableRule("Cut5");
	xsEnableRule("Cut6");
	xsEnableRule("Cut7");
}

rule Cut1
inactive
highFrequency
{
	if(1*trQuestVarGet("Time1") == 0){
		xsDisableSelf();
		xUnitSelect(dPlayerData, xUnitID);
		trUnitMoveToPoint(40,1,40,-1,false);
	}
}

rule Cut2
inactive
highFrequency
{
	if(1*trQuestVarGet("Time2") == 0){
		xsDisableSelf();
		xUnitSelect(dTowers, xUnitID);
		trUnitConvert(1);
		xUnitSelect(dPlayerData, xUnitID);
		trImmediateUnitGarrison(""+xGetInt(dTowers, xUnitID));
	}
}

rule Cut3
inactive
highFrequency
{
	if(1*trQuestVarGet("Time3") == 0){
		xsDisableSelf();
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(cNumberNonGaiaPlayers, "Militia", 42,42,0);
		xsEnableRule("Cut35");
		AddUnitToDB(dEnemies, xUnitID, temp);
	}
}

rule Cut35
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 2){
		xsDisableSelf();
		xUnitSelect(dEnemies, xUnitID);
		trTechInvokeGodPower(0, "Bolt", vector(0,0,0), vector(0,0,0));
		xUnitSelect(dEnemies, xUnitID);
		trDamageUnit(1000);
	}
}

rule Cut4
inactive
highFrequency
{
	if(1*trQuestVarGet("Time4") == 0){
		xsDisableSelf();
		xUnitSelect(dTowers, xUnitID);
		trUnitConvert(0);
		xUnitSelect(dTowers, xUnitID);
		trUnitEjectContained();
		xUnitSelect(dPlayerData, xUnitID);
		trUnitMoveToPoint(44,1,44,-1,false);
		DeployRelic(44,44,2);
	}
}

rule Cut5
inactive
highFrequency
{
	if(1*trQuestVarGet("Time5") == 0){
		xsDisableSelf();
		xUnitSelect(dFreeRelics, xUnitID);
		trImmediateUnitGarrison(""+xGetInt(dPlayerData, xUnitID));
	}
}

rule Cut6
inactive
highFrequency
{
	if(1*trQuestVarGet("Time6") == 0){
		xsDisableSelf();
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Victory Marker", 48,48,0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Gold Mine");
		xUnitSelect(dPlayerData, xUnitID);
		trUnitDoWorkOnUnit(""+temp);
	}
}

rule Cut7
inactive
highFrequency
{
	if(1*trQuestVarGet("Time7") == 0){
		xsDisableSelf();
		unitTransform("Gold Mine", "Rocket");
		xUnitSelect(dPlayerData, xUnitID);
		trUnitMoveToPoint(44,1,44,-1,false);
		xUnitSelect(dPlayerData, xUnitID);
		trUnitChangeProtoUnit("Rocket");
		xUnitSelect(dTowers, xUnitID);
		trUnitChangeProtoUnit("Rocket");
		xUnitSelect(dFreeRelics, xUnitID);
		trUnitChangeProtoUnit("Rocket");
		
	}
}

/*
RESET ALL DATABASES POST CINE

dFreeRelics
dTowers

*/
