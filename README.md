# Capture the Flag

A Capture The Flag demo game made in Unreal Engine 5 in an effort to learn more about UE with a big focus on UI.

---

### High-level design UI features
There are three main widgets (composed of many different user-created widgets) each of them interacts with an appropriate MVVM viewmodel to update and display its data.

* **Main HUD:** Displays player information (health and stamina) as well as match information such as the match remaining time and each team's name and current score.
<br>![Main HUD](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExcDZncTQ5aTQyN3h1YXY0eTlkcWc5YjFqaHhyMTBxemltajNqaG1vNCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/BTpDM8QhLNpk69mYLC/giphy.gif)

* **Friend List Menu:** Displays a list of online and offline players which is fetched from a CSV file, player entries on this list get updated in real-time as their online status changes. The state change is simulated through a mocked Player Online Service.
<br>![Friend List Menu](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExYjIzanM2ODltdDFzZXBjd3NkNHZmem16aWQ3ZTZvdnNkeXR1MnE0OCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Nd79irwaPEvDLrgK6l/giphy.gif)

* **Friend Notification Toast:** When a friend's online status changes, a small pop-up notification window will notify of this change.
<br>![Friend pop-up](https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExN2IyOXF0ajd2anJmMGF5bnVpZzFveTkwaHgwOXdvdHZ6OGkyZG12bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/tOaGLwoWA7QPvR3lvN/giphy.gif)
---
### High-level gameplay features
There are two teams that can be configured with different names and colors, you can then assign instances of ATeamBase, AFlag, and ACaptureTheFlagCharacter to one of these teams to change the way they interact with each other.
 * A player on team A can only pick flags from team B.
 * A flag on team A can only be dropped on a base from team B.

When the match time ends, the team with the most points will be the winner, however, if there's a tie some additional time will be added, but a tie is still possible if both teams fail to score a point then.

---
### Automation testing implementation

This project uses Gauntlet and the UAT (Unreal Automation Tool) to implement automated tests. The automation project source code, which handles the execution command and configuration can be found [here](https://github.com/Narsell/UE5_GauntletAutomation).

The underlying logic of the test case scenario is [implemented in a child of the UGauntletTestController class](https://github.com/Narsell/UE5_CaptureTheFlag/tree/main/Source/CaptureTheFlag/AutomationTests) which allows the puppeteering of the state of the game to evaluate the desired outcome.

---


## Concepts and/or features worked on this project so far:

* UMG Widgets with C++.
* UMG Viewmodels using UE5's MVVM.
* UE5's C++ delegates (Non-dynamic, Multicast, and Dynamic)
* Best practices in the use of the Unreal Engine Game Framework (Game State, Game Mode, Game Instance, Player State, etc...)
* Others such as:
    * C++ Components.
    * Collision profiles, object types, etc...
    * Editor-only tools to facilitate gameplay design.
    * Timer Handles.

## Controls

* **WASD** to move
* Press **Tab** to open the friend list menu
