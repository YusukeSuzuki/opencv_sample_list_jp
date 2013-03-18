#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>

cv::Mat depth_to_color_lut()
{
	auto lut = cv::Mat(256, 1, CV_8UC3);

	lut.ptr(0,0)[0] = 0;
	lut.ptr(0,0)[1] = 0;
	lut.ptr(0,0)[2] = 0;

	for(int i = 1; i < 256; ++i)
	{
		double n = double(i) / 256;

		lut.ptr(i,0)[0] = std::max(0., 1. - pow((n -   1) * 2, 2)) * 255;
		lut.ptr(i,0)[1] = std::max(0., 1. - pow((n - 0.5) * 2, 2)) * 255;
		lut.ptr(i,0)[2] = std::max(0., 1. - pow( n        * 2, 2)) * 255;
	}

	return lut;
}

enum option_state
{
	bgr_image,
	gray_image,
	disparity_map,
	valid_depth_mask,
	gray_depth_image,
	end,
};

option_state operator++(option_state& state)
{
	return state =
		static_cast<option_state>( (static_cast<int>(state) + 1) % end );
}

option_state print_option_state(option_state state)
{
	switch(state)
	{
	case bgr_image:
		std::cout << "displaying sensor bgr image" << std::endl;
		break;
	case gray_image:
		std::cout << "displaying sensor gray image" << std::endl;
		break;
	case disparity_map:
		std::cout << "displaying disparity map" << std::endl;
		break;
	case valid_depth_mask:
		std::cout << "displaying valid depth mask" << std::endl;
		break;
	case gray_depth_image:
		std::cout << "displaying depth image(gray)" << std::endl;
		break;
	default: std::cout << "state is not defined" << std::endl;
		break; 
	}

	return state;
}

int main(int argc, char* argv[])
{
	cv::VideoCapture capture;

	capture.open( CV_CAP_OPENNI );

	if( !capture.isOpened() )
	{
		std::cout << "fail to open capture device." << std::endl;
		return 0;
	}

	bool to_continue = true;

	cv::Mat depth_image;
	cv::Mat depth_gray_image;
	cv::Mat depth_color_image;

	cv::Mat option_image;

	std::cout << "frame width: " <<
		capture.get(CV_CAP_PROP_FRAME_WIDTH) << std::endl;
	std::cout << "frame height: " <<
		capture.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;
	std::cout << "max depth: " <<
		capture.get(CV_CAP_PROP_OPENNI_FRAME_MAX_DEPTH) << std::endl;

	cv::Mat lut = depth_to_color_lut();

	auto option_image_state = print_option_state(bgr_image);

	cv::namedWindow("option image");
	cv::namedWindow("depth image(color mapped)");

	while( to_continue )
	{
		if( !capture.grab() )
		{
			std::cout << "fail to grab frame" << std::endl;
			to_continue = false;
		}

		if(!to_continue) break;


		if( !capture.retrieve(depth_image, CV_CAP_OPENNI_DEPTH_MAP) )
		{
			std::cout << "fail to retrieve frame" << std::endl;
			to_continue = false;
		}

		if(!to_continue) break;

		depth_image.convertTo(depth_gray_image, CV_8U, 0.05);
		cv::cvtColor(depth_gray_image, depth_color_image, CV_GRAY2BGR);
		cv::LUT(depth_color_image, lut, depth_color_image);

		switch(option_image_state)
		{
		case bgr_image:
			if( !capture.retrieve(option_image, CV_CAP_OPENNI_BGR_IMAGE) )
			{
				std::cout << "fail to retrieve frame" << std::endl;
				to_continue = false;
			}
			break;
		case gray_image:
			if( !capture.retrieve(option_image, CV_CAP_OPENNI_GRAY_IMAGE) )
			{
				std::cout << "fail to retrieve frame" << std::endl;
				to_continue = false;
			}
			break;
		case disparity_map:
			if( !capture.retrieve(option_image, CV_CAP_OPENNI_DISPARITY_MAP) )
			{
				std::cout << "fail to retrieve frame" << std::endl;
				to_continue = false;
			}
			break;
		case valid_depth_mask:
			if( !capture.retrieve(option_image, CV_CAP_OPENNI_VALID_DEPTH_MASK) )
			{
				std::cout << "fail to retrieve frame" << std::endl;
				to_continue = false;
			}
			break;
		case gray_depth_image:
			option_image = depth_gray_image;
			break;
		default:
			print_option_state( option_image_state );
			to_continue = false;
			break;
		}

		if(!to_continue) break;

		cv::imshow("option image", option_image);
		cv::imshow("depth image(color mapped)", depth_color_image);

		auto key = cv::waitKey(50);

		if(key == ' ')
		{
			option_image_state =
				print_option_state( ++option_image_state );
		}
		else if(key >= 0)
		{
			to_continue = false;
		}
	}

	return 0;
}

