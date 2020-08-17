#
# https://imagemagick.org/script/mogrify.php
#


# leave in the image only exact color pixels with presision 2%
magick convert 1.png -fuzz 2% -fill white +opaque "#7e786c" 2.png

# apply to image dilate
magick convert 1.png -morphology Dilate Diamond 2.png

# apply to image erode
magick convert 1.png -morphology Erode Octagon 2.png

# invert white-black
magick convert 1.png -grayscale Rec709Luminance 2.png

# inverse colors black to white and white to black
magick convert 1.png -negate 2.png

# binarize image based on threshold
magick convert 1.png -threshold 75% 2.png

# investigate histogram
magick identify -verbose 1.png