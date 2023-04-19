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
				}
				if(Date == 5){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Cyclops");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Manticore");
						}
					}
				}
				if(Date == 6){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Colossus");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Medusa");
						}
					}
				}
				if(Date == 7){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Hero Greek Jason");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Hero Greek Odysseus");
						}
					}
				}
				if(Date == 8){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Hero Greek Bellerophon");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Hero Greek Hippolyta");
						}
					}
				}
				if(Date == 9){
					trQuestVarSetFromRand("temp", 1, 2);
					if(1*trQuestVarGet("temp") == 1){
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Circe");
						}
					}
					else{
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Hero Greek Polyphemus");
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
						for(a = 0; < cNumberNonGaiaPlayers*4){
							NightAttack("Hero Greek Polyphemus");
						}
					}
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
