# Scoot-Scoot-Nook-Nook

## Introduction
This is my custom project for my CS/EE 120B - Introduction to Embedded Systems class at the University of California, Riverside. This project is called Scoot-Scoot, Nook-Nook, and it is a game similar to Space Shooters. To engineer this game, I applied the critical knowledge and skills I gained from this class, which includes the use of microcontrollers and breadboard, capturing state machines in C, and hardware configuration and troubleshooting.

## Description
When the game first starts, a main menu screen displays the title and the difficulty levels. Once a difficulty is selected, the game screen comes on, showing the "asteroids" and the player's "space ship" with a bullet on top of it. The asteroids in both levels shift at the same rate, but in easy mode the asteroid are much closer than medium mode. To win the game, player needs to move (only horizontally) and destroy all the asteroids. Once all asteroids are destroyed, a "YOU WIN!" screen will appear to indicate player's victory.

![alt text](https://github.com/vtruo009/Scoot-Scoot-Nook-Nook/blob/master/Images/Main%20Menu.jpg] "Main Menu")

## User Guide
* Controls
	* Use 2-axis joystick to control ship (blue circle)
	* Use attack button to shoot bullet (yellow circle)
	* Use reset button to restart game at anytime (red circle)
* Rules
	* Can only shoot one bullet at a time
	* Clear all asteroids to win
	* Wait until bullet hits asteroid or disappears to move and shoot again

![alt text](https://github.com/vtruo009/Scoot-Scoot-Nook-Nook/blob/master/Images/Setup.jpg "Seteup")

## Technologies and Components
* Nokia 5110 LCD Screen - used to display game
* 2-Axis Joystick - used for movement control
* Buttons - used to attack and reset
* Atmega1284 Microcontroller
* IEEE Programming Chip
* Breadboard
* Atmel Studio 7

## Bugs & Imperfections
A problem occurred with the timer that causes a shadow to follow the player's ship when moving around the screen. An attempt was made to fix the problem but that caused a shadow to follow the asteroids. In addition, the bullet follows the player's ship if player decides to move while the bullet is traveling up. Thus, player has to wait until bullet hits target or disappears to prevent altering the bullet's path.

## Future Plans
I will attempt to fix the shadow issue by fixing the timer. Also, I will redesign the game logic to allow player to shoot multiple bullets at a time with each bullet being able to travel in an independent path.

## Demo Video
https://www.youtube.com/watch?v=7XM2AXjAvqw
