OpenCV 2.4.0 のサンプルソースの一覧(samples/cpp)
================================================================================

OpenCV 2.4.0 に添付されているサンプルコードがどんなものなのか概観できるようにするためのリストです。

「OpenCV.jp : OpenCV逆引きリファレンス( http://opencv.jp/cookbook/ )」で同等の機能の解説がフォローされているものについては、そちらへのURLを記載します。

.. |cooked| replace:: **（クックブックでフォローされている）**

.. contents:: 目次

基本的なコーディング
--------------------------------------------------------------------------------
- cout_mat.cpp
	行列の標準出力(std::cout)のサンプル
	
	|cooked|

	- http://opencv.jp/cookbook/opencv_mat.html#cv-mat-std-cout
- filestorage.cpp
	ファイルストレージのサンプル。任意の構造をyamlやxmlに書き出す。

	|cooked|

	- http://opencv.jp/cookbook/opencv_io.html#yaml-xml
- image.cpp
	画像を格納するデータ型の相互変換のサンプル。IplImageからcv::Mat、cv::vectorへの変換。
	表色系の変換。ピクセルへのアクセス方法等。

	|cooked|

	- http://opencv.jp/cookbook/opencv_mat.html#cv-matiplimage
- imagelist_creator.cpp
	画像ファイルのリストをyaml / xml フォーマットで出力するサンプル。サンプルというよりもむしろ画像ファイルの集合を利用する他のサンプルへのデータ作成に使用する。
- opencv_version.cpp
	バージョン情報の出力

	|cooked|

	- http://opencv.jp/cookbook/opencv_utility.html#opencv
- starter_imagelist.cpp
	imagelist.cppで作成したファイルからの画像の読み込みサンプル。画像ファイルをすべてコマンドライン引数で指定するのは大変なので、こうやって保存してこうやって読み込みましょうというお話。
- starter_video.cpp
	動画ファイルあるいはビデオデバイス（カメラやキャプチャカード）からの動画読み込みと、フレームの保存のサンプル

	|cooked|

	- http://opencv.jp/cookbook/opencv_io.html#id6

描画処理
--------------------------------------------------------------------------------
- drawing.cpp
	線分、円、楕円、矩形、塗りつぶしの描画処理のサンプル

	|cooked|

	- http://opencv.jp/cookbook/opencv_drawing.html
- gencolors.cpp
	cv::generateColors()を利用した任意の個数の異なる色を生成するサンプル。データ可視化などのために異なるラベル色を作ったりするのに使う。


基本的な画像処理
--------------------------------------------------------------------------------
- edge.cpp
	Cannyエッジ抽出のサンプル

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id19
- demhist.cpp
	ヒストグラム算出のサンプル。指定した画像ファイルのグレイスケール値のヒストグラムを算出しグラフを表示する。輝度、コントラストをスライドバーで変化させ、ヒストグラムがどのように変形するかを見ることもできる。

	|cooked|
	- http://opencv.jp/cookbook/opencv_img.html#id34
- dft.cpp
	離散フーリエ変換（DFT）のサンプル。指定した画像ファイルのDFT/逆DFTの結果画像を表示する。
- laplace.cpp
	ラプラシアンフィルタのサンプル

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id19
- logpolar_bsm.cpp
	Log-Polar変換のサンプル
- morphology2.cpp
	モルフォロジー変換のサンプル

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id14
- inpaint.cpp
	inpainting。cv::inpaint()を使用したノイズ除去、欠損画像補完のサンプル。
	マウスドラッグによって塗りつぶした画像の領域を、その周囲の画素値にしたがって補完する。

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id25

統計・統計的手法
--------------------------------------------------------------------------------
- em.cpp
	EM法による分布の推定のサンプル
- kalman.cpp
	カルマンフィルタのサンプル
- kmeans.cpp
	kmeansクラスタリングのサンプル
- points_classifier.cpp
	点分類機の作成

計算幾何
--------------------------------------------------------------------------------
- convexhull.cpp
	座標群の凸包算出のサンプル

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id20
- delaunay2.cpp
	ドロネー図・ボロノイ図算出のサンプル。ランダムな点群からドロネー三角形分割を逐次的に行う。ドロネー三角形分割からボロノイ領域の算出を行う。
- distrans.cpp
	距離変換のサンプル

- minarea.cpp
	座標群の最小包含矩形・最小包含円の算出のサンプル

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id20


検出処理（古典的）
--------------------------------------------------------------------------------
- contours2.cpp
	輪郭抽出のサンプル。

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id54

- connected_components.cpp
	輪郭ベースの接続領域抽出のサンプル

	しきい値で二値化した画像の白領域の連結領域の抽出を行うサンプル。
	cv::findContours() でトップレベルの輪郭を抽出し、それを塗りつぶして連結領域として表示している。
	また二値化は cv::Mat と double の比較演算子のオーバーロードを使用している。単純な数値比較による二値化を簡潔に記述するサンプルでもある。

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id54

- fitellipse.cpp
	楕円当てはめのサンプル。抽出した輪郭に cv::fitEllipse() で楕円当てはめを行う。

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id30

- squares.cpp
	四角形抽出のサンプル。Cannyエッジ画像から抽出した輪郭成分を cv::approxPolyDP() で多角形近似し、近似結果の角の数が4つのものを4角形として表示している。

	画像ピラミッドを用いたノイズ除去やCannyエッジによるグラデーションのある形状の輪郭抽出の工夫も参考になる。

- houghcircles.cpp
	ハフ変換による円の検出のサンプル。
	
	cv::HoughCircles() によりグレイスケール画像から円を検出する。
	
	|cooked|
	
	- http://opencv.jp/cookbook/opencv_img.html#id29	

- houghlines.cpp
	ハフ変換による線分の検出処理のサンプル。

	cv::HoughLinesP() により、エッジ画像から線分を検出する。

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id26
		
		cv::HoughLines() による直線の検出


検出処理（最近のアルゴリズム）
--------------------------------------------------------------------------------
- chamfer.cpp
	Chamfer マッチングのサンプル。輪郭によるロゴ検出。

	- `cv::chamerMatching()のサンプル`_

.. _cv::chamerMatching()のサンプル : ./cpp_samples/chamfer/README.rst

- peopledetect.cpp
	HOG/SVMによる人検出のサンプル。

	|cooked|

	- http://opencv.jp/cookbook/opencv_img.html#id43

トラッキング系 / 動体検出系
--------------------------------------------------------------------------------
- bgfg_segm.cpp
	混合ガウスモデルの背景差分による動体検出のサンプル。

	cv::BackgroundSubtractorMOG2 を使用している。

- segment_objects.cpp
	混合ガウスモデルの背景差分による動体検出のサンプル。

	cv::BackgroundSubtractorMOG を使用している。

- camshiftdemo.cpp
	CamShiftによる領域追跡のサンプル。

- lkdemo.cpp
	LKトラッキングのサンプル。

- phase_corr.cpp
	ビデオから画像全体の並進移動を検出するサンプル。
	カメラの前に印刷物などをかざして動かすと動作がよくわかる。

	cv::phaseCorrelate() を使用している。

以下、未調査
--------------------------------------------------------------------------------

ステレオ系 / カメラ校正系
--------------------------------------------------------------------------------
- 3calibration.cpp
	キャリブレーション関係（環境がない）
- calibration.cpp
	カメラキャリブレーションのサンプル
- calibration_artificial.cpp
	カメラキャリブレーションのサンプル、人工画像で模擬的に行っているらしい
- stereo_calib.cpp
	ステレオカメラの校正
- stereo_match.cpp
	ステレオマッチング

そのほか最近のアルゴリズムのデモ
--------------------------------------------------------------------------------
- grabcut.cpp
	grabcut デモ
- stitching.cpp
	イメージスティッチング
- stitching_detailed.cpp
	より詳細な設定のできるイメージスティッチング

その他、特殊な実効環境がいるもの
--------------------------------------------------------------------------------
- OpenEXRimages_HighDynamicRange_Retina_toneMapping.cpp
	OpenEXR関係（環境がない）
- OpenEXRimages_HighDynamicRange_Retina_toneMapping_video.cpp
	OpenEXR関係（環境がない）
- hybridtrackingsample.cpp
	SIFTの実装が必要
- linemod.cpp
	OpenNI関係
- openni_capture.cpp
	OpenNI関係

未分類
--------------------------------------------------------------------------------
- bagofwords_classification.cpp
	Bag of Words分類器
	実行がちょっと面倒
- brief_match_test.cpp
	BriefExtractorを用いたマッチング
- build3dmodel.cpp
	ロドリゲス変換のサンプル、ただし未完成で置換予定
- descriptor_extractor_matcher.cpp
	特徴量によるマッチング、要調査
- detection_based_tracker_sample.cpp
	要調査
- detector_descriptor_evaluation.cpp
	要調査
- detector_descriptor_matcher_evaluation.cpp
	要調査
- facerec_demo.cpp
	顔認識デモ
- fback.cpp
	dense optical flow のデモ Gunner Farneback
- ffilldemo.cpp
	フラッドフィルのデモ
- generic_descriptor_match.cpp
	ジェネリックデスクリプタのデモ
- latentsvm_multidetect.cpp
	latentSVM 検出のデモ
- letter_recog.cpp
	文字認識のデモ
- matcher_simple.cpp
	SURFマッチング
- matching_to_many_images.cpp
	SURFマッチング
- meanshift_segmentation.cpp
	mean-shiftによるカラーセグメンテーション
- multicascadeclassifier.cpp
	複数の分類器のカスケーディング
- point_cloud.cpp
	ポイントクラウドの描画？
- retinaDemo.cpp
	Gipsa/Listic Labs retina model のデモ
- rgbdodometry.cpp
	RGBD(深度付き画像)でのオドメトリ
- select3dobj.cpp
	オブジェクトのデータセットとそのセグメンテーションマスクの収集
- video_dmtx.cpp
	ビデオフレームのセーブ
- video_homography.cpp
	特徴量ベースのビデオ処理
- videostab.cpp
	ちょっと不明
- watershed.cpp
	色セグメンテーション

