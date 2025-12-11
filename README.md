# Directional Audio Visualizer
A directional visual overlay of sounds for assisting those who are deaf, hard of hearing, or otherwise unable to take full advantage of audio in games.

Each range of frequencies is mapped to a "dot" on the visualizer. The positions of the "dots" signify horizontal direction, 
and sizes map to loudness. Different colors signify different ranges of frequencies, and are customizable in the settings.

There are currently two types of visualizer available, a horizontal bar, and a circle.

## Installation Instructions:
Download the [latest release](https://github.com/wyliemickelson/Audio-Visualizer/releases/latest), extract the archive, and open AudioVisualizer.exe.

<img width="423" height="245" alt="{98AAD662-AEC8-4928-A727-43A1736CDB6F}" src="https://github.com/user-attachments/assets/286f1b21-ec64-4a68-b9a9-36af040cab19" /> <br>
If the desired application is not listed, make sure it's currently playing audio, and that volume is turned on.<br>
Then press "Refresh List" and it should appear.

After pressing "Ok" the visualization will appear.

## Customization
Customization can be done on startup, or by navigating to the system tray, right clicking the radar icon, and selecting "Customize".

The type of visualizer may be changed to a horizontal bar or a circle.

The position, size, colors, and shape of sounds may all be modified, with a live preview showing changes.

## Exiting the program
As the overlay is transparent and borderless, there is no close button.
However, there are a few straightforward options to close it.

1: Right click it's icon on the taskbar and select "Close window".

2: Press and hold alt+tab, hover over the window named "Audio Visualizer", then click on the X.

3: Navigate to the system tray, located in the bottom right corner of the taskbar, right click the radar icon, and click "Exit"<br>

<img width="152" height="79" alt="{9AB2DE05-ACFA-42DD-9100-79343976EFE7}" src="https://github.com/user-attachments/assets/615985a7-89f8-4f86-a8c8-792731b90387" /><br>

If you cant find the icon, click the "^" symbol to reveal hidden tray icons.

## Preventing audio playback:
If you want to visualize audio, but don't want sound to play through your headphones/speakers,
you can change the audio playback device in most applications. If that isn't supported, open "Sound Mixer Options", then change the program's output device from "Default" to something else.

<img width="945" height="634" alt="{22416591-5597-45BC-A486-7B33A69FCCFF}" src="https://github.com/user-attachments/assets/8824245c-3830-4727-bae4-a28f609cb41b" />

## Build instructions:
Download source, open the Visual Studio solution file, and build the solution.

### Dependencies:
Build dependencies are included in the source files/solution.

GUI/Visualization uses WXWidgets & OpenGL. <br/> 
OpenGL procedures are loaded using GLAD2. <br/> 
Fast fourier transforms are accomplished using the fftw3 library. <br/>
Menus were designed with wxFormBuilder. <br/> 


