#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

const static std::array<std::pair<cv::Scalar, cv::Scalar>, 9> rgs = {{
        {cv::Scalar(0, 120, 70), cv::Scalar(15, 255, 255)},
        {cv::Scalar(160, 50, 50), cv::Scalar(179, 255, 255)},
        {cv::Scalar(27, 120, 70), cv::Scalar(32, 255, 255)},
        {cv::Scalar(47, 120, 70), cv::Scalar(60, 255, 255)},
        {cv::Scalar(85, 120, 70), cv::Scalar(91, 255, 255)},
        {cv::Scalar(117, 120, 70), cv::Scalar(121, 255, 255)},
        {cv::Scalar(149, 120, 70), cv::Scalar(155, 255, 255)},
        {cv::Scalar(0, 0, 254), cv::Scalar(0, 0, 255)},
        {cv::Scalar(0, 0, 0), cv::Scalar(1, 1, 1)}
    }
};

int makeMorphology(cv::Mat &Detector, int ErodeSize = 4, int DilateSize = 4)
{
    cv::Mat ErodeElement = getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ErodeSize + 1, 2 * ErodeSize + 1),
                           cv::Point(ErodeSize, ErodeSize));
    cv::Mat DilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(2 * DilateSize + 1, 2 * DilateSize + 1),
                            cv::Point(DilateSize, DilateSize));
    erode(Detector, Detector, ErodeElement);
    dilate(Detector, Detector, DilateElement);
    dilate(Detector, Detector, DilateElement);
    erode(Detector, Detector, ErodeElement);
}

/*
 * defineHSVRange - preprocess image and define number of ranges and actual range value
 * Orange  0-22
 * Yellow 22- 38
 * Green 38-75
 * Blue 75-130
 * Violet 130-160
 * Red 160-179
 *
 *
    Black	#000000	(0,0,0)	        (0°,0%,0%)
 	White	#FFFFFF	(255,255,255)	(0°,0%,100%)
 	Red	    #FF0000	(255,0,0)	    (0°,100%,100%)
 	Lime	#00FF00	(0,255,0)	    (120°,100%,100%)
 	Blue	#0000FF	(0,0,255)    	(240°,100%,100%)
 	Yellow	#FFFF00	(255,255,0) 	(60°,100%,100%)
 	Cyan	#00FFFF	(0,255,255)	    (180°,100%,100%)
 	Magenta	#FF00FF	(255,0,255)	    (300°,100%,100%)
 	Silver	#C0C0C0	(192,192,192)	(0°,0%,75%)
 	Gray	#808080	(128,128,128)	(0°,0%,50%)
 	Maroon	#800000	(128,0,0)	    (0°,100%,50%)
 	Olive	#808000	(128,128,0)	    (60°,100%,50%)
 	Green	#008000	(0,128,0)	    (120°,100%,50%)
 	Purple	#800080	(128,0,128)	    (300°,100%,50%)
 	Teal	#008080	(0,128,128)	    (180°,100%,50%)
 	Navy	#000080	(0,0,128)	    (240°,100%,50%)
 *
 *
 */
int defineHSVRange(cv::Mat &imageHSV, std::vector<std::pair<cv::Scalar, cv::Scalar> > &ranges)
{
    cv::Mat tmp;

    std::cout << "Color range:\n";
    for (int i = 0; i < rgs.size(); i++)
    {
        inRange(imageHSV, rgs[i].first, rgs[i].second, tmp);
        makeMorphology(tmp);
        std::cout << i << "\n";
        double total = tmp.total();
        double white = countNonZero(tmp);
        std::cout << "Total is " << total << "; White is " << white << "\n";
        if (white / total > 0.01)
            ranges.push_back(rgs[i]);
        tmp.release();
    }
    return 0;
}



/*
 * getRegion - base on incoming image and HSV ranges separate regions into vector
 */
int getRegion(cv::Mat& ImageBGR, std::vector<cv::Mat>& Regions)
{
    cv::Mat ImageHSV, Detector, DetectorRed;
    std::vector<std::pair<cv::Scalar, cv::Scalar>> Ranges;

    try
    {
        cvtColor(ImageBGR, ImageHSV, cv::COLOR_BGR2HSV, 0);
    }
    catch(cv::Exception &e)
    {
        std::cout << "Bad file: " << e.what();
        return -1;
    }

    defineHSVRange(ImageHSV, Ranges);

    int numOfRanges = Ranges.size();
    std::cout << "Define number of ranges: " << numOfRanges << "\n";

    for (int i = 0; i < numOfRanges; i++)
    {
        if (DetectorRed.empty() && (Ranges[i] == rgs[0] || Ranges[i] == rgs[1]))
        {
            inRange(ImageHSV, rgs[0].first, rgs[0].second, Detector);
            inRange(ImageHSV, rgs[1].first, rgs[1].second, DetectorRed);
            Detector = Detector + DetectorRed;
        }
        else if (Ranges[i] != rgs[0] && Ranges[i] != rgs[1])
            inRange(ImageHSV, Ranges[i].first, Ranges[i].second, Detector);
        else
            continue;

        makeMorphology(Detector);

        Regions.push_back(Detector);

        Detector.release();
    }

    return 0;
}

/*
 * calcRegionPerimeter - calculate perimeters for white range on image
 */
int calcRegionPerimeter(cv::Mat& image, std::vector<cv::Mat>& Perimeters)
{
    cv::Mat edge;
    cv::Canny(image, edge, 1, 1);
    Perimeters.emplace_back(edge);

    return 0;
}

int readImage(char *path, cv::Mat& image)
{
    if (path == nullptr)
        return -1;

    image = cv::imread(path, CV_LOAD_IMAGE_COLOR);

    if (!image.data)
    {
        std::cout << "No image data\n";
        return -1;
    }

    return 0;
}

int showImage(char* window, cv::Mat& image)
{
    cv::imshow(window, image);
    cv::waitKey(0);

    return 0;
}

int saveImage(char* path, cv::Mat& image)
{
    cv::imwrite(path, image);

    return 0;
}

/*
 *
 */
class Contours
{
public:
    Contours(cv::Mat img);
    virtual ~Contours() = default;
    void show();

protected:

    cv::Mat contour;
    const char* window = "Image";
};

Contours::Contours(cv::Mat img)
{
    cv::Canny(img, contour, 1, 1, 3);
}

void Contours::show()
{
    cv::imshow(window, contour);
    cv::waitKey(0);
}

/*
 *
 */
class SmoothContours : public Contours
{
public:
    SmoothContours(cv::Mat img);
    virtual ~SmoothContours() = default;
    void smoothCurveFitting();
    void smoothGaussian();
    void smoothSpline();
    void show(std::string window);

private:
    std::vector<std::vector<cv::Point> > data;
};

SmoothContours::SmoothContours(cv::Mat img) : Contours(img)
{
    findContours(contour, data, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
}

void SmoothContours::smoothCurveFitting()
{
    int ErodeSize = 10;
    int DilateSize = 10;
    cv::Mat tmp;
    cv::Mat ErodeElement = getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ErodeSize + 1, 2 * ErodeSize + 1),
                           cv::Point(ErodeSize, ErodeSize));
    cv::Mat DilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(2 * DilateSize + 1, 2 * DilateSize + 1),
                            cv::Point(DilateSize, DilateSize));
    dilate(contour, tmp, DilateElement);
    erode(tmp, tmp, ErodeElement);

    for (int i = 0; i < data.size(); i++)
        data[i].clear();
    data.clear();

    findContours(tmp, data, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
}

void SmoothContours::smoothGaussian()
{
    cv::Mat tmp;
    cv::GaussianBlur(contour, tmp, cv::Size(15, 15), 0, 0);
    int ErodeSize = 7;
    cv::Mat ErodeElement = getStructuringElement(cv::MORPH_RECT, cv::Size(2 * ErodeSize + 1, 2 * ErodeSize + 1), cv::Point(ErodeSize, ErodeSize));
    erode(tmp, tmp, ErodeElement);

    for (int i = 0; i < data.size(); i++)
        data[i].clear();
    data.clear();

    findContours(tmp, data, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
}

void SmoothContours::smoothSpline()
{
    /*TODO*/
    /*
     * iterate thru contour elements and apply for each contour set of points spline interpolation
     *
     * linear interpolation should be considered too
     */
}

void SmoothContours::show(std::string window)
{
    cv::Mat edge = cv::Mat::zeros(contour.size(), CV_8UC3);

    for( int i = 0; i< data.size(); i++ )
    {
        for (auto i : data[i])
            std::cout << i << "\n";

        std::cout << "contour: " << i << "\t";

        drawContours(edge, data, i, cv::Scalar(0, 0, 255), 1, 8);
    }

    cv::namedWindow(window.c_str(), CV_WINDOW_AUTOSIZE);
    imshow(window.c_str(), edge);
    cv::waitKey(0);
}

void applyCourveSmooth(std::vector<cv::Mat>& Regions)
{
    for (int i = 0; i < Regions.size(); i++)
    {
        auto sm = std::make_unique<SmoothContours>(Regions[i]);

        sm->smoothCurveFitting();
        std::string w("curvefit");
        sm->show(w);
    }
}

void applyGaussianSmooth(std::vector<cv::Mat>& Regions)
{
    for (int i = 0; i < Regions.size(); i++)
    {
        auto sm = std::make_unique<SmoothContours>(Regions[i]);

        sm->smoothGaussian();
        std::string w("gaussian");
        sm->show(w);
    }
}

void applySplineSmooth(std::vector<cv::Mat>& Regions)
{
    for (int i = 0; i < Regions.size(); i++)
    {
        auto sm = std::make_unique<SmoothContours>(Regions[i]);

        sm->smoothSpline();
        std::string w("gaussian");
        sm->show(w);
    }
}

static void usage(char *argv[])
{
    std::cout << argv[0] << " [-f smooth curve fit] [-g smooth gaussian] [-s spline [TODO]] <Image_Path>\n";
}

int main(int argc, char *argv[])
{
    cv::Mat image;
    std::vector<cv::Mat> Regions;
    std::vector<cv::Mat> Perimeters;
    char window[32];
    char ImgName[32];

    if (argc < 2)
    {
        usage(argv);
        return -1;
    }

    std::cout << "IMAGE: " << argv[argc-1] << "\n";

    readImage(argv[argc-1], image);

    getRegion(image, Regions);

    std::cout << "Found regions: " << Regions.size() << "\n";

    for (int i = 0; i < Regions.size(); i++)
    {
        sprintf(window,"Image-%d", i);
        showImage(window, Regions[i]);
    }

    for (int i = 0; i < Regions.size(); i++)
    {
        sprintf(ImgName,"%s-Image-%d.png", argv[argc-1], i);
        saveImage(ImgName, Regions[i]);
    }

    std::cout << "Region perimeter\n";
    for (int i = 0; i < Regions.size(); i++)
        calcRegionPerimeter(Regions[i], Perimeters);

    for (int i = 0; i < Perimeters.size(); i++)
    {
        sprintf(window,"Edge-%d", i);
        showImage(window, Perimeters[i]);
    }

    int opt = 0;
    while ((opt = getopt(argc, argv, "fgs")) != -1)
    {
        switch (opt)
        {

        case 'f':
            applyCourveSmooth(Regions);
            break;

        case 'g':
            applyGaussianSmooth(Regions);
            break;

        case 's':
            applySplineSmooth(Regions);
            break;

        }
    }

    return 0;
}
