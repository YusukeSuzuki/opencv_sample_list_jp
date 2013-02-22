#include <opencv2/contrib/contrib.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// 画像の std::vector<cv::Point> に格納されたピクセル座標に色を設定する
void
dots(const std::vector<cv::Point>& points, cv::Mat& dst, const cv::Scalar& color)
{
	for(const auto& p : points)
	{
		if(p.inside(cv::Rect(0,0,dst.cols,dst.rows)))
		{
			dst.at<cv::Vec3b>(p) = cv::Vec3b(color[0], color[1], color[2]);
		}
	}
}

int
main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cout << "usage: " << argv[0] << " template_img search_image" << std::endl;
		return 0;
	}

	// テンプレート画像の読み込み
	// あらかじめCannyエッジなどで線画化されていること
	auto template_img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

	if( template_img.empty() )
	{
		std::cout << "can't read " << argv[1] << std::endl;
		return -1;
	}

	// 探索画像の読み込み
	auto search_image = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);

	if( search_image.empty() )
	{
		std::cout << "can't read " << argv[2] << std::endl;
		return -1;
	}

	// 探索画像の線画化
	cv::Mat search_edge_image;
	cv::Canny(search_image, search_edge_image, 50, 200);

	// 結果 座標群
	// マッチした窓座標ごとに、探索画像内でテンプレートのエッジにマッチした座標が格納される
	std::vector<std::vector<cv::Point>> results;

	// 結果 コスト
	// マッチした窓座標ごとに、マッチングのコストが格納される
	std::vector<float> costs;

	// chamfer matchingを行う
	// OpenCV 2.4.3の時点で chamerMatching という名前になっている。
	auto best = cv::chamerMatching(
			search_edge_image, template_img, results, costs,
			1, // templScale、テンプレート画像の倍率。逆数
			20, // maxMatches、結果の最大数。
			1, // minMatchDistance
			3, // padX、探索窓のX方向の移動画素数
			3, // padY、探索窓のY方向の移動画素数
			5, // scales、スケーリングの段階数
			0.6, // minScale、テンプレートの最小スケーリング倍率
			1.6, // maxScale、テンプレートの最大スケーリング倍率
			0.5, // orientationWeight
			20 // truncate
			);

	// cv::chamerMatching() はもっともマッチした結果のインデックスを返す
	// 負の値を返した場合、マッチング失敗
	if(best < 0)
	{
		std::cout << "matching failed" << std::endl;
		return 0;
	}

	std::cout << "best: " << best << std::endl;
	std::cout << "costs: " << std::endl;

	for(auto c : costs)
	{
		std::cout <<  c << std::endl;
	}

	// 結果画像の生成
	// 白黒のエッジ画像にカラーで描画するため色空間を変換
	cv::Mat display_image;
	cv::cvtColor(search_edge_image, display_image, CV_GRAY2BGR);

	// すべての結果を緑で描画
	for(const auto& result : results)
	{
		dots(result, display_image, cv::Scalar(0,255,0));
	}

	// ベストの結果を赤で描画
	dots(results[best], display_image, cv::Scalar(0,0,255));

	// 結果画像の表示
	cv::namedWindow("result");
	cv::imshow("result", display_image);
	cv::waitKey();

	// 結果画像の保存
	cv::imwrite("out.png", display_image);

	return 0;
}

