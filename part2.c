rule Part2
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 7){
		trOverlayText("Repair the rocket with wood to win!", 7);
		Part = 2;
		trUnitSelectByQV("RocketUnit");
		if(trUnitPercentDamaged() < 70){
			trDamageUnitPercent(10);
		}
		for(p = 1; < cNumberNonGaiaPlayers){
			modifyProtounitAbsolute("Wonder SPC", p, 16, 0);
			modifyProtounitAbsolute("Wonder SPC", p, 17, 100000);
			modifyProtounitAbsolute("Wonder SPC", p, 18, 0);
			modifyProtounitAbsolute("Wonder SPC", p, 19, 0);
		}
		xsDisableSelf();
		xsEnableRule("RocketHPCounter");
		xsEnableRule("RocketWin");
		trUnitSelectByQV("RocketUnit");
		trUnitHighlight(10, false);
		trRateConstruction(1);
		xsEnableRule("Part2Text");
	}
}

rule Part2Text
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 7){
		if(Day){
			trOverlayText("Watch out for bomber attacks during the day!", 7);
			xsDisableSelf();
		}
	}
	
}

rule RocketHPCounter
inactive
highFrequency
{
	if(Part == 2){
		trUnitSelectByQV("RocketUnit");
		WonderHP = 100-trUnitPercentDamaged();
		trCounterAbort("rockethealth");
		trCounterAddTime("rockethealth", -100, -20000, "</color>Rocket Completion: " + WonderHP + "/100", -1);
	}
}

rule RocketWin
inactive
highFrequency
{
	trUnitSelectByQV("RocketUnit");
	if(trUnitPercentDamaged() == 0){
		Part = 3;
		xsDisableRule("RocketHPCounter");
		trCounterAbort("rockethealth");
		vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
		trOverlayText("The rocket is ready for launch!", 4);
		xsDisableSelf();
		trPlayerKillAllUnits(cNumberNonGaiaPlayers);
		trPlayerKillAllBuildings(cNumberNonGaiaPlayers);
		NextDay = trTime()+1000;
		NextNight = trTime()+1000;
		LunchTime = trTime()+1000;
		TeaTime = trTime()+1000;
		trSetLighting("default", 6);
		xsEnableRule("RocketLaunchSequence");
		for(a = 11; <= 24){
			trUnitSelectByQV("LaunchPadEC"+a);
			trMutateSelected(kbGetProtoUnitID("Rocket"));
		}
	}
}

rule EndGameWin
highFrequency
inactive
{
	trCounterAbort("clock");
	trShowWinLose("TEST VERSION DO NOT HOST", "xwin.wav");
	for(p=1 ; < cNumberNonGaiaPlayers){
		trSetPlayerWon(p);
	}
	EndChats();
	xsDisableSelf();
	trEndGame();
}


rule RocketLaunchSequence
highFrequency
inactive
{
	if (trTime() > cActivationTime + 5) {
		xsDisableSelf();
		FloatingUnitAnimIdle("Implode Sphere Effect", getMapSize()/2,0,getMapSize()/2,0,0,0);
		AddUnitToDB(dRocket, xUnitID, 1*trQuestVarGet("QVHero"));
		trUnitSelectByQV("QVRelic");
		trSetSelectedUpVector(0,0,0);
		trUnitSelectByQV("QVHero");
		trSetSelectedUpVector(0,0,0);
		xsEnableRule("Launch");
		trCounterAbort("clock");
	}
}

rule Launch
highFrequency
inactive
{
	if(trTimeMS() > 1*trQuestVarGet("LaunchTimer")){
		trQuestVarSet("LaunchTimer", trTimeMS()+10);
		vector unit = vector(0,0,0);
		for(a = xGetDatabaseCount(dRocket) ; > 0){
			xDatabaseNext(dRocket);
			unit = kbGetBlockPosition(""+xGetInt(dRocket, xUnitID));
			xUnitSelect(dRocket, xUnitID);
			trUnitTeleport(xsVectorGetX(unit), xsVectorGetY(unit)+yc, xsVectorGetZ(unit));
		}
		yc = yc+0.01;
		if(yc > 1){
			xsDisableSelf();
			xsEnableRule("EndGameWin");
		}
	}
}
