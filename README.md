# Black Hole Visualization with SFML

This project is a **realistic 2D visualization of a black hole** built with [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/).  
It simulates particle motion around a black hole with gravitational and tangential forces, including features such as an accretion disk, photon ring, and glow effects.

---

## Features
- Real-time particle simulation with gravitational attraction.
- Accretion disk and photon sphere visual effects.
- Dynamic particle coloring based on velocity and distance.
- Particles respawn at the screen edges when absorbed by the black hole.

---

## Requirements

### Dependencies
- **C++17** or higher
- **CMake >= 3.16**
- **SFML 2.5+**

You can install SFML via:
- **Linux (Debian/Ubuntu)**:
  ```bash
  sudo apt-get install libsfml-dev
  ```
- **macOS (Homebrew)**:
  ```bash
  brew install sfml
  ```
- **Windows**:
  Download binaries from the [SFML official website](https://www.sfml-dev.org/download.php).

---

## Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/BlackHoleSFML.git
   cd BlackHoleSFML
   ```

2. Create a build directory and configure with CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. Compile the project:
   ```bash
   cmake --build .
   ```

4. Run the executable:
   ```bash
   ./BlackHoleSFML
   ```

---

## Project Structure
```
BlackHoleSFML/
├── src/
│   └── main.cpp        # Main simulation code
├── CMakeLists.txt      # Build configuration
└── README.md           # Project documentation
```

---

## Notes
- On **Windows**, SFML DLLs must be available in the same directory as the executable.  
  This project includes a CMake rule to copy the SFML binaries automatically when building with Visual Studio.
- On **Linux/macOS**, SFML will be linked via system libraries (ensure `pkg-config` is installed).

---

## License
This project is released under the MIT License.  
You are free to use, modify, and distribute this code with attribution.
