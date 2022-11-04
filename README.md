# The Seed Engine
The Seed Engine is unfinished, we are working on this during the assigment of *Game Engine Development* for the CITM degree in Video Game Design and Development.

The Seed Engine is a game engine developed in C++ using the external libraries: 

&emsp; -&emsp;*[SDL2](https://www.libsdl.org/)*

&emsp; -&emsp;*[OpenGL](https://www.opengl.org/)* 

&emsp; -&emsp;*[ImGui](https://github.com/ocornut/imgui)*

&emsp; -&emsp;*[GLEW](https://glew.sourceforge.net/)*

&emsp; -&emsp;*[DevIL](https://openil.sourceforge.net/)*

&emsp; -&emsp;*[MathGeoLib](https://github.com/juj/MathGeoLib)*

&emsp; -&emsp;*[GLMath](https://glmath.sourceforge.net/)*

***

## Guide to execute
 * Download the Engine
 * Unpack .zip
 * Execute .exe

***
## Camera Controls
- Default Mode:
  * Mouse wheel scroll = Zoom in and out.
  * Mouse wheel click = move around.
  * 'F' = focus camera to selected object.
  
- Fly Mode (mouse right click pressed):
  * Mouse movement = look around
  * 'W' = move forward
  * 'S' = move back
  * 'A' = move left
  * 'D' = move right
  * 'Q' = move up
  * 'E' = move down
  * 'LShift' = increase movement speed
  
- Focused Mode ('Alt' + mouse left click pressed):
  * Mouse movement = orbit selected object

***
## Windows
* Windows can be docked around the screen, or keep them floating.

### * Main Menu
In this part you can find multiple dropdowns: 
* *File*: you find a button to open a popUp about de engine, a button with the link to GitHub, and a button to close the engine.
* *Basic Shapes*: a list of basic game object shaps to creat.
* *Windows*: you can open/close the other windows, and change the therme of the window to **"light"**, **"dark"**, **"soft dark"** and you can **"personalise"**
* *Render*: a button to render the meshes in wireframe

### * Inspector
It shows the components of the selected object, where you can change the name or disable it. 
* Transform
* Mesh
* Texture

### * Hierarchy
* Show the list of the objects in the scene and their parents/children.
* Right click on any object to show menu.
* 'Delete' / 'Supr' to delete selected game object.

### * Console
Don't be afraid to resize the console, the buttons risize with it.
* Print 3 typs of LOG (Warning, System, Missage), you can filter the different typs of LOG's with they own button (you can see how many are they next to de button).
* Collapse button: stacks identic logs.
* Clear button: clear all stored LOGS of the console.
* If you whant, can show the document and line of that debug.

### * Configuration
Headers with options over basic engine functionalities.
* *FPS*: Show and limitate FPS, information about frame calculation time.
* *Window*: Toggle Fullscreen, resize (or not) the windows, borderless mode, Window information.
* *Visual*: Let you activate some additional widgets of the windows: VSync, brightness, lights, dephts test, face culling, color material, textures.
* Hardware: Shows information about the hardware your PC is using.

### * Scene
* Draw the render of the scene in this windows

***
## How the game engine works
  * Game Objects:
    - Everything in the scene is stored in game objects, they have variable components to add to them, in order to be fully personalisable.
    - Game objects can be selected from the hierarchy window, this also makes the inspector appear.
    - Game objects have parents and childs, which makes them interactuate in different ways.
    - In the inspector, all of the selected game object components can be modified.
    - Disabling game objects in inspector prevents rendering itself plus all of its childs.
    
  * Components:
    - Transform: stores the information of the local position, rotation and scale. Global position is calculed by their parent transform.
    - Mesh: stores the mesh that is rendering every frame.
    - Texture: stores the texture rendering on the mesh, can be changed to print no texture, or to print default checkers texture.
    
 * Drag and drop:
   - Any FBX can be dropped on the scene. A game object will be created with child objects that store their meshes, if the FBX has a texture, and is loaded in Assets folder, it will be loaded automatically.
   - Any PNG and DDS image can be dropped on the scene. This will be loaded as the selected game object texture (creating a Texture Component if there isn't one yet).
  
***
## Possible Crashes:
 * Having a Texture Component and an **empty** Mesh Component in the same object. (Solved in the next patch)

***
Github adress: https://github.com/bielrabasa/TheSeed_GameEngine
## Creators

- Biel Rabasa
    * Github Account: [bielrabasa](https://github.com/bielrabasa)


- Roger Salas
    * Github Account: [Draquian](https://github.com/Draquian)
