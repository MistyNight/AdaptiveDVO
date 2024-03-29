#ifndef FRAME_H
#define FRAME_H

#include <opencv2/core/core.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <string>
#include "Settings.h"
#include <opencv2/ximgproc.hpp>

//TODO make image pyramids, (Canny) edge pyramids, depth pyramids
//TODO make derivative pyramids

namespace EdgeVO{
    class Sequence;
class Frame{
    public:
        Frame();
        Frame(std::string imagePath, std::string depthPath, Sequence* seq);
        Frame(cv::Mat& image);
        Frame(cv::Mat& image, cv::Mat& depthMap);
        //Frame(const Frame& cp);
        ~Frame();
        void printPaths();
        //Frame& operator=(const Frame& rhs);
        //For cleanup
        void releaseAllVectors();
        //For calculations
        cv::Mat getImage(int lvl) const;        
        cv::Mat getDepthMap(int lvl) const;        
        cv::Mat getMask(int lvl) const;        
        cv::Mat getEdges(int lvl) const;    

        cv::Mat getDepthGradientX(int lvl) const;
        cv::Mat getDepthGradientY(int lvl) const;        
        cv::Mat getLaplacian(int lvl) const;
        cv::Mat getGradientX(int lvl) const;
        cv::Mat getGradientY(int lvl) const;
        cv::Mat getImageVector(int lvl) const;
        
        cv::Mat getGradientMagVector(int lvl) const;
        cv::Mat getGdx(int lvl) const;
        cv::Mat getGdy(int lvl) const;

        void createPyramid(cv::Mat& src, std::vector<cv::Mat>& dst, int pyramidSize, int interpolationFlag, bool flagMASP=false);
        void createPyramidWithBilateralFiltering(cv::Mat& src, std::vector<cv::Mat>& dst, int pyramidSize, int interpolationFlag);
        void calcGradientX(cv::Mat& src, cv::Mat& dst);
        void calcGradientY(cv::Mat& src, cv::Mat& dst);
        void calcLaplacian(cv::Mat& src, cv::Mat& dst);

        int getHeight(int lvl) const;
        int getWidth(int lvl) const;

        //For display purposes only
        cv::Mat& getImageForDisplayOnly();
        cv::Mat& getEdgeForDisplayOnly();
        cv::Mat& getDepthForDisplayOnly();

        void makePyramids(bool flagMasf = false);
        void createDepthGradientPyramids();
        void createImageGradientPyramids(bool flagLaplacian = false);
        
        // Edge Smoothing Fiter for extending valid gradient ranges.
        void edgeSmoothingFilter(cv::Mat &in_img);

        // Canny Edges
        void createCannyEdgePyramids();
        // LoG Edges
        void createLoGEdgePyramids();
        // Sobel Edges
        void createSobelEdgePyramids();
        // Structured Forests
        void createStructuredForestEdgePyramid();
        // Extra Pyramid Layer with Full Image
        void createBasinPyramids();

        void setDepthMap(cv::Mat& depthMap);
        bool hasDepthMap();

    private:
        cv::Mat m_image;
        cv::Mat m_depthMap;
        cv::Mat m_edgeMap;
        std::vector<cv::Mat> m_pyramidImage;
        std::vector<cv::Mat> m_pyramidImageUINT;
        //std::vector<cv::Mat> m_pyramidImageFloat;
        std::vector<cv::Mat> m_pyramid_Ddx, m_pyramid_Ddy;
        std::vector<cv::Mat> m_pyramid_Idx, m_pyramid_Idy;
        std::vector<cv::Mat> m_pyramid_gradMag; // G
        std::vector<cv::Mat> m_pyramid_Gdx, m_pyramid_Gdy;
        std::vector<cv::Mat> m_pyramidLaplacian;
        std::vector<cv::Mat> m_pyramidEdge;
        std::vector<cv::Mat> m_pyramidDepth;
        // std::vector<cv::Mat3f> m_pyramidX3D;
        // std::vector<cv::Mat3f> m_pyramidNormal;
        std::vector<cv::Mat> m_pyramidMask;
        std::string m_imageName;
        std::string m_depthName;

        cv::Ptr<cv::ximgproc::StructuredEdgeDetection> m_sforestDetector;
        std::vector<cv::Mat> m_pyramidImageSF;
        Sequence* m_seq;


        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic, Eigen::RowMajor> m_GX;


};
}

#endif //FRAME_H