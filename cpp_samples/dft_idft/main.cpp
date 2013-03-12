#include <opencv2/contrib/contrib.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

void create_complex_dft_image(const cv::Mat& in, cv::Mat& out)
{
	using namespace cv;

	Mat padded;

	copyMakeBorder(in, padded,
		0, getOptimalDFTSize(in.rows) - in.rows,
		0, getOptimalDFTSize(in.cols) - in.cols,
		BORDER_CONSTANT, Scalar::all(0) );

	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};

	merge(planes, 2, out);
}

void create_fourier_magnitude_image_from_complex(const cv::Mat& in, cv::Mat& out)
{
	using namespace cv;

	Mat planes[2];
	split(in, planes);

	magnitude(planes[0], planes[1], out);

	out += Scalar::all(1);

	log(out, out);

	out = out(
		Rect(0, 0, out.cols & -2, out.rows & -2) );

	normalize(out, out, 0, 1, CV_MINMAX);

	const int half_width = out.cols / 2;
	const int half_height = out.rows / 2;

	Mat tmp;

	Mat q0(out,
		Rect(0,0,half_width,half_height));
	Mat q1(out,
		Rect(half_width,0,half_width,half_height));
	Mat q2(out,
		Rect(0,half_height,half_width,half_height));
	Mat q3(out,
		Rect(half_width,half_height,half_width,half_height));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

void create_inverse_fourier_image_from_complex(
	const cv::Mat& in, const::cv::Mat& origin, cv::Mat& out)
{
	using namespace cv;

	Mat splitted_image[2];

	split(in, splitted_image);

	splitted_image[0](cv::Rect(0, 0, origin.cols, origin.rows)).copyTo(out);
	cv::normalize(out, out, 0, 1, CV_MINMAX);
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "usage: " << argv[0] << " image" << std::endl;
		return 0;
	}

	// 画像の読み込み
	auto image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

	if( image.empty() )
	{
		std::cout << "can't read " << argv[1] << std::endl;
		return -1;
	}

	// フーリエ変換のために適切なサイズの複素画像を作る
	cv::Mat complex_image;
	create_complex_dft_image(image, complex_image);

	// フーリエ変換
	cv::dft(complex_image, complex_image);

	// フーリエ変換の結果の可視化
	cv::Mat magnitude_image;
	create_fourier_magnitude_image_from_complex(complex_image, magnitude_image);

	// 逆フーリエ変換
	cv::idft(complex_image, complex_image);

	// 逆フーリエ変換の結果の可視化
	cv::Mat idft_image;
	create_inverse_fourier_image_from_complex(complex_image, image, idft_image);

	// 結果表示
	cv::namedWindow("original");
	cv::imshow("original", image);

	cv::namedWindow("dft");
	cv::imshow("dft", magnitude_image);

	cv::namedWindow("idft");
	cv::imshow("idft", idft_image);

	cv::waitKey(0);

	// 結果画像の保存
	cv::imwrite(std::string(argv[1]) + ".dft.jpg", magnitude_image * 255);
	cv::imwrite(std::string(argv[1]) + ".idft.jpg", idft_image * 255);

	return 0;
}

