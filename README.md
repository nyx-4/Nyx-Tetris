```abc
                      #        TM
       $    $  $     $ #     #
       $$   $   $   $   #   #
       $ $  $    $ $     # #
       $  $ $     $       #
       $   $$     $      # #
       $    $     $     #   #
  
  
              Nyx-Tetris

Authors: IsmailHamza & AwaisTahir
```


## 1. About _Nyx-Tetris_
### Overview
Tetris is a classic puzzle game where players manipulate falling tetrominoes (geometric shapes composed of four square blocks) to create and clear horizontal lines on the game board. The goal is to prevent the stack of blocks from reaching the top of the screen. Tetris is often named **_one of the greatest video games_**.
### Purpose
The Nyx-Tetris project was created to explore the capabilities of **vanilla C++** in building a console-based graphical game on _Linux_. The goal was to **avoid** using external libraries like SFML or SDL, emphasizing the _use of minimalistic system libraries_ to handle inputs and control the game flow.

## 2. Development Process
### Tools and Libraries Used:
- **C++**: The primary programming language used for development.
- **termios.h**: For handling **non-canonical input**, allowing real-time user interactions without needing to press Enter.
- **unistd.h**: Used for system-level operations such as _sleeping/delaying_ and _reading input/output._
- **Linux Terminal**: The game is designed to run directly in the GNU/Linux terminal environment.

### Features:
- **Minimalistic** and bare-bone approach to Tetris logic.
- **Real-time rendering** of the game board using ASNI escape characters.
- **Custom built psedo-random customizable algorithm**, just for Nyx-Tetris.
- Customizable personalized **24-bit true colors** support.
- Support for custom size and shape tetrominos (or **polyminos**, as I call it).
- Adjustable speed and scoring criteron.
- **Cross-platform** with minimal changes due to use of almost no libraries.

### Challenges:
- Making a **psedo-random** polymino generator.
- Managing **system-level interactions** for input and output with minimal dependencies.
- **Simulating graphical output** using text-based rendering in a console.
- Ensuring **smooth** and responsive gameplay **without advanced libraries**.

## 3. Final Status
The project is nearly complete, with the following achievements and limitations:

### Achievements:
- The **core** mechanics of Tetris, including movement, rotation, and line clearing, are **fully implemented**.
- A **scoring system** that tracks player progress is functional.
- The **game dynamically** adjusts difficulty by reducing delays as the score increases.
- **Psedo-random algorithm** is giving unpredictable results. (Because that's what its supposed to do.)
- Made a meaningful contribution to the **Free and Open-Source Softwares** (FOSS).

### Limitation
- Some minor bugs.