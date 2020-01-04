# Generic RANSAC in C++ and Image Stitching
Implementation of a generic RANSAC (Random sample consensus) in C++ and of Image Stitching (Panorama) of multiple images (mosaic stitching).

## Dependencies
- CMake
- OpenCV

## Running
```
mkdir build
cd build
cmake ..
make
./ransac
./test
```

`ransac` shows the stitching of 3 images
`test` shows the performance comparison between OpenCV and our method.