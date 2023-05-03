rule BeginDay
inactive
highFrequency
{
	if(trTime() >= NextDay){
		trCounterAbort("clock");
		trCounterAddTime("clock", 180, 0, "<color={PlayerColor(0)}>Night Time", -1);
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
		//[DIFFICULTY CHECK]
		xsEnableRule("NightClearout");
		if(Date == 1){
			xsEnableRule("Helper01");
		}
		if(Date == 2){
			xsEnableRule("Helper03");
		}
		if(Part == 2){
			//Send bombers
			for(a = 1; <= Date){
				SpawnBomber("Hero Norse");
			}
		}
	}
}

rule Lunch
inactive
highFrequency
{
	if(trTime() >= LunchTime){
		xsDisableSelf();
		trSetLighting("default", 80);
		TeaTime = trTime()+80;
		xsEnableRule("DinDins");
		if(Part == 2){
			//Send bombers
			for(a = 1; <= Date){
				SpawnBomber("Hero Norse");
			}
		}
	}
}

rule DinDins
inactive
highFrequency
{
	if(trTime() >= TeaTime){
		xsDisableSelf();
		trSetLighting("Dusk", 90);
		NextNight = trTime()+90;
		xsEnableRule("BeginNight");
		if(Part == 2){
			//Send bombers
			for(a = 1; <= Date){
				SpawnBomber("Hero Norse");
			}
		}
	}
}

rule BeginNight
inactive
highFrequency
{
	if(trTime() >= NextNight){
		trCounterAbort("clock");
		trCounterAddTime("clock", 120, 0, "<color={PlayerColor(0)}>Day Time", -1);
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
		if(Part == 2){
			NightInterval = 30;
			//Extra attack when building
		}
		NextNightAttack = trTime()+5;
		if(Date == 1){
			xsEnableRule("Helper02");
		}
	}
}

rule NightAttacksLoop
active
highFrequency
{
	if(AllowEnemies){
		if(trTime() > NextNightAttack){
			if(Day == false){
				if(Part == 2){
					if(Difficulty > 1){
						Date = Date+1;
					}
					//Stronger enemies
				}
				NextNightAttack = trTime()+NightInterval;
				if(Date == 1){
					trQuestVarSetFromRand("temp", 1, 2);
					for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*2){
						NightAttack(Enemy0);
					}
					
				}
				if(Date == 2){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*5){
							NightAttack(Enemy1);
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*5){
							NightAttack(Enemy2);
						}
					}
				}
				if(Date == 3){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*2){
							NightAttack(Enemy3);
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*2){
							NightAttack(Enemy4);
						}
					}
					SpawnBomber(Enemy1);
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 4){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*4){
							NightAttack(Enemy3);
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*4){
							NightAttack(Enemy4);
						}
					}
					SpawnBomber(Enemy1);
					SpawnBomber(Enemy1);
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 5){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*5){
							NightAttack(Enemy5);
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*4){
							NightAttack(Enemy6);
						}
					}
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 6){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*6){
							NightAttack(Enemy7);
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*6){
							NightAttack(Enemy8);
						}
					}
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 7){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*5){
							NightAttack("Hero Greek Jason");
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*6){
							NightAttack("Hero Greek Odysseus");
						}
					}
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 8){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*7){
							NightAttack("Hero Greek Bellerophon");
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*8){
							NightAttack("Hero Greek Hippolyta");
						}
					}
					SpawnBomber("Hero Norse");
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)*3){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 9){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*10){
							NightAttack("Circe");
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*10){
							NightAttack("Hero Greek Polyphemus");
						}
					}
					SpawnBomber("Hero Norse");
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)*3){
							SpawnBomber("Hero Greek Jason");
						}
					}
				}
				if(Date >= 10){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*5){
							NightAttack("Catapult");
						}
					}
					else{
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*12){
							NightAttack("Hero Greek Polyphemus");
							NightAttack("Circe");
						}
					}
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)*3){
							SpawnBomber("Hero Greek Jason");
						}
					}
				}
				if(Date >= 12){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < (cNumberNonGaiaPlayers-PlayersDead)*1){
							NightAttack("Guardian XP");
						}
					}
					if(Part == 2){
						for(a = 1; <= (cNumberNonGaiaPlayers-PlayersDead)*3){
							SpawnBomber("Hero Greek Bellerophon");
						}
					}
				}
				if(Part == 2){
					if(Difficulty > 1){
						Date = Date-1;
					}
					//Stronger enemies reset
				}
			}
		}
	}
}

rule NightClearout
inactive
highFrequency
{
	int anim = 0;
	for(a = xGetDatabaseCount(dEnemies); >0){
		xDatabaseNext(dEnemies);
		if(xGetBool(dEnemies, xStationary) == false){
			anim = kbUnitGetAnimationActionType(kbGetBlockID(""+xGetInt(dEnemies, xUnitID)));
			if(anim == 9){
				xUnitSelect(dEnemies, xUnitID);
				trUnitDestroy();
			}
		}
	}
	xsDisableSelf();
}
