# ProjectApollo

Utilizing the CheekyFPS project as a base, this project serves as my study for level design and AI Perception.
My goal is to have something small but focused by the late summer to publish onto stores as an Early Access title with a prologue 1.0 version available by the end of the year.

## Goals for the project

- AI can react to player actions (shot out lights, thrown objects, etc)
- At least 3 levels that grow from small and linear but focused, to large and open ended - as a starting point
- Using raytracing along with a dynamic lighting system to further immersion, interaction
- Seamless transition from each level, using Level Streaming


## Currently Implemented Features
- AI Perception that can detect the player, react to auditory stimulus (footsteps)
- Basic weapon system (player and AI can fire and reload, but only two weapons implemented)
- Thrown projectiles that the player can use to attack or defend with
- All features from [CheekyFPS](https://github.com/DaveFace/CheekyFPS) as of 11/09/2020

## Stretch goals
- Generic VO for player and AI, BGM
- *Plot???*

## Getting Started
This project is *mainly* based in Blueprint but some AI features and other lower level systems require C++ programming.

I have tried to stick to [Allar's fantastic style guide](https://github.com/Allar/ue4-style-guide), at least where it comes to asset naming conventions.


## Contributing, Bug Reports, and Feature Requests
Any suggestions or requestions you can send to me on Discord: InfinityStarlight#9795 or email bcjones2016@gmail.com or create a issue here on GitHub.


## Update History
**12/27/2020** : First Commit - Weapons and Basic AI implemented
**01/21/2020** : Save system inital implementation - Player's inventory, position and enemy status and other things is tracked and updated upon saving and loading to/from disk. I'm also dabbling with Raytracing GI and reflections as part of the lighting system.


## Authors

* **Brandon Jones** - [Portfolio](https://professionaljones.com/) / [LinkedIn](https://www.linkedin.com/in/professionaljones16/)


## Acknowledgments

- Special Thanks to **Dave Watts** - [ArtStation](https://www.artstation.com/daveface) / [Twitter](https://twitter.com/therealdaveface)
- Example footstep sounds from https://freesound.org/
