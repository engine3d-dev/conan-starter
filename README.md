# Conan Starter Project

This conan-starter project is an example project on how to create your own application using Conan. This projects \
going to output a window and an imgui window with docking enabled. To ensure packages from engine3d-conan are \
correctly being pulled into this project.

## Conan Setup

To get all of Engine3D packages, just run this conan command.

```
conan remote add engine3d-conan https://libhal.jfrog.io/artifactory/api/conan/engine3d-conan
```

## Build Starter

Run this conan command to build the project.

```
conan build .
```

## Running the Starter

Run the executable doing the following

```
./build/Release/Starter
```
