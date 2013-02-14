OpenCV 2.4.0 のサンプルソースの一覧(samples/cpp)
================================================================================

OpenCV 2.4.0 に添付されているサンプルコードがどんなものなのか概観できるようにするためのリストです。

.. |cooked| replace:: **（クックブックでフォローされている）**

.. contents:: 目次

基本的なコーディング
--------------------------------------------------------------------------------
- cout_mat.cpp |cooked|
	行列の標準出力(std::cout)のサンプル
- filestorage.cpp
	ファイルストレージデモ
- image.cpp
	CvMat / IplImage変換デモ
- imagelist_creator.cpp
	画像ファイルのリストをyaml / xml フォーマットで出力するデモ
- opencv_version.cpp
	バージョン情報
- starter_imagelist.cpp
	image listからの読み込み
- starter_video.cpp
	ビデオデバイスからの読み込み

描画処理
--------------------------------------------------------------------------------
- drawing.cpp
	線分、円、楕円、矩形、塗りつぶしの描画処理のデモ
- gencolors.cpp
	色を生成する。コードスニペット


基本的な画像処理
--------------------------------------------------------------------------------
- edge.cpp
	Cannyエッジ抽出
- demhist.cpp
	ヒストグラム算出のサンプル
- dft.cpp(クックブックに未掲載)
	離散フーリエ変換
- laplace.cpp
	ラプラシアンフィルタのデモ
- logpolar_bsm.cpp
	Log-Polar変換のデモ
- morphology2.cpp
	モルフォロジー変換
- inpaint.cpp
	inpainting 欠損画像補完のデモ

統計・統計的手法
--------------------------------------------------------------------------------
- em.cpp
	EM法によるクラスタリング
- kalman.cpp
	カルマンフィルタのデモ
- kmeans.cpp
	kmeansクラスタリングのデモ

計算幾何
--------------------------------------------------------------------------------
- convexhull.cpp
	座標群の凸包算出のサンプル
- delaunay2.cpp
	ドロネー図算出のサンプル
- distrans.cpp
	距離変換
- minarea.cpp
	最小包含矩形・最小包含円


検出処理（古典的）
--------------------------------------------------------------------------------
- connected_components.cpp
	輪郭ベースの接続領域抽出のサンプル
- contours2.cpp
	輪郭抽出のサンプル
- fitellipse.cpp
	楕円当てはめのデモ
- houghcircles.cpp
	ハフ変換による円の検出
- houghlines.cpp
	ハフ変換による線分の検出
- squares.cpp
	矩形当てはめ

検出処理（最近のアルゴリズム）
--------------------------------------------------------------------------------
- chamfer.cpp
	Chamfer マッチングのサンプル。輪郭によるロゴ検出
- peopledetect.cpp
	HOG/SVMによる人認識

トラッキング系 / 動体検出系
--------------------------------------------------------------------------------
- bgfg_segm.cpp
	中央値背景差分
- camshiftdemo.cpp
	CamShiftによる領域追跡のサンプル
- lkdemo.cpp
	LKトラッキングのデモ
- phase_corr.cpp
	モーション関係
- points_classifier.cpp
	点分類機の作成
- segment_objects.cpp
	背景差分

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

未調査
--------------------------------------------------------------------------------

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

