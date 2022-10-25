# The Seed Engine
The Seed Engine is unfinished, we are working on this during the assigment of *Engine Development* for the CITM Bachelor's degree in Video Game Design and Development.

The Seed Engine is a game engine developed in c++ using the external librarys: 

&emsp; -&emsp;*[SDL2](https://www.libsdl.org/)*

&emsp; -&emsp;*[OpenGL](https://www.opengl.org/)* 

&emsp; -&emsp;*[ImGui](https://github.com/ocornut/imgui)*

&emsp; -&emsp;*[GLEW](https://glew.sourceforge.net/)*

&emsp; -&emsp;*[DevIL](https://openil.sourceforge.net/)*

&emsp; -&emsp;*[MathGeoLib](https://github.com/juj/MathGeoLib)*

&emsp; -&emsp;*[GLMath](https://glmath.sourceforge.net/)*

***

## Guid to execute
 * Download the Engine
 * Unpack .zip
 * Execute .exe

***
## Camera Controls
- While Right clicking, “WASD” fps-like movement and free look around must be enabled.
- Mouse wheel should zoom in and out.
- Alt+Left click should orbit the object.
- Pressing “f” should focus the camera around the geometry.
- Holding SHIFT duplicates movement speed.

***
## Windows
* You can drag and drop any fbx or png in any windows to import to the project.
* You can dock the windows were you whant.

### * Main Menu
In this part you can find multiple dropdowns: 
* *File*: you find a button to open a popUp about de engine, a button with the link to GitHub, and a button to close the engine.
* *Basic Shapes*: a list of basic game object shaps to creat.
* *Windows*: you can open/close the other windows, and change the therme of the window to **"light"**, **"dark"**, **"soft dark"** and you can **"personify"**
* *Render*: a button to render the meshes in wireframe

### * Inspector
Show the components of the selected objects 
* Trnasform with position, rotarion and scale of the object
* Mesh of the object
* Texture of the object

### * Hierarchy
* Show the list of the objects in the scene and their parents/chillds.

### * Console
* Print 3 typs of LOG (Warning, System, Missage), you can filter the different typs of LOG's with they own button (you can see how many are they next to de button).
* If 2 LOG's are the same, you can collapse and see this has 1 and you have a counter of how many are they.
* You can clear the LOG of the console.
* If you whant, can show the document and line of that debug.

### * Configuration
You can find some headers with some propertis of windows or configuration:
* *FPS*: Show the name of engine and the organisation that help us, shos too the fps (you can limitate) and miliseconds.
* *Window*: Let you put the fullscreen, let resiz (or not) the windows, put borderless mode; let you know the with and height of the windows.
* *Visual*: Let you active some aditional widgets of the windows: VSync, brightness, lights, dephts test, face culling, color material, textures.
* Hardware: Show the versions of some librarys that we use, the CPU, the GB of RAM, and the Caps that your PC are using.

### * Scene
* Draw the render of the scene in this windows


***
## Creators

- Biel Rabasa
    * Github Account: [bielrabasa](https://github.com/bielrabasa)


- Roger Salas
    * Github Account: [Draquian](https://github.com/Draquian)
