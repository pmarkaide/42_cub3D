# cub3D

A simple raycasting engine inspired by Wolfenstein 3D, developed as part of the 42 school curriculum at Hive Helsinki. This project creates a 3D graphical representation of a maze using raycasting principles.

https://github.com/user-attachments/assets/2301bc31-b68d-4cdc-8479-6894fa5f300d

## Description

cub3D is a first-person perspective maze renderer inspired by Wolfenstein 3D. The rendering process happens in three main steps:

1. **Basic Scene Creation**: First, we draw the ceiling and floor until the middle of the screen using solid colors defined in the map file. This creates the basic structure of our 3D view.

2. **Wall Rendering**: For each vertical line on the screen, we calculate the distance from the player to the wall. Closer walls appear taller and wider, while distant walls appear shorter and thinner, creating the 3D perspective effect.

3. **Texture Mapping**: Finally, we apply textures to the walls based on their orientation (North, South, East, West). The textures are mapped onto the walls according to where the ray hits the wall, creating the final detailed appearance.

![raycasting-steps](https://github.com/user-attachments/assets/1eede5f6-0bee-47a5-bebd-a94c7bb6eb14)

## Installation

```bash
git clone https://github.com/pmarkaid/cub3D.git
cd cub3D
make
```

## Usage

```bash
# runt he program with the desired map
./cub3D maps/valid_subject.cub
```

### Controls
- `W` : Move forward
- `S` : Move backward
- `A` : Strafe left
- `D` : Strafe right
- `←` : Rotate camera left
- `→` : Rotate camera right
- `ESC` : Exit the game

### Map Characteristics
- The map is represented with `1` for walls, `0` for empty space and a spawing point, that can be any of the letters `N|S|W|E` that represent the starting player view direction.
- The map must be closed/surrounded by walls
- The game implements a buffer zone around the defined map
- An outer wall with collision detection surrounds this buffer zone
- While there's no collision detection with interior walls, you cannot exit the buffer zone


Example map file format:

```
NO textures/Ncolor.png
SO textures/Scolor.png
WE textures/Wcolor.png
EA textures/Ecolor.png

F 117,92,60
C 14,62,89

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        10010000000000000W0000001
111111111011000001110000000000001
100000000011000001110000000011111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
1100000111010101111101111000111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## How Raycasting Works

Raycasting creates a 3D perspective by sending out rays from the player's position and using the Digital Differential Analysis (DDA) algorithm to efficiently find wall intersections.

![raycasting-visualization](https://github.com/user-attachments/assets/4d471897-563a-4ebb-9040-c53886a88e10)

### Basic Principle
- For each vertical screen column, a ray is cast from the player's position
- The ray's direction is calculated based on the player's viewing angle and the screen column position
- When the ray hits a wall, we calculate the distance to determine the wall's height on screen

### DDA Algorithm Implementation
The DDA algorithm efficiently finds wall intersections by:
1. Calculating the ray's direction and initial position
2. Computing the distance to the next X and Y grid intersections
3. Moving step by step through the grid by choosing the shortest distance
4. Stopping when a wall is hit

The algorithm is particularly efficient because:
- It only checks grid cells the ray actually passes through
- It avoids floating-point arithmetic where possible
- It naturally finds the closest wall intersection

### Wall Rendering
1. The perpendicular distance to the wall is used to avoid fisheye effect
2. Wall height is calculated as: screenHeight / distance
3. Texture coordinates are determined by where exactly the ray hits the wall
4. Final color is sampled from the appropriate wall texture
