#ifndef _BRIEFEXTRACTOR
#define _BRIEFEXTRACTOR
#include "opencv2/core/core.hpp"
#include "opencv2/core/internal.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
class BriefExtractor{
public:
	cv::Mat mSum;

	BriefExtractor();
	~BriefExtractor();

	void computeIntegralImg(const cv::Mat& image);

	void compute(const cv::Mat& image, cv::KeyPoint& keyPt, cv::Mat& desc);
	void compute(const cv::Mat &image, std::vector<cv::KeyPoint> &kpts, cv::Mat &descriptors);

	static void pixelTests32_single(const cv::Mat& sum, const cv::KeyPoint& kpt, cv::Mat& descriptor);
	static void pixelTests32(const cv::Mat& sum, const std::vector<cv::KeyPoint>& keypoints, cv::Mat& descriptors);
};
#endif
