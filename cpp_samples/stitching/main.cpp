#include <opencv2/stitching/stitcher.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

// 動作オプション
struct options
{
	bool show_help;
	std::vector<std::string> filenames;
	std::string imagelist_filename;
	std::string output_filename;
	bool show_result;
};

options get_options(cv::CommandLineParser& parser);
std::vector<cv::Mat> read_images(const std::vector<std::string>& filename);
std::vector<std::string> read_imagelist(const std::string& filename);

// std::for_each の全範囲ラッパー
template<typename T, typename F>
auto for_each(T t, F f) -> F
{
	return std::for_each(t.begin(), t.end(), f);
}

int
main(int argc, char* argv[])
{
	// cv::CommandLineParserに渡すオプションの書式
	// 以下の順に記述する。
	// 省略名 (-hの形式) | 完全名 (--helpの形式) | デフォルト値 (省略可能) | 説明
	const char* option_keys =
		"{h| help| false| show help message}"
		"{o| out| out.png| output file name}"
		"{s| show| false| show output in window}"
		"{l| imagelist| | imagelist filename}"
		"{i| images| | image filenames separated with comma}";

	cv::CommandLineParser parser(argc, argv, option_keys);

	auto options = get_options(parser);

	if(options.show_help)
	{
		std::cout << "This program is sample code of cv::Stitcher." << std::endl; 

		// cv::CommandLineParser::printParams() はオプションの概説を std::cout に出力する。
		parser.printParams();
		return 0;
	}

	// imagelist に記述されたファイル名を取得
	auto imagelist = read_imagelist(options.imagelist_filename);

	// コマンドライン引数で渡されたファイル名と結合
	imagelist.insert(imagelist.end(),
		options.filenames.begin(), options.filenames.end());

	// 全画像ファイルを読み込み
	auto images = read_images(imagelist);

	if( images.empty() )
	{
		std::cout << "no image read" << std::endl;
		return -1;
	}

	if( images.size() != imagelist.size() )
	{
		std::cout << "some images are not able to be loaded" << std::endl;
	}

	cv::Mat panorama;

	auto stitcher = cv::Stitcher::createDefault(false);

	// cv::Stitcher::stitch() のみでスティッチングを行える。
	auto status = stitcher.stitch(images, panorama);

	if( status != cv::Stitcher::OK )
	{
		std::cout << "stitching failed" << std::endl;
		return -1;
	}

	if(options.show_result)
	{
		cv::namedWindow("image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
		cv::imshow("image", panorama);
		cv::waitKey();
	}

	cv::imwrite(options.output_filename, panorama);

	return 0;
}

// コマンドライン引数の解釈
options get_options(cv::CommandLineParser& parser)
{
	options options;

	options.show_help = parser.get<bool>("help");
	options.imagelist_filename = parser.get<std::string>("imagelist");

	std::stringstream ss( parser.get<std::string>("images") );

	for(std::string s; getline(ss, s, ',');)
	{
		options.filenames.push_back(s);
	}

	options.show_result = parser.get<bool>("show");
	options.output_filename = parser.get<std::string>("out");

	return options;
}

// 画像の読み込み
std::vector<cv::Mat> read_images(const std::vector<std::string>& filenames)
{
	std::vector<cv::Mat> result;

	for_each(filenames, [&result](const std::string& str)
		{
			auto img  = cv::imread(str);

			if( img.empty() )
			{
				std::cout << "can't read image: " << str << std::endl;
			}
			else
			{
				std::cout << "read image: " << str << std::endl;
				result.push_back(img);
			}
		} );

	return result;
}

// imagelistの読み込み
std::vector<std::string> read_imagelist(const std::string& filename)
{
	if( filename.empty() )
	{
		return {};
	}

	cv::FileStorage fs(filename, cv::FileStorage::READ);

	if( not fs.isOpened() )
	{
		return {};
	}

	std::vector<std::string> result;

	for_each(fs.getFirstTopLevelNode(),
		[&result](const cv::FileNode& n) { result.push_back( (std::string)(n) ); });

	return result;
}

