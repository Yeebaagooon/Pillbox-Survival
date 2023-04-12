rule BeginDay
inactive
highFrequency
{
	if(trTime() >= NextDay){
		Date = Date+1;
		trSetLighting("Dawn", 10);
		Day = true;
		LunchTime = trTime()+10;
		xsDisableSelf();
		xsEnableRule("Lunch");
		trOverlayText("Day " + Date, 4.0);
		playSound("restorationbirth.wav");
		playSound("recreation.wav");
		playSound("herorevived.wav");
	}
}

rule Lunch
inactive
highFrequency
{
	if(trTime() >= LunchTime){
		xsDisableSelf();
		trSetLighting("default", 50);
		TeaTime = trTime()+50;
		xsEnableRule("DinDins");
	}
}

rule DinDins
inactive
highFrequency
{
	if(trTime() >= TeaTime){
		xsDisableSelf();
		trSetLighting("Dusk", 60);
		NextNight = trTime()+60;
		xsEnableRule("BeginNight");
	}
}

rule BeginNight
inactive
highFrequency
{
	if(trTime() >= NextNight){
		xsDisableSelf();
		trSetLighting("Night", 10);
		NextNight = trTime()+240;
		NextDay = trTime()+120;
		Day = false;
		xsEnableRule("BeginDay");
		trOverlayText("Night " + Date, 4.0);
		playSound("\xpack\xcinematics\intro\magicvoice.mp3");
		playSound("eclipsebirth.wav");
		if(NightInterval == 0){
			NightInterval = 40;
		}
		NextNightAttack = trTime()+5;
	}
}

rule NightAttacksLoop
active
highFrequency
{
	if(AllowEnemies){
		if(trTime() > NextNightAttack){
			if(Day == false){
				NextNightAttack = trTime()+NightInterval;
				debugLog("SPAWN");
				if(Date == 1){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*5){
							NightAttack("Militia");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*5){
							NightAttack("Toxotes");
						}
					}
				}
				if(Date == 2){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*5){
							NightAttack("Hoplite");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*5){
							NightAttack("Toxotes");
						}
					}
				}
			}
		}
	}
}
