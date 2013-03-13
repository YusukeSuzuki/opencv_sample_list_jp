#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

// DFTのための複素画像を作成する
void create_complex_dft_image(const cv::Mat& in, cv::Mat& out)
{
	using namespace cv;

	Mat real_image; // 複素画像の実部

	/**
	 * DFTを行うには画像の両辺それぞれがDFTに適したサイズであることが必要。
	 * 入力画像をDFTに適したサイズに拡大してコピーした上であまりを塗りつぶす。
	 *
	 * cv::getOptimalDFTSize()はDFT入力された大きさに対してDFTに適した大きさを返す。
	 *
	 * cv::copyMakeBorder()は入力画像の周囲を指定幅分だけ塗りつぶして出力画像に
	 * コピーする。
	 *
	 * 今回は、DFTのサイズに拡大する分だけ右端と下端を0で塗りつぶしている。
	 */
	copyMakeBorder(in, real_image,
		0, getOptimalDFTSize(in.rows) - in.rows,
		0, getOptimalDFTSize(in.cols) - in.cols,
		BORDER_CONSTANT, Scalar::all(0) );

	// 0で埋めた虚部とマージして複素画像にする。
	Mat planes[] = {Mat_<float>(real_image), Mat::zeros(real_image.size(), CV_32F)};
	merge(planes, 2, out);
}

// DFTの結果である複素画像を表示用の強度画像に変換する。
void create_fourier_magnitude_image_from_complex(const cv::Mat& in, cv::Mat& out)
{
	using namespace cv;

	/**
	 * 複素画像の実部と虚部を2枚の画像に分離する。
	 */
	Mat planes[2];
	split(in, planes);

	/**
	 * cv::magnitude()で二枚の画像から強度を算出する。
	 *
	 * 強度画像の各ピクセル値の擬似コード
	 * dst(x,y) = sqrt(pow( src1(x,y),2) + pow(src2(x,y),2) )
	 */
	magnitude(planes[0], planes[1], out);

	/**
	 * 表示用に対数に変換する。そのため各ピクセルに1を加算しておく。
	 */
	out += Scalar::all(1);
	log(out, out);

	/**
	 * 以下に続く入れ替えのために、画像の両辺のサイズを偶数にしておく
	 */
	out = out( Rect(0, 0, out.cols & -2, out.rows & -2) );


	/**
	 * cv::dft()で得られる画像を一般的な二次元DFTの表示様式にする。
	 *
	 * 具体的には以下のように画像の各四半分を入れ替える。
	 *
	 * +----+----+    +----+----+
	 * |    |    |    |    |    |
	 * | q0 | q1 |    | q3 | q2 |
	 * |    |    |    |    |    |
	 * +----+----+ -> +----+----+
	 * |    |    |    |    |    |
	 * | q2 | q3 |    | q1 | q0 |
	 * |    |    |    |    |    |
	 * +----+----+    +----+----+
	 */
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

	// 濃淡を強調するために、画像最小値を0に、最大値を1にするように正規化する。
	normalize(out, out, 0, 1, CV_MINMAX);
}

// 逆DFTで得られた画像を実画像に変換する。
void create_inverse_fourier_image_from_complex(
	const cv::Mat& in, const::cv::Mat& origin, cv::Mat& out)
{
	using namespace cv;

	// 複素画像の実部と虚部を2枚の画像に分離する。
	Mat splitted_image[2];
	split(in, splitted_image);

	/**
	 * 実部について正規化を行う。
	 * 入力画像のサイズはDFT用に拡大されているので、原画像の同サイズにROIを設定して
	 * 縮小する。
	 */
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

	/**
	 * フーリエ変換
	 *
	 * 複素画像から複素画像へ変換する。ここでは入力画像自体を出力先にしている。
	 *
	 * 呼び出し時のオプションにより複素画像から実画像への変換などもできる。
	 */
	cv::dft(complex_image, complex_image);

	// フーリエ変換の結果の可視化
	cv::Mat magnitude_image;
	create_fourier_magnitude_image_from_complex(complex_image, magnitude_image);

	/**
	 * 逆フーリエ変換
	 *
	 * 複素画像から複素画像へ変換する。ここでは入力画像自体を出力先にしている。
	 *
	 * 呼び出し時のオプションにより複素画像から実画像への変換などもできる。
	 */
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

	/**
	 * 結果画像の保存
	 *
	 * 表示画像は浮動小数表現で値域が[0,1]なので255を掛けたものを入力とする。
	 */
	cv::imwrite(std::string(argv[1]) + ".dft.jpg", magnitude_image * 255);
	cv::imwrite(std::string(argv[1]) + ".idft.jpg", idft_image * 255);

	return 0;
}

