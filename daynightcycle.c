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
		trSetLighting("default", 50);
		TeaTime = trTime()+50;
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
		trSetLighting("Dusk", 60);
		NextNight = trTime()+60;
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
					Date = Date+1;
					//Stronger enemies
				}
				NextNightAttack = trTime()+NightInterval;
				if(Date == 1){
					trQuestVarSetFromRand("temp", 1, 2);
					for(a = 0; < cNumberNonGaiaPlayers*2){
						NightAttack("Militia");
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
				if(Date == 3){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*2){
							NightAttack("Minotaur");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*2){
							NightAttack("Centaur");
						}
					}
					SpawnBomber("Hoplite");
					if(Part == 2){
						for(a = 1; <= cNumberNonGaiaPlayers*2){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 4){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Minotaur");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Centaur");
						}
					}
					SpawnBomber("Hoplite");
					SpawnBomber("Hoplite");
					if(Part == 2){
						for(a = 1; <= cNumberNonGaiaPlayers*2){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 5){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*5){
							NightAttack("Cyclops");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Manticore");
						}
					}
					if(Part == 2){
						for(a = 1; <= cNumberNonGaiaPlayers*2){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 6){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*6){
							NightAttack("Colossus");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*6){
							NightAttack("Medusa");
						}
					}
					if(Part == 2){
						for(a = 1; <= cNumberNonGaiaPlayers*2){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 7){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*5){
							NightAttack("Hero Greek Jason");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*6){
							NightAttack("Hero Greek Odysseus");
						}
					}
					if(Part == 2){
						for(a = 1; <= cNumberNonGaiaPlayers*2){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 8){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*7){
							NightAttack("Hero Greek Bellerophon");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*8){
							NightAttack("Hero Greek Hippolyta");
						}
					}
					if(Part == 2){
						for(a = 1; <= cNumberNonGaiaPlayers*3){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date == 9){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*10){
							NightAttack("Circe");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*10){
							NightAttack("Hero Greek Polyphemus");
						}
					}
					if(Part == 2){
						for(a = 1; <= cNumberNonGaiaPlayers*3){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Date >= 10){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Catapult");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*12){
							NightAttack("Hero Greek Polyphemus");
							NightAttack("Circe");
						}
					}
					if(Part == 2){
						for(a = 1; <= cNumberNonGaiaPlayers*4){
							SpawnBomber("Hero Norse");
						}
					}
				}
				if(Part == 2){
					Date = Date-1;
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
