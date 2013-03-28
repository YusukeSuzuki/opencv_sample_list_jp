#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc//imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>

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

	// Data Matrixのコードが格納される
	std::vector<std::string> codes;

	// Data Matrixの4すみが格納される
	cv::Mat corners;

	/**
	 * Data Matrixを検出する
	 *
	 * 現在の実装だと3文字までのテキストのData Matrixにしか対応しない。
	 */
	cv::findDataMatrix(image, codes, corners);

	/**
	 * 4すみを格納する行列のフォーマット。
	 *
	 * 行数 : 検出数
	 * 列数 : 4
	 * データ型 : CV_32SC2 (第1チャネル : X座標, 第2チャネル : Y座標)
	 */
	std::cout << "cols " << corners.cols <<
		", rows " << corners.rows <<
		", channels " << corners.channels() <<
		std::endl;

	// 検出領域の行列の出力
	std::cout << corners << std::endl;

	// 検出したコードの内容の出力
	for(int i = 0; i < corners.rows; ++i)
	{
		std::cout << "code: " << codes[i] << ", corners: " <<
			corners.cols << std:: endl;
	}

	cv::Mat result;
	cvtColor(image, result, CV_GRAY2BGR);

	/**
	 * 結果を画像として描画する
	 *
	 * 検出領域を線で囲い、左下にコードのテキストを描画する。
	 */
	cv::drawDataMatrixCodes(result, codes, corners);

	cv::namedWindow("image");
	cv::imshow("image", image);
	cv::namedWindow("result");
	cv::imshow("result", result);
	cv::waitKey();

	return 0;
}

