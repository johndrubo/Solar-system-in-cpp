# Solar System Simulator

## Overview
This Solar System Simulator is a 3D visualization tool implemented in C using OpenGL and the GLUT library. It offers a dynamic representation of the major planets in the solar system, including Earth and its moon, along with features like the asteroid belt and the rotation of planets around the sun.

## Features
- Real-time 3D rendering of the solar system.
- Simulated orbits for major planets: Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, and Neptune.
- Inclusion of Earth's Moon, and features like the asteroid belt.
- Smooth transitions and rotations to depict planetary movements.
- Adjustable scaling factors for the sun and planets.
- Light effects to simulate the sun's illumination.

## Requirements
- C compiler (like GCC)
- OpenGL
- GLUT library

## Installation
1. Ensure you have OpenGL and the GLUT library installed on your system.
2. Compile the code using a C compiler. For example, using GCC:
gcc -o solar_system_simulator solarsystem.cpp -lGL -lGLU -lglut
3. Run the compiled program:


## Usage
Once you run the program, a window displaying the solar system will appear. The planets will be in motion, revolving around the sun. You can observe the different planetary orbits and rotations.

## Code Structure
- `main()`: Initializes the GLUT library and sets up the main window and callbacks.
- `initLighting()`: Sets up the lighting for the scene, including sunlight and ambient light.
- `myinit()`: Initializes various OpenGL settings like background color, depth testing, and anti-aliasing.
- `background()`: Renders the background of the scene.
- `orbit()`: Draws the orbits for the planets.
- `draw()`: The main function that draws the entire scene including planets, their orbits, and the sun.
- `update()`: Updates the angles and scales for the animation, creating the effect of planetary motion.

## Contributing
Contributions to this project are welcome. Please ensure to follow the project's coding standards and submit your pull requests for review.

## License
[MIT License](https://opensource.org/licenses/MIT)
