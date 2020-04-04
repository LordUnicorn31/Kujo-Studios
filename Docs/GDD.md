# GAME DESIGN DOCUMENT (GDD)


# Game pillars

This game has 3 main game pillars:

Exploration: The player is meant to explore all the map and discover all the places they can acces too. At some points of the game the player will be forced to go to specific areas of the map to do side quests.

Strategy: Strategy is the most important pillar in any RTS game and so it is in this game too. This game is much more about using the brain and knowing what to do in each moment than having great physical skills.

Mining & farming: This game has the intention of having to farm and mine the map in order to be able to increase your base and units to be able to reach the main goal of the game.


# Story

You are the captain in a spaceship. You and your team have been raiding planets to get ores for years now, however, you just had an accident and landed in a mysterious planet. In order to escape you will need to gather resources from the planet and build a new starship that helps you get out of that planet. But be careful! the population of the planet have discovered you, and they don't like the idea of having a bunch of strangers raiding their planet and stealing their ores, so you better protect yourself in order to achieve your main goal.


# Controls

Mouse: Move around the map.

Left mouse button: Select (units, building, menus, basically select everything you can press).

Right mouse button: Move units (When a unit is selected and you press right mouse button somewhere, the unit will move to that point).

Mouse button rudder: Zoom out/Zoom in.

# Gameplay features

Unit automation: This game has an automatic system that makes the collectors collect and transport materials on their own, without having to tell them to do so. This is basically because we want the player to have the experience of only focusing on mining in the early stage of the game and not focusing that much on the late game (where the player will have a lot of resources and won't be focused on transporting resources to the base).

Unit counter: This game has a counter system for the fighting units. this means that each unit goes well against another unit and bad against another unit (like the rock, paper, scissors game). By this we amplify the startegy of the gameplay and make the player think what unit is better in any specific given situation.

Fog of war: This game has a fog of war system. It means that a part of the map is shown (where the player starts) and the other is unseen. This mechanics allows us to surprise and make the player explore. The idea is that by putting fog of war the player will have to explore places to find resources and he will get attacked by the enemy from surprising angles.

Evolution: In this game the player must notice a change between the first minute he plays and the minute 20 of game. This means that the game has to evolve, starting from a point where decisions don't matter (farming phase) to a point where you have to get an army to destroy the enemies and escape. It is essential that the player feels he has gotten stronger while playing.


# Maps

There are 2 different maps. The first one is the main map which represents the 90% of the game. The map is a representation of a part of the planet where the player is. This map (futuristic style) is where the action will develop and the player will build all his base.

The second map is a special map for some quests. This map is a cave in which the player can enter in order to complete missions or find resources. The idea of this map is that it will work as some kind of mini-game map because of the change in style from the main map.


# Buildings

This game has a building system in which every building matters and has its own function on the game. The main buildings are as they follow.

Spaceship: It is your base, where everything starts and it is given to you at the beggining of the game. (HP: 5000)

Gold mine:Tthe gold mine is the place where you can extract gold to be able to build and buy stuff. (HP: 1500) (time: 30s)

Ore mine: The ore mine is the place where ore is extracted in order to be able to build buildings and create weapons. (HP: 1500) (time: 30s)
Cable: It connects the electric power plants with the rest of building. (HP: 750) 

Electric power plant: the electric power plant is the building that generates electricity. (HP: 3000) (Energy: 100) (time: 40s) 

Weapon industry: the weapon industry is where all the main weapons are created. (HP: 3500) (time: 50s) (items investigation time: 60s)

spaceship factory: The spaceship factory is the place where all the basic units are recruited. (HP: 3500) (time: 50s) (production time: 30s)

Special factory: The special factory is the building in which the special units are recruited. (HP: 4000) (time: 60s) (production time: 60s)


# Units

Units can be and should be separated in 3 big groups.

## Collectors
The collectors are robots that work on the gold and ore mines, their job is to collect gold and ores and then bring them to the spaceship. (unit cost: 50 gold) (unit value 1:1) (speed: 100) (weight: 20gold)

## Basic units (recruited at the barracks)

This units are the most basic warriors and the ones that will most likely be the backbone of your army. Their cost is not very expensive and the number of units you can recruit is more than the one for the special units. There are 3 basic units:

Lazership: Spaceships that shoot a single beam. (unit cost: 100 gold) (unit value 1:1) (HP: 100) (attack:40) (range: 200) (speed: 100)

Dualship: Spaceships that shoot 2 beams. (unit cost: 150 gold) (unit value 1:1) (HP: 100) (attack: 60 total, 30 each beam) (range 200) (speed: 100)

Cannonship: Spaceships that shoot a beam that goes through enemies (unit cost: 300 gold) (unit value 1:2) (HP: 120) (attack:50) (range 250) (speed: 90)

## Special units

This units can only be recruited in the special barracks. they are far more expensive than the basic units and the maximum number of units you can recruit is way lower than the basic units ones. The special units are:

Laser-Shooters: Spaceship that shoots beams in a circular area. (unit cost: 500 gold) (unit value 1:5) (HP: 180) (attack: 50) (range: 350)


# Items

Weapons are the most important thing when recruiting units. Depending on the weapons you investigate and create you will be able to recruit one kind of unit or another. This is why in this game items are an important part of the strategy. Here is the list of the items:

Single beam: The single beam is the weapon that the lazerships shoot.

Double beam: the double beam is the weapon that the dualship shoots. 

Cannon: The cannon beam is the weapon that the cannonship shoots. Stats 

Circular beams: the circular beam is the projectile the Laser-Shooters shoot. Stats 

Gold: Can be found in gold mines.

Ore: Can be found in ore mines.

Electricity: It is generated in the electric power plant.


# AI

## Enemies in the main map

The AI has the same units the player has. Thanks to this we are able to make the game fair in any aspect and make it feel like the player is playing against another human and not a machine. 

All the enemies have the same stats.

## Enemies in the dungeons

Goblins: Globins have a medium damage. (HP: 100) (attack: 40) (range: 20) (speed: 100)

Minotaur: Slow enemies that have tons of damage. (HP: 150) (attack: 60) (range: 30) (speed: 60)

Sipders: Fast enemies that have low damage. (HP: 70) (attack: 25) (speed: 120)

# Quests & quests solutions

As quests are one of the most important things in any RTS games, we decided to create a secondary quests systems that will help the player in the main goal of the game but won't have any punish if the player doesn't do them.

1st Quest: The player is given the quest of invading 1 enemy village and raid its resources.

Solution: Go to the village and attack their main building so the village gets instantly invaded.


2nd Quest: Steal a map from the enemy. 

Solution: Go to an enemy factory. Destroy it and then the map will be given to you automatically.


3rd Quest: Go to the cave with the map you achieved in the first quest go to the cave in the map and get the special ore.

Solution: Fight the enemies on the front door, enter, dodge all the enemies (the enemies inside the mine can't be fought), go to the last room and get the ore.
