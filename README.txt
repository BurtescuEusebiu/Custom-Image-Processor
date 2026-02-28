# Image Editor Project

**3D Matrix-Based Image Processing | C / C++**

- **Overview:**  
  - Program edits images represented as a 3D matrix of RGB values for each pixel  
  - Supports multiple image processing operations: crop, flip, rotate, extend, copy-paste, and apply filters  
  - Operated entirely via command-line input  

- **Supported Commands:**  
  - `e` – Exit: closes the program  
  - `l N M path` – Load: allocates and loads an NxM image from `path`  
  - `s index path` – Save: saves the image at `index` to `path`  
  - `ah index` – Apply Horizontal Flip: flips the image at `index` horizontally  
  - `ar index` – Apply Rotate: rotates the image at `index` left  
  - `ac index x y w h` – Apply Crop: crops the image at `index` with given coordinates and size  
  - `ae index rows cols R G B` – Apply Extend: extends the image at `index` with given rows, cols, and color  
  - `ap index_dst index_src x y` – Apply Paste: pastes `index_src` image into `index_dst` at coordinates `(x, y)`  
  - `cf size [values]` – Create Filter: creates a filter of given size and values  
  - `af index_img index_filter` – Apply Filter: applies filter `index_filter` on image `index_img`  
  - `df index_filter` – Delete Filter: deletes and deallocates the filter at `index_filter`  
  - `di index_img` – Delete Image: deletes and deallocates the image at `index_img`  

- **Reliability & Constraints:**  
  - Fully memory-leak free  
  - Paths limited to 100 characters, no spaces  
  - Input files are assumed valid  
  - Commands and parameters are always valid and within bounds  
