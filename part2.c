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
		trCounterAddTime("rockethealth", -100, -20000, "Rocket Completion: " + WonderHP + "/100", -1);
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
		playSound("x_win.wav");
		xsDisableSelf();
		trPlayerKillAllUnits(cNumberNonGaiaPlayers);
		trPlayerKillAllBuildings(cNumberNonGaiaPlayers);
		NextDay = trTime()+1000;
		NextNight = trTime()+1000;
		LunchTime = trTime()+1000;
		TeaTime = trTime()+1000;
		trSetLighting("default", 6);
		xsEnableRule("EndGameWin");
	}
}

rule EndGameWin
highFrequency
inactive
{
	if (trTime() > cActivationTime + 5) {
		trShowWinLose("TEST VERSION DO NOT HOST", "xwin.wav");
		for(p=1 ; < cNumberNonGaiaPlayers){
			trSetPlayerWon(p);
		}
		EndChats();
		xsDisableSelf();
		trEndGame();
	}
}
