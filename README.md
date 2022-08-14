# fdf 125/100
This is my solution for the fdf project of 42 school.<br>

![result](https://github.com/Sirelaw/fdf/blob/master/readme_addons/Screen%20Shot%202022-08-14%20at%201.17.34%20AM.png)

## This code is capable of
- reading from a correctly parsed fdf file.

## rasterization
- In computer graphics, rasterization is the task of taking an image described in a vector graphics format (shapes) and converting it into a raster image (a series of pixels, dots or lines, which, when displayed together, create the image which was represented via shapes). The rasterized image may then be displayed on a computer display, video display or printer, or stored in a bitmap file format. Rasterization may refer to the technique of drawing 3D models, or the conversion of 2D rendering primitives such as polygons, line segments into a rasterized format.

# Implementation
- Points are read from the and stored as nodes in a n X m array.
- Each node is a point in space with x,y,z coordinates.
- Depending on the type of rotation, x, y or z-roll is applied on all nodes and the coordinate is updated.
- Every node is then placed as a pixel on an image with their x,y coordinate.
- This image is then put to the screen with the steps repeated once a key is pressed.




## how to use the program
This will compile my code into an executable called `fdf` and delete all unnecesarry files that were created during compilation.<br>

```
make
```

To visualize more maps like the one below.<br>

```
./fdf maps/test_maps/[other_map]
```

### movement
- Translate with arrow keys
- Rotate with ```
 QWEASD ```
- Zoom with mouse wheel.

## visualization two maps from the maps/test_maps folder.
more maps can be found in this folder.

![visualizer](https://github.com/Sirelaw/42_curcus_fdf/blob/master/readme_addons/Screen-Recording-2022-08-14-at-1.27.54-AM.gif)