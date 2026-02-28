# Image Editor Project

**3D Matrix-Based Image Processing | C / C++**

## Overview
- Edits images represented as a 3D matrix of RGB values per pixel
- Supports crop, flip, rotate, extend, copy-paste, and filter application
- Fully command-line operated

## Commands
- `e` – Exit program
- `l N M path` – Load: allocates and loads an NxM image from `path`
- `s index path` – Save: saves image at `index` to `path`
- `ah index` – Apply Horizontal Flip on image at `index`
- `ar index` – Apply Rotate (left) on image at `index`
- `ac index x y w h` – Apply Crop on image at `index` with given coordinates and size
- `ae index rows cols R G B` – Apply Extend on image at `index` with given rows, cols, and color
- `ap index_dst index_src x y` – Apply Paste: pastes `index_src` into `index_dst` at `(x, y)`
- `cf size [values]` – Create Filter of given size and values
- `af index_img index_filter` – Apply Filter: applies `index_filter` on `index_img`
- `df index_filter` – Delete Filter: deletes and deallocates filter at `index_filter`
- `di index_img` – Delete Image: deletes and deallocates image at `index_img`

## Features & Constraints
- Memory-leak free
- Path lengths ≤ 100 characters, no spaces allowed
- Assumes input files exist and are valid
- Commands and parameters are always valid and within bounds
