# Sample code 
Example of using openCV to find region and calc region perimeter
- Currently brute force algorithm implemented
- Probably K-mean should be try based on magick experiments it shows better result

## Requirements
- OpenCV 2.X
- CMake > 2.8

## Usage
    cmake .
    make
    ./RegionProcessing image.png
    ./RegionProcessing -g image.png
    ./RegionProcessing -f image.png

## Resources
https://www.learnopencv.com/invisibility-cloak-using-color-detection-and-segmentation-with-opencv/
http://aishack.in/tracks/image-processing-algorithms-level-1/
https://docs.opencv.org/3.4.0/da/d54/group__imgproc__transform.html