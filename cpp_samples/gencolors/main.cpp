#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <ctime>

const int block_size = 80;
const int margin = 5;

const int width = 640;
const int height = 480;

const uint64_t random_seed = 19771228;

int main(int argc, char* argv[])
{
	/**
	 * 乱数生成器のシードの初期化
	 *
	 * cv::RNGはスレッドローカルな乱数生成器
	 * cv::theRNG()はOpenCVで確保された乱数生成器を返す
	 *
	 * cv::generateColors()は内部でtheRNG()を使用している。
	 */
	cv::theRNG() = random_seed;

	const int cols = width / block_size;
	const int rows = height / block_size;

	std::cout <<
		"this program shows performance of cv::generateColors()." <<
		std::endl <<
		"usage: " << argv[0] <<
		" [num_colors(= " << (cols * rows) << ") [factor(=100)]]" <<
		std::endl <<
		"ESC: quit" << std::endl <<
		"Others: generate other colors" << std::endl;

	// 色数、無入力の場合は48
	int colors_count =
		[](int i) { return i ? i : cols * rows; }(
			std::max(atoi(argc < 2 ? "" : argv[1]), 0) );

	// ファクター、入力なしの場合は100
	int factor =
		[](int i) { return i ? i : 100; }(
			std::max(atoi(argc < 3 ? "" : argv[2]), 0) );

	cv::namedWindow("random color");

	for(bool next = true; next; next = cv::waitKey() != 27)
	{
		std::vector<cv::Scalar> colors;

		/**
		 * colors_count のランダムな色を生成する。
		 * cv::generateColors()は colors_count * factor のBGR色を一回生成し、
		 * LAB色空間上でそれぞれの色が最も離れる色を colors_count 選び出す。
		 *
		 * そのため colors_count あるいは factor が大きな数である場合、
		 * CPUやメモリを多く消費する。
		 */
		cv::generateColors(colors, colors_count, factor);

		auto image = cv::Mat(height, width, CV_8UC3) = cv::Scalar(255,255,255);

		for(int i = 0; i < colors_count; ++i)
		{
			int x = (i % cols) * block_size + margin;
			int y = (i / cols) * block_size + margin;
			int bs = block_size - margin * 2;

			cv::rectangle(image, cv::Rect(x, y, bs, bs), colors[i], -1);
		}

		cv::imshow("random color", image);
	}

	return 0;
}

