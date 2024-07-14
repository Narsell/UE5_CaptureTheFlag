# Capture the Flag

A Capture The Flag demo game made in Unreal Engine 5 in an effort to learn more about UE with a big focus on UI.

### High level design UI features
There are three main widgets (composed of many different user created widgets) each of them interacts with an appropriate MVVM viewmodel to update and display its data.

* **Main HUD:** Displays player information (health and stamina) as well as match information such as the match remaining time and each team's name and current score.
<br>![Main HUD](https://media.discordapp.net/attachments/862531972748673024/1261868790006808686/image.png?ex=66948663&is=669334e3&hm=e3c44e8080026f9c9b5bec283aa77bf0ce99194edeac19cc4c3ccbceefbebcdc&=&format=webp&quality=lossless&width=550&height=324)

* **Friend List Menu:** Displays a list of online and offline players which is fetched from a CSV file, player entries on this list get updated in real-time as their online status changes. The state change is simulated through a mocked Player Online Service.
<br>![Friend List Menu](https://media.discordapp.net/attachments/862531972748673024/1261869315079012392/UnrealEditor_PKuxNxSA24.gif?ex=669486e1&is=66933561&hm=fecf42c597a3e6595c89ef189b4572c93aa971d852c8fe5e1b4500116ec75ca1&=)

* **Friend Notification Toast:** When a friend's online status changes, a small pop-up notification window will notify of this change.
<br>![Friend pop-up](https://media.discordapp.net/attachments/862531972748673024/1261870908075806801/UnrealEditor_bWLzTE5Bej.gif?ex=6694885c&is=669336dc&hm=9e95a5e14c6284209ea69a273536a2dfb75f4f7ef1144f46015f5f5dc07bddcb&=)

### High level gameplay features
There are two teams that can be configured with different names and colors, you can then assign instances of ATeamBase, AFlag and, ACaptureTheFlagCharacter to one of these teams to change the way they interact with each other.
 * A player on team A can only pick flags from team B.
 * A flag on team A can only be dropped on a base from team B.

When the match time ends, the team with the most points will be the winner, however if there's a tie some additional time will be added, but a tie is still possible if both teams fail to score a point then.


## Concepts and/or features worked on this project so far:

* UMG Widgets with C++.
* UMG Viewmodels using UE5's MVVM.
* UE5's C++ delegates (Non-dynamic, Multicast, and Dynamic)
* Best practices in the use of the Unreal Engine Game Framework (Game State, Game Mode, Game Instance, Player State, etc...)
* Others such as:
    * C++ Components.
    * Collision profiles, object types, etc...
    * Editor only tools to facilitate gameplay design.
    * Timer Handles.

## Controls

* **WASD** to move
* Press **Tab** to open the friend list menu
