# Darxi Networking

🔥 THIS IS A WORK IN PROGRESS (End goal is a real-use exectuable application for buisnesses and individuals).

🌱 This repo is a perosnal project creating a real-time network analysis dashboard. Providing users with detailed insights into various aspects of their network traffic and performance. 

This project is created and lead by me [JesseH](https://github.com/Jesse-11). However, is also collaborated on time to time by: [ShaurabD](https://github.com/FRDrago) and [ArthurP](https://github.com/ArthurPerets).

---


## Prerequisites

The application requires the following dependencies:
* Qt6
* CMake (version 3.16 or higher)
* C++ compiler with C++17 support
* Build essentials

Don't worry if you don't have these installed - our build system will automatically install the required packages on Debian-based systems (including Ubuntu).

## Project Structure

```
qt_application/
├── src/              # Source files
├── include/          # Header files
├── resources/        # Application resources
└── build/           # Build output (generated)
```

## Building the Application

### First-Time Setup
1. Clone the repository:
```bash
git clone [repository-url]
cd [repository-name]
```

2. Create and enter the build directory:
```bash
mkdir build
cd build
```

3. Configure and build the project:
```bash
cmake ..
make
```


### Regular Development
For daily development work, use these commands from the build directory:

**Build the application:**
```bash
make
```

**Build using multiple cores (faster):**
```bash
make -j4  # Replace 4 with your number of CPU cores
```

**Clean and rebuild:**
```bash
make clean
make
```

**View detailed build output:**
```bash
make VERBOSE=1
```


### Starting Fresh
If you need to start with a clean slate:

```bash
cd ..
rm -rf build
mkdir build
cd build
cmake ..
make
```

---

## Running the Application

After building successfully, run the application from the build directory:

```bash
./Darxi_Networking
```

---

## Build Configurations

### Debug Build
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Release Build
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```


---
## Troubleshooting

### Common Issues
1. **Qt components not found:**
   * Verify Qt6 installation:
   ```bash
   dpkg -l | grep qt6-base-dev
   ```
   * If missing, install manually:
   ```bash
   sudo apt update
   sudo apt install qt6-base-dev
   ```

2. **Build errors:**
   * Ensure you're in the build directory
   * Try a clean rebuild
   * Check CMAKE_PREFIX_PATH is correctly set

### Getting Help
If you encounter issues:
1. Check the error message carefully
2. Ensure all prerequisites are installed
3. Try a clean rebuild
4. Check the Qt6 installation paths

## Contributing 
1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request