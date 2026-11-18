# Blocky

Blocky is an early C++ experiment in storing a voxel world as 32×32×32 sub-chunks. It defines compact voxel data and code for creating the face vertices used to render solid blocks.

## Build

Open `Blocky.sln` in Visual Studio and build the `Blocks` project. The project uses vcpkg manifest dependencies; Visual Studio must be configured to use vcpkg.

## Status

This repository is a data-structure and meshing prototype, not a playable voxel game. The current entry point is a stress experiment that fills a large world; rendering and a normal interactive loop are not implemented yet.
