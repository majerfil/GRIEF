/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009-2010, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "grief.h"
#include "precomp.hpp"
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace cv;

inline int smoothedSum(const Mat& sum, const KeyPoint& pt, int y, int x)
{
    static const int HALF_KERNEL = GriefDescriptorExtractor::KERNEL_SIZE / 2;

    int img_y = (int)(pt.pt.y + 0.5) + y;
    int img_x = (int)(pt.pt.x + 0.5) + x;
    return   sum.at<int>(img_y + HALF_KERNEL + 1, img_x + HALF_KERNEL + 1)
           - sum.at<int>(img_y + HALF_KERNEL + 1, img_x - HALF_KERNEL)
           - sum.at<int>(img_y - HALF_KERNEL, img_x + HALF_KERNEL + 1)
           + sum.at<int>(img_y - HALF_KERNEL, img_x - HALF_KERNEL);
}

static void pixelTests16(const Mat& sum, const std::vector<KeyPoint>& keypoints, Mat& descriptors)
{
    for (int i = 0; i < (int)keypoints.size(); ++i)
    {
        uchar* desc = descriptors.ptr(i);
        const KeyPoint& pt = keypoints[i];
	vector<int> pairs;
	ifstream in("test_pairs.grief");
    pairs.clear();
	if(fs.isOpened()){
		in >> pairs;
#define SMOOTHED(y,x) smoothedSum(sum, pt, y, x)
		desc[0] = ((SMOOTHED(pairs[1], pairs[0]) < SMOOTHED(pairs[3], pairs[2])) << 7) + ((SMOOTHED(pairs[5], pairs[4] < SMOOTHED(pair[7], pairs[6])) << 6) + ((SMOOTHED(pairs[9],pairs[8]) < SMOOTHED(pairs[11],pairs[10])) << 5) + ((SMOOTHED(pairs[13], pairs[12]) < SMOOTHED(pairs[15], pairs[14])) << 4) + ((SMOOTHED(pairs[17], pairs[16]) < SMOOTHED(pairs[19], pairs[18])) << 3) + ((SMOOTHED(pairs[21], pairs[20]) < SMOOTHED(pairs[23], pairs[22])) << 2) + ((SMOOTHED(pairs[25], pairs[24]) < SMOOTHED(pairs[27], pairs[26])) << 1) + ((SMOOTHED(pairs[29], pairs[28]) < SMOOTHED(pairs[31], pairs[30])) << 0) ;
		desc[1] = ((SMOOTHED(pairs[33], pairs[32]) < SMOOTHED(pairs[35], pairs[34])) << 7) + ((SMOOTHED(pairs[37], pairs[36] < SMOOTHED(pair[39], pairs[38])) << 6) + ((SMOOTHED(pairs[41],pairs[40]) < SMOOTHED(pairs[43],pairs[42])) << 5) + ((SMOOTHED(pairs[45], pairs[44]) < SMOOTHED(pairs[47], pairs[46])) << 4) + ((SMOOTHED(pairs[49], pairs[48]) < SMOOTHED(pairs[51], pairs[50])) << 3) + ((SMOOTHED(pairs[53], pairs[52]) < SMOOTHED(pairs[55], pairs[54])) << 2) + ((SMOOTHED(pairs[57], pairs[56]) < SMOOTHED(pairs[59], pairs[58])) << 1) + ((SMOOTHED(pairs[61], pairs[60]) < SMOOTHED(pairs[63], pairs[62])) << 0) ;
		desc[2] = ((SMOOTHED(-11, -24) < SMOOTHED(-15, -24)) << 7) + ((SMOOTHED(-15, -25) < SMOOTHED(-14, -23)) << 6) + ((SMOOTHED(16, -20) < SMOOTHED(21, -25)) << 5) + ((SMOOTHED(-9, 0) < SMOOTHED(-12, 3)) << 4) + ((SMOOTHED(25, -9) < SMOOTHED(24, -6)) << 3) + ((SMOOTHED(-18, -5) < SMOOTHED(-18, -3)) << 2) + ((SMOOTHED(25, 25) < SMOOTHED(22, 24)) << 1) + ((SMOOTHED(-5, 22) < SMOOTHED(-9, 24)) << 0) ;
		desc[3] = ((SMOOTHED(-11, -25) < SMOOTHED(-8, -25)) << 7) + ((SMOOTHED(25, 19) < SMOOTHED(22, 18)) << 6) + ((SMOOTHED(16, -20) < SMOOTHED(17, -18)) << 5) + ((SMOOTHED(5, -1) < SMOOTHED(5, 3)) << 4) + ((SMOOTHED(17, 17) < SMOOTHED(19, 17)) << 3) + ((SMOOTHED(22, 8) < SMOOTHED(23, 7)) << 2) + ((SMOOTHED(-12, 1) < SMOOTHED(-12, 2)) << 1) + ((SMOOTHED(-24, 25) < SMOOTHED(-22, 21)) << 0) ;
		desc[4] = ((SMOOTHED(-25, -18) < SMOOTHED(-22, -16)) << 7) + ((SMOOTHED(-10, -6) < SMOOTHED(-9, -6)) << 6) + ((SMOOTHED(2, -2) < SMOOTHED(-17, -19)) << 5) + ((SMOOTHED(8, 2) < SMOOTHED(3, 1)) << 4) + ((SMOOTHED(-20, -25) < SMOOTHED(0, 25)) << 3) + ((SMOOTHED(-24, -15) < SMOOTHED(-25, -14)) << 2) + ((SMOOTHED(12, -19) < SMOOTHED(15, -19)) << 1) + ((SMOOTHED(-17, -2) < SMOOTHED(-25, 0)) << 0) ;
		desc[5] = ((SMOOTHED(-5, -20) < SMOOTHED(-4, -20)) << 7) + ((SMOOTHED(2, 14) < SMOOTHED(-3, 17)) << 6) + ((SMOOTHED(-5, 9) < SMOOTHED(-6, 16)) << 5) + ((SMOOTHED(25, 19) < SMOOTHED(22, 14)) << 4) + ((SMOOTHED(4, 0) < SMOOTHED(3, -2)) << 3) + ((SMOOTHED(24, -14) < SMOOTHED(25, -15)) << 2) + ((SMOOTHED(17, 25) < SMOOTHED(11, 25)) << 1) + ((SMOOTHED(21, -17) < SMOOTHED(20, -21)) << 0) ;
		desc[6] = ((SMOOTHED(-4, -18) < SMOOTHED(-3, -16)) << 7) + ((SMOOTHED(-3, 12) < SMOOTHED(-5, 12)) << 6) + ((SMOOTHED(24, -23) < SMOOTHED(24, -25)) << 5) + ((SMOOTHED(-21, 1) < SMOOTHED(-25, 18)) << 4) + ((SMOOTHED(-25, 2) < SMOOTHED(-23, 2)) << 3) + ((SMOOTHED(-19, 22) < SMOOTHED(-20, 22)) << 2) + ((SMOOTHED(-23, 14) < SMOOTHED(-24, 18)) << 1) + ((SMOOTHED(19, -22) < SMOOTHED(25, -22)) << 0) ;
		desc[7] = ((SMOOTHED(-23, 1) < SMOOTHED(-24, 0)) << 7) + ((SMOOTHED(-23, -19) < SMOOTHED(-14, -22)) << 6) + ((SMOOTHED(-17, -17) < SMOOTHED(-14, -16)) << 5) + ((SMOOTHED(-20, 7) < SMOOTHED(-19, 7)) << 4) + ((SMOOTHED(25, -13) < SMOOTHED(17, -10)) << 3) + ((SMOOTHED(-24, -11) < SMOOTHED(-25, -10)) << 2) + ((SMOOTHED(0, -9) < SMOOTHED(2, -7)) << 1) + ((SMOOTHED(10, -25) < SMOOTHED(24, -25)) << 0) ;
		desc[8] = ((SMOOTHED(-1, -23) < SMOOTHED(5, -24)) << 7) + ((SMOOTHED(-12, -7) < SMOOTHED(-23, -20)) << 6) + ((SMOOTHED(-1, -11) < SMOOTHED(3, -15)) << 5) + ((SMOOTHED(-18, -12) < SMOOTHED(-20, -12)) << 4) + ((SMOOTHED(7, -16) < SMOOTHED(9, -12)) << 3) + ((SMOOTHED(-2, -2) < SMOOTHED(-1, -5)) << 2) + ((SMOOTHED(2, 25) < SMOOTHED(2, 23)) << 1) + ((SMOOTHED(-25, 4) < SMOOTHED(-25, 10)) << 0) ;
		desc[9] = ((SMOOTHED(23, 14) < SMOOTHED(23, 8)) << 7) + ((SMOOTHED(24, -24) < SMOOTHED(25, -14)) << 6) + ((SMOOTHED(-13, -5) < SMOOTHED(-14, -4)) << 5) + ((SMOOTHED(12, -4) < SMOOTHED(13, -4)) << 4) + ((SMOOTHED(14, -25) < SMOOTHED(13, -24)) << 3) + ((SMOOTHED(23, -4) < SMOOTHED(20, -2)) << 2) + ((SMOOTHED(-20, 11) < SMOOTHED(-18, 12)) << 1) + ((SMOOTHED(-4, -24) < SMOOTHED(-4, -25)) << 0) ;
		desc[10] = ((SMOOTHED(-25, 17) < SMOOTHED(-23, 15)) << 7) + ((SMOOTHED(-7, 18) < SMOOTHED(-3, 18)) << 6) + ((SMOOTHED(15, -7) < SMOOTHED(-8, -9)) << 5) + ((SMOOTHED(25, -8) < SMOOTHED(23, -8)) << 4) + ((SMOOTHED(16, -11) < SMOOTHED(20, -17)) << 3) + ((SMOOTHED(1, -10) < SMOOTHED(-3, -10)) << 2) + ((SMOOTHED(-25, 11) < SMOOTHED(-22, 10)) << 1) + ((SMOOTHED(24, 22) < SMOOTHED(25, 23)) << 0) ;
		desc[11] = ((SMOOTHED(-14, 8) < SMOOTHED(-14, 9)) << 7) + ((SMOOTHED(20, 14) < SMOOTHED(25, 11)) << 6) + ((SMOOTHED(19, -1) < SMOOTHED(24, 0)) << 5) + ((SMOOTHED(-15, 19) < SMOOTHED(-18, 21)) << 4) + ((SMOOTHED(-8, 20) < SMOOTHED(-10, 20)) << 3) + ((SMOOTHED(11, 10) < SMOOTHED(11, 13)) << 2) + ((SMOOTHED(24, 1) < SMOOTHED(16, 3)) << 1) + ((SMOOTHED(-4, -17) < SMOOTHED(-20, -10)) << 0) ;
		desc[12] = ((SMOOTHED(9, -11) < SMOOTHED(12, -5)) << 7) + ((SMOOTHED(-23, -13) < SMOOTHED(-21, -13)) << 6) + ((SMOOTHED(23, -14) < SMOOTHED(18, -16)) << 5) + ((SMOOTHED(4, -9) < SMOOTHED(-2, -10)) << 4) + ((SMOOTHED(-19, -3) < SMOOTHED(-16, -2)) << 3) + ((SMOOTHED(14, -12) < SMOOTHED(13, -12)) << 2) + ((SMOOTHED(7, -11) < SMOOTHED(9, -11)) << 1) + ((SMOOTHED(-4, 0) < SMOOTHED(-5, 0)) << 0) ;
		desc[13] = ((SMOOTHED(4, -23) < SMOOTHED(7, -25)) << 7) + ((SMOOTHED(17, -7) < SMOOTHED(14, -7)) << 6) + ((SMOOTHED(-3, 25) < SMOOTHED(-6, 25)) << 5) + ((SMOOTHED(-4, 6) < SMOOTHED(-9, 1)) << 4) + ((SMOOTHED(-12, -7) < SMOOTHED(-14, -8)) << 3) + ((SMOOTHED(-10, 8) < SMOOTHED(-10, 12)) << 2) + ((SMOOTHED(-19, 23) < SMOOTHED(-17, 24)) << 1) + ((SMOOTHED(-12, -20) < SMOOTHED(-16, -18)) << 0) ;
		desc[14] = ((SMOOTHED(-24, -18) < SMOOTHED(-23, -25)) << 7) + ((SMOOTHED(-25, 25) < SMOOTHED(18, 25)) << 6) + ((SMOOTHED(25, -24) < SMOOTHED(20, -25)) << 5) + ((SMOOTHED(-6, -17) < SMOOTHED(-16, -20)) << 4) + ((SMOOTHED(-3, -12) < SMOOTHED(-3, -10)) << 3) + ((SMOOTHED(9, -24) < SMOOTHED(7, -25)) << 2) + ((SMOOTHED(19, 7) < SMOOTHED(21, 11)) << 1) + ((SMOOTHED(-9, -24) < SMOOTHED(0, -25)) << 0) ;
		desc[15] = ((SMOOTHED(-4, -15) < SMOOTHED(-10, -23)) << 7) + ((SMOOTHED(-22, 7) < SMOOTHED(-23, 7)) << 6) + ((SMOOTHED(16, -7) < SMOOTHED(21, -7)) << 5) + ((SMOOTHED(-12, 3) < SMOOTHED(-13, 3)) << 4) + ((SMOOTHED(3, -5) < SMOOTHED(1, -5)) << 3) + ((SMOOTHED(-14, -4) < SMOOTHED(-13, -2)) << 2) + ((SMOOTHED(-20, -18) < SMOOTHED(-17, -18)) << 1) + ((SMOOTHED(2, 8) < SMOOTHED(6, -1)) << 0) ;
#undef SMOOTHED


		}
	 }
}

static void pixelTests32(const Mat& sum, const std::vector<KeyPoint>& keypoints, Mat& descriptors)
{
    for (int i = 0; i < (int)keypoints.size(); ++i)
    {
        uchar* desc = descriptors.ptr(i);
        const KeyPoint& pt = keypoints[i];
		vector<int> pairs;
		ifstream in("test_pairs.grief");
    	pairs.clear();
		if(fs.isOpened()){
			in >> pairs;

#define SMOOTHED(y,x) smoothedSum(sum, pt, y, x)
			desc[0] = ((SMOOTHED(-13, -12) < SMOOTHED(-10, -12)) << 7) + ((SMOOTHED(-1, 25) < SMOOTHED(-3, 23)) << 6) + ((SMOOTHED(10, 9) < SMOOTHED(11, 10)) << 5) + ((SMOOTHED(15, 18) < SMOOTHED(15, 21)) << 4) + ((SMOOTHED(16, -15) < SMOOTHED(4, 22)) << 3) + ((SMOOTHED(0, -15) < SMOOTHED(0, -14)) << 2) + ((SMOOTHED(3, 23) < SMOOTHED(1, 24)) << 1) + ((SMOOTHED(-15, -2) < SMOOTHED(5, 21)) << 0) ;
			desc[1] = ((SMOOTHED(10, 12) < SMOOTHED(14, 10)) << 7) + ((SMOOTHED(3, 6) < SMOOTHED(-4, 8)) << 6) + ((SMOOTHED(25, -4) < SMOOTHED(23, -3)) << 5) + ((SMOOTHED(13, -18) < SMOOTHED(4, -17)) << 4) + ((SMOOTHED(-13, -25) < SMOOTHED(-13, -22)) << 3) + ((SMOOTHED(-7, -16) < SMOOTHED(-1, -17)) << 2) + ((SMOOTHED(-4, -5) < SMOOTHED(-3, -6)) << 1) + ((SMOOTHED(-17, 21) < SMOOTHED(-17, 25)) << 0) ;
			desc[2] = ((SMOOTHED(-11, -24) < SMOOTHED(-15, -24)) << 7) + ((SMOOTHED(-15, -25) < SMOOTHED(-14, -23)) << 6) + ((SMOOTHED(16, -20) < SMOOTHED(21, -25)) << 5) + ((SMOOTHED(-9, 0) < SMOOTHED(-12, 3)) << 4) + ((SMOOTHED(25, -9) < SMOOTHED(24, -6)) << 3) + ((SMOOTHED(-18, -5) < SMOOTHED(-18, -3)) << 2) + ((SMOOTHED(25, 25) < SMOOTHED(22, 24)) << 1) + ((SMOOTHED(-5, 22) < SMOOTHED(-9, 24)) << 0) ;
			desc[3] = ((SMOOTHED(-11, -25) < SMOOTHED(-8, -25)) << 7) + ((SMOOTHED(25, 19) < SMOOTHED(22, 18)) << 6) + ((SMOOTHED(16, -20) < SMOOTHED(17, -18)) << 5) + ((SMOOTHED(5, -1) < SMOOTHED(5, 3)) << 4) + ((SMOOTHED(17, 17) < SMOOTHED(19, 17)) << 3) + ((SMOOTHED(22, 8) < SMOOTHED(23, 7)) << 2) + ((SMOOTHED(-12, 1) < SMOOTHED(-12, 2)) << 1) + ((SMOOTHED(-24, 25) < SMOOTHED(-22, 21)) << 0) ;
			desc[4] = ((SMOOTHED(-25, -18) < SMOOTHED(-22, -16)) << 7) + ((SMOOTHED(-10, -6) < SMOOTHED(-9, -6)) << 6) + ((SMOOTHED(2, -2) < SMOOTHED(-17, -19)) << 5) + ((SMOOTHED(8, 2) < SMOOTHED(3, 1)) << 4) + ((SMOOTHED(-20, -25) < SMOOTHED(0, 25)) << 3) + ((SMOOTHED(-24, -15) < SMOOTHED(-25, -14)) << 2) + ((SMOOTHED(12, -19) < SMOOTHED(15, -19)) << 1) + ((SMOOTHED(-17, -2) < SMOOTHED(-25, 0)) << 0) ;
			desc[5] = ((SMOOTHED(-5, -20) < SMOOTHED(-4, -20)) << 7) + ((SMOOTHED(2, 14) < SMOOTHED(-3, 17)) << 6) + ((SMOOTHED(-5, 9) < SMOOTHED(-6, 16)) << 5) + ((SMOOTHED(25, 19) < SMOOTHED(22, 14)) << 4) + ((SMOOTHED(4, 0) < SMOOTHED(3, -2)) << 3) + ((SMOOTHED(24, -14) < SMOOTHED(25, -15)) << 2) + ((SMOOTHED(17, 25) < SMOOTHED(11, 25)) << 1) + ((SMOOTHED(21, -17) < SMOOTHED(20, -21)) << 0) ;
			desc[6] = ((SMOOTHED(-4, -18) < SMOOTHED(-3, -16)) << 7) + ((SMOOTHED(-3, 12) < SMOOTHED(-5, 12)) << 6) + ((SMOOTHED(24, -23) < SMOOTHED(24, -25)) << 5) + ((SMOOTHED(-21, 1) < SMOOTHED(-25, 18)) << 4) + ((SMOOTHED(-25, 2) < SMOOTHED(-23, 2)) << 3) + ((SMOOTHED(-19, 22) < SMOOTHED(-20, 22)) << 2) + ((SMOOTHED(-23, 14) < SMOOTHED(-24, 18)) << 1) + ((SMOOTHED(19, -22) < SMOOTHED(25, -22)) << 0) ;
			desc[7] = ((SMOOTHED(-23, 1) < SMOOTHED(-24, 0)) << 7) + ((SMOOTHED(-23, -19) < SMOOTHED(-14, -22)) << 6) + ((SMOOTHED(-17, -17) < SMOOTHED(-14, -16)) << 5) + ((SMOOTHED(-20, 7) < SMOOTHED(-19, 7)) << 4) + ((SMOOTHED(25, -13) < SMOOTHED(17, -10)) << 3) + ((SMOOTHED(-24, -11) < SMOOTHED(-25, -10)) << 2) + ((SMOOTHED(0, -9) < SMOOTHED(2, -7)) << 1) + ((SMOOTHED(10, -25) < SMOOTHED(24, -25)) << 0) ;
			desc[8] = ((SMOOTHED(-1, -23) < SMOOTHED(5, -24)) << 7) + ((SMOOTHED(-12, -7) < SMOOTHED(-23, -20)) << 6) + ((SMOOTHED(-1, -11) < SMOOTHED(3, -15)) << 5) + ((SMOOTHED(-18, -12) < SMOOTHED(-20, -12)) << 4) + ((SMOOTHED(7, -16) < SMOOTHED(9, -12)) << 3) + ((SMOOTHED(-2, -2) < SMOOTHED(-1, -5)) << 2) + ((SMOOTHED(2, 25) < SMOOTHED(2, 23)) << 1) + ((SMOOTHED(-25, 4) < SMOOTHED(-25, 10)) << 0) ;
			desc[9] = ((SMOOTHED(23, 14) < SMOOTHED(23, 8)) << 7) + ((SMOOTHED(24, -24) < SMOOTHED(25, -14)) << 6) + ((SMOOTHED(-13, -5) < SMOOTHED(-14, -4)) << 5) + ((SMOOTHED(12, -4) < SMOOTHED(13, -4)) << 4) + ((SMOOTHED(14, -25) < SMOOTHED(13, -24)) << 3) + ((SMOOTHED(23, -4) < SMOOTHED(20, -2)) << 2) + ((SMOOTHED(-20, 11) < SMOOTHED(-18, 12)) << 1) + ((SMOOTHED(-4, -24) < SMOOTHED(-4, -25)) << 0) ;
			desc[10] = ((SMOOTHED(-25, 17) < SMOOTHED(-23, 15)) << 7) + ((SMOOTHED(-7, 18) < SMOOTHED(-3, 18)) << 6) + ((SMOOTHED(15, -7) < SMOOTHED(-8, -9)) << 5) + ((SMOOTHED(25, -8) < SMOOTHED(23, -8)) << 4) + ((SMOOTHED(16, -11) < SMOOTHED(20, -17)) << 3) + ((SMOOTHED(1, -10) < SMOOTHED(-3, -10)) << 2) + ((SMOOTHED(-25, 11) < SMOOTHED(-22, 10)) << 1) + ((SMOOTHED(24, 22) < SMOOTHED(25, 23)) << 0) ;
			desc[11] = ((SMOOTHED(-14, 8) < SMOOTHED(-14, 9)) << 7) + ((SMOOTHED(20, 14) < SMOOTHED(25, 11)) << 6) + ((SMOOTHED(19, -1) < SMOOTHED(24, 0)) << 5) + ((SMOOTHED(-15, 19) < SMOOTHED(-18, 21)) << 4) + ((SMOOTHED(-8, 20) < SMOOTHED(-10, 20)) << 3) + ((SMOOTHED(11, 10) < SMOOTHED(11, 13)) << 2) + ((SMOOTHED(24, 1) < SMOOTHED(16, 3)) << 1) + ((SMOOTHED(-4, -17) < SMOOTHED(-20, -10)) << 0) ;
			desc[12] = ((SMOOTHED(9, -11) < SMOOTHED(12, -5)) << 7) + ((SMOOTHED(-23, -13) < SMOOTHED(-21, -13)) << 6) + ((SMOOTHED(23, -14) < SMOOTHED(18, -16)) << 5) + ((SMOOTHED(4, -9) < SMOOTHED(-2, -10)) << 4) + ((SMOOTHED(-19, -3) < SMOOTHED(-16, -2)) << 3) + ((SMOOTHED(14, -12) < SMOOTHED(13, -12)) << 2) + ((SMOOTHED(7, -11) < SMOOTHED(9, -11)) << 1) + ((SMOOTHED(-4, 0) < SMOOTHED(-5, 0)) << 0) ;
			desc[13] = ((SMOOTHED(4, -23) < SMOOTHED(7, -25)) << 7) + ((SMOOTHED(17, -7) < SMOOTHED(14, -7)) << 6) + ((SMOOTHED(-3, 25) < SMOOTHED(-6, 25)) << 5) + ((SMOOTHED(-4, 6) < SMOOTHED(-9, 1)) << 4) + ((SMOOTHED(-12, -7) < SMOOTHED(-14, -8)) << 3) + ((SMOOTHED(-10, 8) < SMOOTHED(-10, 12)) << 2) + ((SMOOTHED(-19, 23) < SMOOTHED(-17, 24)) << 1) + ((SMOOTHED(-12, -20) < SMOOTHED(-16, -18)) << 0) ;
			desc[14] = ((SMOOTHED(-24, -18) < SMOOTHED(-23, -25)) << 7) + ((SMOOTHED(-25, 25) < SMOOTHED(18, 25)) << 6) + ((SMOOTHED(25, -24) < SMOOTHED(20, -25)) << 5) + ((SMOOTHED(-6, -17) < SMOOTHED(-16, -20)) << 4) + ((SMOOTHED(-3, -12) < SMOOTHED(-3, -10)) << 3) + ((SMOOTHED(9, -24) < SMOOTHED(7, -25)) << 2) + ((SMOOTHED(19, 7) < SMOOTHED(21, 11)) << 1) + ((SMOOTHED(-9, -24) < SMOOTHED(0, -25)) << 0) ;
			desc[15] = ((SMOOTHED(-4, -15) < SMOOTHED(-10, -23)) << 7) + ((SMOOTHED(-22, 7) < SMOOTHED(-23, 7)) << 6) + ((SMOOTHED(16, -7) < SMOOTHED(21, -7)) << 5) + ((SMOOTHED(-12, 3) < SMOOTHED(-13, 3)) << 4) + ((SMOOTHED(3, -5) < SMOOTHED(1, -5)) << 3) + ((SMOOTHED(-14, -4) < SMOOTHED(-13, -2)) << 2) + ((SMOOTHED(-20, -18) < SMOOTHED(-17, -18)) << 1) + ((SMOOTHED(2, 8) < SMOOTHED(6, -1)) << 0) ;
			desc[16] = ((SMOOTHED(-18, -24) < SMOOTHED(-24, -22)) << 7) + ((SMOOTHED(15, -22) < SMOOTHED(-8, 22)) << 6) + ((SMOOTHED(-24, -6) < SMOOTHED(-25, -1)) << 5) + ((SMOOTHED(21, 25) < SMOOTHED(20, 25)) << 4) + ((SMOOTHED(6, 10) < SMOOTHED(6, 18)) << 3) + ((SMOOTHED(-14, 13) < SMOOTHED(-14, 14)) << 2) + ((SMOOTHED(7, -25) < SMOOTHED(8, -23)) << 1) + ((SMOOTHED(0, 22) < SMOOTHED(16, 21)) << 0) ;
			desc[17] = ((SMOOTHED(-16, -25) < SMOOTHED(-18, -22)) << 7) + ((SMOOTHED(23, 9) < SMOOTHED(23, -9)) << 6) + ((SMOOTHED(19, 16) < SMOOTHED(23, 16)) << 5) + ((SMOOTHED(18, -24) < SMOOTHED(-21, -21)) << 4) + ((SMOOTHED(16, -24) < SMOOTHED(17, -23)) << 3) + ((SMOOTHED(4, 17) < SMOOTHED(13, 21)) << 2) + ((SMOOTHED(19, 1) < SMOOTHED(13, 0)) << 1) + ((SMOOTHED(25, 21) < SMOOTHED(23, 24)) << 0) ;
			desc[18] = ((SMOOTHED(-7, 10) < SMOOTHED(-8, 10)) << 7) + ((SMOOTHED(-10, 15) < SMOOTHED(-9, 18)) << 6) + ((SMOOTHED(11, -2) < SMOOTHED(9, -1)) << 5) + ((SMOOTHED(7, 20) < SMOOTHED(7, 22)) << 4) + ((SMOOTHED(24, 12) < SMOOTHED(22, 12)) << 3) + ((SMOOTHED(-23, -13) < SMOOTHED(-23, -11)) << 2) + ((SMOOTHED(5, -20) < SMOOTHED(7, -19)) << 1) + ((SMOOTHED(23, -18) < SMOOTHED(25, -17)) << 0) ;
			desc[19] = ((SMOOTHED(-14, 17) < SMOOTHED(-12, 17)) << 7) + ((SMOOTHED(1, 2) < SMOOTHED(0, 2)) << 6) + ((SMOOTHED(-4, 8) < SMOOTHED(-4, 12)) << 5) + ((SMOOTHED(-14, 23) < SMOOTHED(-15, 16)) << 4) + ((SMOOTHED(-25, 13) < SMOOTHED(-23, 14)) << 3) + ((SMOOTHED(-13, 11) < SMOOTHED(13, -22)) << 2) + ((SMOOTHED(3, 10) < SMOOTHED(2, 10)) << 1) + ((SMOOTHED(-22, -5) < SMOOTHED(-25, -4)) << 0) ;
			desc[20] = ((SMOOTHED(-13, 9) < SMOOTHED(-16, 9)) << 7) + ((SMOOTHED(-8, -1) < SMOOTHED(-10, -7)) << 6) + ((SMOOTHED(-16, 1) < SMOOTHED(-18, 1)) << 5) + ((SMOOTHED(15, 24) < SMOOTHED(13, 25)) << 4) + ((SMOOTHED(21, -6) < SMOOTHED(25, -2)) << 3) + ((SMOOTHED(1, -16) < SMOOTHED(5, -17)) << 2) + ((SMOOTHED(-22, -16) < SMOOTHED(-20, -16)) << 1) + ((SMOOTHED(-24, 3) < SMOOTHED(-24, 5)) << 0) ;
			desc[21] = ((SMOOTHED(-1, -24) < SMOOTHED(-3, -21)) << 7) + ((SMOOTHED(-23, 8) < SMOOTHED(-18, 0)) << 6) + ((SMOOTHED(20, -18) < SMOOTHED(18, -17)) << 5) + ((SMOOTHED(24, -12) < SMOOTHED(24, -13)) << 4) + ((SMOOTHED(8, 13) < SMOOTHED(-25, -25)) << 3) + ((SMOOTHED(-25, 12) < SMOOTHED(-24, 10)) << 2) + ((SMOOTHED(-11, 24) < SMOOTHED(-10, 25)) << 1) + ((SMOOTHED(-20, 6) < SMOOTHED(-18, 8)) << 0) ;
			desc[22] = ((SMOOTHED(-2, -6) < SMOOTHED(-7, -7)) << 7) + ((SMOOTHED(-7, 23) < SMOOTHED(-7, 25)) << 6) + ((SMOOTHED(-24, 19) < SMOOTHED(-25, 22)) << 5) + ((SMOOTHED(19, -2) < SMOOTHED(18, -4)) << 4) + ((SMOOTHED(-11, 16) < SMOOTHED(-7, 15)) << 3) + ((SMOOTHED(-2, 20) < SMOOTHED(-3, 22)) << 2) + ((SMOOTHED(-21, 24) < SMOOTHED(-25, 19)) << 1) + ((SMOOTHED(-25, -16) < SMOOTHED(-25, -21)) << 0) ;
			desc[23] = ((SMOOTHED(-24, -25) < SMOOTHED(-22, -23)) << 7) + ((SMOOTHED(25, 1) < SMOOTHED(25, 5)) << 6) + ((SMOOTHED(-13, -9) < SMOOTHED(-13, -10)) << 5) + ((SMOOTHED(-13, 24) < SMOOTHED(-12, 23)) << 4) + ((SMOOTHED(8, -8) < SMOOTHED(7, -10)) << 3) + ((SMOOTHED(15, 0) < SMOOTHED(15, 1)) << 2) + ((SMOOTHED(4, -2) < SMOOTHED(3, -2)) << 1) + ((SMOOTHED(-6, -1) < SMOOTHED(-6, 1)) << 0) ;
			desc[24] = ((SMOOTHED(2, -22) < SMOOTHED(0, -23)) << 7) + ((SMOOTHED(25, 8) < SMOOTHED(24, 8)) << 6) + ((SMOOTHED(-3, 21) < SMOOTHED(-4, 21)) << 5) + ((SMOOTHED(22, 13) < SMOOTHED(22, 22)) << 4) + ((SMOOTHED(0, 5) < SMOOTHED(-2, 2)) << 3) + ((SMOOTHED(6, -18) < SMOOTHED(7, -16)) << 2) + ((SMOOTHED(-5, -7) < SMOOTHED(-8, -10)) << 1) + ((SMOOTHED(23, 3) < SMOOTHED(25, 4)) << 0) ;
			desc[25] = ((SMOOTHED(-4, 25) < SMOOTHED(4, 25)) << 7) + ((SMOOTHED(6, -21) < SMOOTHED(1, -21)) << 6) + ((SMOOTHED(-18, -9) < SMOOTHED(-17, -7)) << 5) + ((SMOOTHED(10, 24) < SMOOTHED(2, 6)) << 4) + ((SMOOTHED(-22, 25) < SMOOTHED(-19, 24)) << 3) + ((SMOOTHED(6, 24) < SMOOTHED(8, 24)) << 2) + ((SMOOTHED(11, -21) < SMOOTHED(11, -22)) << 1) + ((SMOOTHED(-25, 18) < SMOOTHED(-23, 19)) << 0) ;
			desc[26] = ((SMOOTHED(-1, 18) < SMOOTHED(0, 20)) << 7) + ((SMOOTHED(-20, -7) < SMOOTHED(-22, -6)) << 6) + ((SMOOTHED(22, 9) < SMOOTHED(23, 10)) << 5) + ((SMOOTHED(-8, 10) < SMOOTHED(-15, 10)) << 4) + ((SMOOTHED(17, -5) < SMOOTHED(17, -7)) << 3) + ((SMOOTHED(24, 13) < SMOOTHED(17, 19)) << 2) + ((SMOOTHED(11, 17) < SMOOTHED(14, 16)) << 1) + ((SMOOTHED(24, 21) < SMOOTHED(23, -23)) << 0) ;
			desc[27] = ((SMOOTHED(2, 17) < SMOOTHED(11, -3)) << 7) + ((SMOOTHED(-25, -3) < SMOOTHED(-24, -2)) << 6) + ((SMOOTHED(-25, 23) < SMOOTHED(-20, 24)) << 5) + ((SMOOTHED(19, 25) < SMOOTHED(17, 23)) << 4) + ((SMOOTHED(10, 22) < SMOOTHED(13, 24)) << 3) + ((SMOOTHED(17, 17) < SMOOTHED(12, 13)) << 2) + ((SMOOTHED(-21, -15) < SMOOTHED(-21, -19)) << 1) + ((SMOOTHED(21, 25) < SMOOTHED(20, 22)) << 0) ;
			desc[28] = ((SMOOTHED(-21, -4) < SMOOTHED(-24, 2)) << 7) + ((SMOOTHED(8, -1) < SMOOTHED(11, 0)) << 6) + ((SMOOTHED(-4, 7) < SMOOTHED(-6, 8)) << 5) + ((SMOOTHED(-17, 25) < SMOOTHED(-15, 24)) << 4) + ((SMOOTHED(24, 24) < SMOOTHED(23, 25)) << 3) + ((SMOOTHED(-25, -21) < SMOOTHED(-23, -19)) << 2) + ((SMOOTHED(8, 6) < SMOOTHED(10, 6)) << 1) + ((SMOOTHED(-21, -13) < SMOOTHED(-15, -12)) << 0) ;
			desc[29] = ((SMOOTHED(4, 25) < SMOOTHED(3, 24)) << 7) + ((SMOOTHED(-17, 9) < SMOOTHED(-19, 11)) << 6) + ((SMOOTHED(23, 0) < SMOOTHED(24, 1)) << 5) + ((SMOOTHED(13, -11) < SMOOTHED(8, -13)) << 4) + ((SMOOTHED(-6, 22) < SMOOTHED(-19, 21)) << 3) + ((SMOOTHED(-9, 25) < SMOOTHED(-25, 25)) << 2) + ((SMOOTHED(8, 17) < SMOOTHED(7, 19)) << 1) + ((SMOOTHED(-2, -7) < SMOOTHED(-1, -10)) << 0) ;
			desc[30] = ((SMOOTHED(-3, 11) < SMOOTHED(-2, 12)) << 7) + ((SMOOTHED(-14, -16) < SMOOTHED(-13, -10)) << 6) + ((SMOOTHED(9, -19) < SMOOTHED(8, -18)) << 5) + ((SMOOTHED(-11, 25) < SMOOTHED(-13, -25)) << 4) + ((SMOOTHED(13, -25) < SMOOTHED(11, -25)) << 3) + ((SMOOTHED(-16, 15) < SMOOTHED(-18, 15)) << 2) + ((SMOOTHED(-23, -11) < SMOOTHED(-25, -14)) << 1) + ((SMOOTHED(-8, -12) < SMOOTHED(-6, -12)) << 0) ;
			desc[31] = ((SMOOTHED(-19, -25) < SMOOTHED(-18, -23)) << 7) + ((SMOOTHED(11, -7) < SMOOTHED(11, -5)) << 6) + ((SMOOTHED(2, -25) < SMOOTHED(-6, -25)) << 5) + ((SMOOTHED(-23, -25) < SMOOTHED(-25, -25)) << 4) + ((SMOOTHED(11, 4) < SMOOTHED(16, 7)) << 3) + ((SMOOTHED(25, -8) < SMOOTHED(23, -11)) << 2) + ((SMOOTHED(8, 10) < SMOOTHED(4, 11)) << 1) + ((SMOOTHED(-22, 16) < SMOOTHED(-19, 18)) << 0) ;
#undef SMOOTHED
		}
    }
}

static void pixelTests64(const Mat& sum, const std::vector<KeyPoint>& keypoints, Mat& descriptors)
{
    for (int i = 0; i < (int)keypoints.size(); ++i)
    {
        uchar* desc = descriptors.ptr(i);
        const KeyPoint& pt = keypoints[i];
		vector<int> pairs;
		ifstream in("test_pairs.grief");
    	pairs.clear();
		if(fs.isOpened()){
			in >> pairs;

#define SMOOTHED(y,x) smoothedSum(sum, pt, y, x)
			desc[0] = ((SMOOTHED(-13, -12) < SMOOTHED(-10, -12)) << 7) + ((SMOOTHED(-1, 25) < SMOOTHED(-3, 23)) << 6) + ((SMOOTHED(10, 9) < SMOOTHED(11, 10)) << 5) + ((SMOOTHED(15, 18) < SMOOTHED(15, 21)) << 4) + ((SMOOTHED(16, -15) < SMOOTHED(4, 22)) << 3) + ((SMOOTHED(0, -15) < SMOOTHED(0, -14)) << 2) + ((SMOOTHED(3, 23) < SMOOTHED(1, 24)) << 1) + ((SMOOTHED(-15, -2) < SMOOTHED(5, 21)) << 0) ;
			desc[1] = ((SMOOTHED(10, 12) < SMOOTHED(14, 10)) << 7) + ((SMOOTHED(3, 6) < SMOOTHED(-4, 8)) << 6) + ((SMOOTHED(25, -4) < SMOOTHED(23, -3)) << 5) + ((SMOOTHED(13, -18) < SMOOTHED(4, -17)) << 4) + ((SMOOTHED(-13, -25) < SMOOTHED(-13, -22)) << 3) + ((SMOOTHED(-7, -16) < SMOOTHED(-1, -17)) << 2) + ((SMOOTHED(-4, -5) < SMOOTHED(-3, -6)) << 1) + ((SMOOTHED(-17, 21) < SMOOTHED(-17, 25)) << 0) ;
			desc[2] = ((SMOOTHED(-11, -24) < SMOOTHED(-15, -24)) << 7) + ((SMOOTHED(-15, -25) < SMOOTHED(-14, -23)) << 6) + ((SMOOTHED(16, -20) < SMOOTHED(21, -25)) << 5) + ((SMOOTHED(-9, 0) < SMOOTHED(-12, 3)) << 4) + ((SMOOTHED(25, -9) < SMOOTHED(24, -6)) << 3) + ((SMOOTHED(-18, -5) < SMOOTHED(-18, -3)) << 2) + ((SMOOTHED(25, 25) < SMOOTHED(22, 24)) << 1) + ((SMOOTHED(-5, 22) < SMOOTHED(-9, 24)) << 0) ;
			desc[3] = ((SMOOTHED(-11, -25) < SMOOTHED(-8, -25)) << 7) + ((SMOOTHED(25, 19) < SMOOTHED(22, 18)) << 6) + ((SMOOTHED(16, -20) < SMOOTHED(17, -18)) << 5) + ((SMOOTHED(5, -1) < SMOOTHED(5, 3)) << 4) + ((SMOOTHED(17, 17) < SMOOTHED(19, 17)) << 3) + ((SMOOTHED(22, 8) < SMOOTHED(23, 7)) << 2) + ((SMOOTHED(-12, 1) < SMOOTHED(-12, 2)) << 1) + ((SMOOTHED(-24, 25) < SMOOTHED(-22, 21)) << 0) ;
			desc[4] = ((SMOOTHED(-25, -18) < SMOOTHED(-22, -16)) << 7) + ((SMOOTHED(-10, -6) < SMOOTHED(-9, -6)) << 6) + ((SMOOTHED(2, -2) < SMOOTHED(-17, -19)) << 5) + ((SMOOTHED(8, 2) < SMOOTHED(3, 1)) << 4) + ((SMOOTHED(-20, -25) < SMOOTHED(0, 25)) << 3) + ((SMOOTHED(-24, -15) < SMOOTHED(-25, -14)) << 2) + ((SMOOTHED(12, -19) < SMOOTHED(15, -19)) << 1) + ((SMOOTHED(-17, -2) < SMOOTHED(-25, 0)) << 0) ;
			desc[5] = ((SMOOTHED(-5, -20) < SMOOTHED(-4, -20)) << 7) + ((SMOOTHED(2, 14) < SMOOTHED(-3, 17)) << 6) + ((SMOOTHED(-5, 9) < SMOOTHED(-6, 16)) << 5) + ((SMOOTHED(25, 19) < SMOOTHED(22, 14)) << 4) + ((SMOOTHED(4, 0) < SMOOTHED(3, -2)) << 3) + ((SMOOTHED(24, -14) < SMOOTHED(25, -15)) << 2) + ((SMOOTHED(17, 25) < SMOOTHED(11, 25)) << 1) + ((SMOOTHED(21, -17) < SMOOTHED(20, -21)) << 0) ;
			desc[6] = ((SMOOTHED(-4, -18) < SMOOTHED(-3, -16)) << 7) + ((SMOOTHED(-3, 12) < SMOOTHED(-5, 12)) << 6) + ((SMOOTHED(24, -23) < SMOOTHED(24, -25)) << 5) + ((SMOOTHED(-21, 1) < SMOOTHED(-25, 18)) << 4) + ((SMOOTHED(-25, 2) < SMOOTHED(-23, 2)) << 3) + ((SMOOTHED(-19, 22) < SMOOTHED(-20, 22)) << 2) + ((SMOOTHED(-23, 14) < SMOOTHED(-24, 18)) << 1) + ((SMOOTHED(19, -22) < SMOOTHED(25, -22)) << 0) ;
			desc[7] = ((SMOOTHED(-23, 1) < SMOOTHED(-24, 0)) << 7) + ((SMOOTHED(-23, -19) < SMOOTHED(-14, -22)) << 6) + ((SMOOTHED(-17, -17) < SMOOTHED(-14, -16)) << 5) + ((SMOOTHED(-20, 7) < SMOOTHED(-19, 7)) << 4) + ((SMOOTHED(25, -13) < SMOOTHED(17, -10)) << 3) + ((SMOOTHED(-24, -11) < SMOOTHED(-25, -10)) << 2) + ((SMOOTHED(0, -9) < SMOOTHED(2, -7)) << 1) + ((SMOOTHED(10, -25) < SMOOTHED(24, -25)) << 0) ;
			desc[8] = ((SMOOTHED(-1, -23) < SMOOTHED(5, -24)) << 7) + ((SMOOTHED(-12, -7) < SMOOTHED(-23, -20)) << 6) + ((SMOOTHED(-1, -11) < SMOOTHED(3, -15)) << 5) + ((SMOOTHED(-18, -12) < SMOOTHED(-20, -12)) << 4) + ((SMOOTHED(7, -16) < SMOOTHED(9, -12)) << 3) + ((SMOOTHED(-2, -2) < SMOOTHED(-1, -5)) << 2) + ((SMOOTHED(2, 25) < SMOOTHED(2, 23)) << 1) + ((SMOOTHED(-25, 4) < SMOOTHED(-25, 10)) << 0) ;
			desc[9] = ((SMOOTHED(23, 14) < SMOOTHED(23, 8)) << 7) + ((SMOOTHED(24, -24) < SMOOTHED(25, -14)) << 6) + ((SMOOTHED(-13, -5) < SMOOTHED(-14, -4)) << 5) + ((SMOOTHED(12, -4) < SMOOTHED(13, -4)) << 4) + ((SMOOTHED(14, -25) < SMOOTHED(13, -24)) << 3) + ((SMOOTHED(23, -4) < SMOOTHED(20, -2)) << 2) + ((SMOOTHED(-20, 11) < SMOOTHED(-18, 12)) << 1) + ((SMOOTHED(-4, -24) < SMOOTHED(-4, -25)) << 0) ;
			desc[10] = ((SMOOTHED(-25, 17) < SMOOTHED(-23, 15)) << 7) + ((SMOOTHED(-7, 18) < SMOOTHED(-3, 18)) << 6) + ((SMOOTHED(15, -7) < SMOOTHED(-8, -9)) << 5) + ((SMOOTHED(25, -8) < SMOOTHED(23, -8)) << 4) + ((SMOOTHED(16, -11) < SMOOTHED(20, -17)) << 3) + ((SMOOTHED(1, -10) < SMOOTHED(-3, -10)) << 2) + ((SMOOTHED(-25, 11) < SMOOTHED(-22, 10)) << 1) + ((SMOOTHED(24, 22) < SMOOTHED(25, 23)) << 0) ;
			desc[11] = ((SMOOTHED(-14, 8) < SMOOTHED(-14, 9)) << 7) + ((SMOOTHED(20, 14) < SMOOTHED(25, 11)) << 6) + ((SMOOTHED(19, -1) < SMOOTHED(24, 0)) << 5) + ((SMOOTHED(-15, 19) < SMOOTHED(-18, 21)) << 4) + ((SMOOTHED(-8, 20) < SMOOTHED(-10, 20)) << 3) + ((SMOOTHED(11, 10) < SMOOTHED(11, 13)) << 2) + ((SMOOTHED(24, 1) < SMOOTHED(16, 3)) << 1) + ((SMOOTHED(-4, -17) < SMOOTHED(-20, -10)) << 0) ;
			desc[12] = ((SMOOTHED(9, -11) < SMOOTHED(12, -5)) << 7) + ((SMOOTHED(-23, -13) < SMOOTHED(-21, -13)) << 6) + ((SMOOTHED(23, -14) < SMOOTHED(18, -16)) << 5) + ((SMOOTHED(4, -9) < SMOOTHED(-2, -10)) << 4) + ((SMOOTHED(-19, -3) < SMOOTHED(-16, -2)) << 3) + ((SMOOTHED(14, -12) < SMOOTHED(13, -12)) << 2) + ((SMOOTHED(7, -11) < SMOOTHED(9, -11)) << 1) + ((SMOOTHED(-4, 0) < SMOOTHED(-5, 0)) << 0) ;
			desc[13] = ((SMOOTHED(4, -23) < SMOOTHED(7, -25)) << 7) + ((SMOOTHED(17, -7) < SMOOTHED(14, -7)) << 6) + ((SMOOTHED(-3, 25) < SMOOTHED(-6, 25)) << 5) + ((SMOOTHED(-4, 6) < SMOOTHED(-9, 1)) << 4) + ((SMOOTHED(-12, -7) < SMOOTHED(-14, -8)) << 3) + ((SMOOTHED(-10, 8) < SMOOTHED(-10, 12)) << 2) + ((SMOOTHED(-19, 23) < SMOOTHED(-17, 24)) << 1) + ((SMOOTHED(-12, -20) < SMOOTHED(-16, -18)) << 0) ;
			desc[14] = ((SMOOTHED(-24, -18) < SMOOTHED(-23, -25)) << 7) + ((SMOOTHED(-25, 25) < SMOOTHED(18, 25)) << 6) + ((SMOOTHED(25, -24) < SMOOTHED(20, -25)) << 5) + ((SMOOTHED(-6, -17) < SMOOTHED(-16, -20)) << 4) + ((SMOOTHED(-3, -12) < SMOOTHED(-3, -10)) << 3) + ((SMOOTHED(9, -24) < SMOOTHED(7, -25)) << 2) + ((SMOOTHED(19, 7) < SMOOTHED(21, 11)) << 1) + ((SMOOTHED(-9, -24) < SMOOTHED(0, -25)) << 0) ;
			desc[15] = ((SMOOTHED(-4, -15) < SMOOTHED(-10, -23)) << 7) + ((SMOOTHED(-22, 7) < SMOOTHED(-23, 7)) << 6) + ((SMOOTHED(16, -7) < SMOOTHED(21, -7)) << 5) + ((SMOOTHED(-12, 3) < SMOOTHED(-13, 3)) << 4) + ((SMOOTHED(3, -5) < SMOOTHED(1, -5)) << 3) + ((SMOOTHED(-14, -4) < SMOOTHED(-13, -2)) << 2) + ((SMOOTHED(-20, -18) < SMOOTHED(-17, -18)) << 1) + ((SMOOTHED(2, 8) < SMOOTHED(6, -1)) << 0) ;
			desc[16] = ((SMOOTHED(-18, -24) < SMOOTHED(-24, -22)) << 7) + ((SMOOTHED(15, -22) < SMOOTHED(-8, 22)) << 6) + ((SMOOTHED(-24, -6) < SMOOTHED(-25, -1)) << 5) + ((SMOOTHED(21, 25) < SMOOTHED(20, 25)) << 4) + ((SMOOTHED(6, 10) < SMOOTHED(6, 18)) << 3) + ((SMOOTHED(-14, 13) < SMOOTHED(-14, 14)) << 2) + ((SMOOTHED(7, -25) < SMOOTHED(8, -23)) << 1) + ((SMOOTHED(0, 22) < SMOOTHED(16, 21)) << 0) ;
			desc[17] = ((SMOOTHED(-16, -25) < SMOOTHED(-18, -22)) << 7) + ((SMOOTHED(23, 9) < SMOOTHED(23, -9)) << 6) + ((SMOOTHED(19, 16) < SMOOTHED(23, 16)) << 5) + ((SMOOTHED(18, -24) < SMOOTHED(-21, -21)) << 4) + ((SMOOTHED(16, -24) < SMOOTHED(17, -23)) << 3) + ((SMOOTHED(4, 17) < SMOOTHED(13, 21)) << 2) + ((SMOOTHED(19, 1) < SMOOTHED(13, 0)) << 1) + ((SMOOTHED(25, 21) < SMOOTHED(23, 24)) << 0) ;
			desc[18] = ((SMOOTHED(-7, 10) < SMOOTHED(-8, 10)) << 7) + ((SMOOTHED(-10, 15) < SMOOTHED(-9, 18)) << 6) + ((SMOOTHED(11, -2) < SMOOTHED(9, -1)) << 5) + ((SMOOTHED(7, 20) < SMOOTHED(7, 22)) << 4) + ((SMOOTHED(24, 12) < SMOOTHED(22, 12)) << 3) + ((SMOOTHED(-23, -13) < SMOOTHED(-23, -11)) << 2) + ((SMOOTHED(5, -20) < SMOOTHED(7, -19)) << 1) + ((SMOOTHED(23, -18) < SMOOTHED(25, -17)) << 0) ;
			desc[19] = ((SMOOTHED(-14, 17) < SMOOTHED(-12, 17)) << 7) + ((SMOOTHED(1, 2) < SMOOTHED(0, 2)) << 6) + ((SMOOTHED(-4, 8) < SMOOTHED(-4, 12)) << 5) + ((SMOOTHED(-14, 23) < SMOOTHED(-15, 16)) << 4) + ((SMOOTHED(-25, 13) < SMOOTHED(-23, 14)) << 3) + ((SMOOTHED(-13, 11) < SMOOTHED(13, -22)) << 2) + ((SMOOTHED(3, 10) < SMOOTHED(2, 10)) << 1) + ((SMOOTHED(-22, -5) < SMOOTHED(-25, -4)) << 0) ;
			desc[20] = ((SMOOTHED(-13, 9) < SMOOTHED(-16, 9)) << 7) + ((SMOOTHED(-8, -1) < SMOOTHED(-10, -7)) << 6) + ((SMOOTHED(-16, 1) < SMOOTHED(-18, 1)) << 5) + ((SMOOTHED(15, 24) < SMOOTHED(13, 25)) << 4) + ((SMOOTHED(21, -6) < SMOOTHED(25, -2)) << 3) + ((SMOOTHED(1, -16) < SMOOTHED(5, -17)) << 2) + ((SMOOTHED(-22, -16) < SMOOTHED(-20, -16)) << 1) + ((SMOOTHED(-24, 3) < SMOOTHED(-24, 5)) << 0) ;
			desc[21] = ((SMOOTHED(-1, -24) < SMOOTHED(-3, -21)) << 7) + ((SMOOTHED(-23, 8) < SMOOTHED(-18, 0)) << 6) + ((SMOOTHED(20, -18) < SMOOTHED(18, -17)) << 5) + ((SMOOTHED(24, -12) < SMOOTHED(24, -13)) << 4) + ((SMOOTHED(8, 13) < SMOOTHED(-25, -25)) << 3) + ((SMOOTHED(-25, 12) < SMOOTHED(-24, 10)) << 2) + ((SMOOTHED(-11, 24) < SMOOTHED(-10, 25)) << 1) + ((SMOOTHED(-20, 6) < SMOOTHED(-18, 8)) << 0) ;
			desc[22] = ((SMOOTHED(-2, -6) < SMOOTHED(-7, -7)) << 7) + ((SMOOTHED(-7, 23) < SMOOTHED(-7, 25)) << 6) + ((SMOOTHED(-24, 19) < SMOOTHED(-25, 22)) << 5) + ((SMOOTHED(19, -2) < SMOOTHED(18, -4)) << 4) + ((SMOOTHED(-11, 16) < SMOOTHED(-7, 15)) << 3) + ((SMOOTHED(-2, 20) < SMOOTHED(-3, 22)) << 2) + ((SMOOTHED(-21, 24) < SMOOTHED(-25, 19)) << 1) + ((SMOOTHED(-25, -16) < SMOOTHED(-25, -21)) << 0) ;
			desc[23] = ((SMOOTHED(-24, -25) < SMOOTHED(-22, -23)) << 7) + ((SMOOTHED(25, 1) < SMOOTHED(25, 5)) << 6) + ((SMOOTHED(-13, -9) < SMOOTHED(-13, -10)) << 5) + ((SMOOTHED(-13, 24) < SMOOTHED(-12, 23)) << 4) + ((SMOOTHED(8, -8) < SMOOTHED(7, -10)) << 3) + ((SMOOTHED(15, 0) < SMOOTHED(15, 1)) << 2) + ((SMOOTHED(4, -2) < SMOOTHED(3, -2)) << 1) + ((SMOOTHED(-6, -1) < SMOOTHED(-6, 1)) << 0) ;
			desc[24] = ((SMOOTHED(2, -22) < SMOOTHED(0, -23)) << 7) + ((SMOOTHED(25, 8) < SMOOTHED(24, 8)) << 6) + ((SMOOTHED(-3, 21) < SMOOTHED(-4, 21)) << 5) + ((SMOOTHED(22, 13) < SMOOTHED(22, 22)) << 4) + ((SMOOTHED(0, 5) < SMOOTHED(-2, 2)) << 3) + ((SMOOTHED(6, -18) < SMOOTHED(7, -16)) << 2) + ((SMOOTHED(-5, -7) < SMOOTHED(-8, -10)) << 1) + ((SMOOTHED(23, 3) < SMOOTHED(25, 4)) << 0) ;
			desc[25] = ((SMOOTHED(-4, 25) < SMOOTHED(4, 25)) << 7) + ((SMOOTHED(6, -21) < SMOOTHED(1, -21)) << 6) + ((SMOOTHED(-18, -9) < SMOOTHED(-17, -7)) << 5) + ((SMOOTHED(10, 24) < SMOOTHED(2, 6)) << 4) + ((SMOOTHED(-22, 25) < SMOOTHED(-19, 24)) << 3) + ((SMOOTHED(6, 24) < SMOOTHED(8, 24)) << 2) + ((SMOOTHED(11, -21) < SMOOTHED(11, -22)) << 1) + ((SMOOTHED(-25, 18) < SMOOTHED(-23, 19)) << 0) ;
			desc[26] = ((SMOOTHED(-1, 18) < SMOOTHED(0, 20)) << 7) + ((SMOOTHED(-20, -7) < SMOOTHED(-22, -6)) << 6) + ((SMOOTHED(22, 9) < SMOOTHED(23, 10)) << 5) + ((SMOOTHED(-8, 10) < SMOOTHED(-15, 10)) << 4) + ((SMOOTHED(17, -5) < SMOOTHED(17, -7)) << 3) + ((SMOOTHED(24, 13) < SMOOTHED(17, 19)) << 2) + ((SMOOTHED(11, 17) < SMOOTHED(14, 16)) << 1) + ((SMOOTHED(24, 21) < SMOOTHED(23, -23)) << 0) ;
			desc[27] = ((SMOOTHED(2, 17) < SMOOTHED(11, -3)) << 7) + ((SMOOTHED(-25, -3) < SMOOTHED(-24, -2)) << 6) + ((SMOOTHED(-25, 23) < SMOOTHED(-20, 24)) << 5) + ((SMOOTHED(19, 25) < SMOOTHED(17, 23)) << 4) + ((SMOOTHED(10, 22) < SMOOTHED(13, 24)) << 3) + ((SMOOTHED(17, 17) < SMOOTHED(12, 13)) << 2) + ((SMOOTHED(-21, -15) < SMOOTHED(-21, -19)) << 1) + ((SMOOTHED(21, 25) < SMOOTHED(20, 22)) << 0) ;
			desc[28] = ((SMOOTHED(-21, -4) < SMOOTHED(-24, 2)) << 7) + ((SMOOTHED(8, -1) < SMOOTHED(11, 0)) << 6) + ((SMOOTHED(-4, 7) < SMOOTHED(-6, 8)) << 5) + ((SMOOTHED(-17, 25) < SMOOTHED(-15, 24)) << 4) + ((SMOOTHED(24, 24) < SMOOTHED(23, 25)) << 3) + ((SMOOTHED(-25, -21) < SMOOTHED(-23, -19)) << 2) + ((SMOOTHED(8, 6) < SMOOTHED(10, 6)) << 1) + ((SMOOTHED(-21, -13) < SMOOTHED(-15, -12)) << 0) ;
			desc[29] = ((SMOOTHED(4, 25) < SMOOTHED(3, 24)) << 7) + ((SMOOTHED(-17, 9) < SMOOTHED(-19, 11)) << 6) + ((SMOOTHED(23, 0) < SMOOTHED(24, 1)) << 5) + ((SMOOTHED(13, -11) < SMOOTHED(8, -13)) << 4) + ((SMOOTHED(-6, 22) < SMOOTHED(-19, 21)) << 3) + ((SMOOTHED(-9, 25) < SMOOTHED(-25, 25)) << 2) + ((SMOOTHED(8, 17) < SMOOTHED(7, 19)) << 1) + ((SMOOTHED(-2, -7) < SMOOTHED(-1, -10)) << 0) ;
			desc[30] = ((SMOOTHED(-3, 11) < SMOOTHED(-2, 12)) << 7) + ((SMOOTHED(-14, -16) < SMOOTHED(-13, -10)) << 6) + ((SMOOTHED(9, -19) < SMOOTHED(8, -18)) << 5) + ((SMOOTHED(-11, 25) < SMOOTHED(-13, -25)) << 4) + ((SMOOTHED(13, -25) < SMOOTHED(11, -25)) << 3) + ((SMOOTHED(-16, 15) < SMOOTHED(-18, 15)) << 2) + ((SMOOTHED(-23, -11) < SMOOTHED(-25, -14)) << 1) + ((SMOOTHED(-8, -12) < SMOOTHED(-6, -12)) << 0) ;
			desc[31] = ((SMOOTHED(-19, -25) < SMOOTHED(-18, -23)) << 7) + ((SMOOTHED(11, -7) < SMOOTHED(11, -5)) << 6) + ((SMOOTHED(2, -25) < SMOOTHED(-6, -25)) << 5) + ((SMOOTHED(-23, -25) < SMOOTHED(-25, -25)) << 4) + ((SMOOTHED(11, 4) < SMOOTHED(16, 7)) << 3) + ((SMOOTHED(25, -8) < SMOOTHED(23, -11)) << 2) + ((SMOOTHED(8, 10) < SMOOTHED(4, 11)) << 1) + ((SMOOTHED(-22, 16) < SMOOTHED(-19, 18)) << 0) ;
			desc[32] = ((SMOOTHED(16, 12) < SMOOTHED(0, 19)) << 7) + ((SMOOTHED(4, 3) < SMOOTHED(6, 0)) << 6) + ((SMOOTHED(-2, -1) < SMOOTHED(2, 17)) << 5) + ((SMOOTHED(8, 1) < SMOOTHED(3, 1)) << 4) + ((SMOOTHED(-12, -1) < SMOOTHED(-11, 0)) << 3) + ((SMOOTHED(-11, 2) < SMOOTHED(7, 9)) << 2) + ((SMOOTHED(-1, 3) < SMOOTHED(-19, 4)) << 1) + ((SMOOTHED(-1, -11) < SMOOTHED(-1, 3)) << 0) ;
			desc[33] = ((SMOOTHED(1, -10) < SMOOTHED(-10, -4)) << 7) + ((SMOOTHED(-2, 3) < SMOOTHED(6, 11)) << 6) + ((SMOOTHED(3, 7) < SMOOTHED(-9, -8)) << 5) + ((SMOOTHED(24, -14) < SMOOTHED(-2, -10)) << 4) + ((SMOOTHED(-3, -3) < SMOOTHED(-18, -6)) << 3) + ((SMOOTHED(-13, -10) < SMOOTHED(-7, -1)) << 2) + ((SMOOTHED(2, -7) < SMOOTHED(9, -6)) << 1) + ((SMOOTHED(2, -4) < SMOOTHED(6, -13)) << 0) ;
			desc[34] = ((SMOOTHED(4, -4) < SMOOTHED(-2, 3)) << 7) + ((SMOOTHED(-4, 2) < SMOOTHED(9, 13)) << 6) + ((SMOOTHED(-11, 5) < SMOOTHED(-6, -11)) << 5) + ((SMOOTHED(4, -2) < SMOOTHED(11, -9)) << 4) + ((SMOOTHED(-19, 0) < SMOOTHED(-23, -5)) << 3) + ((SMOOTHED(-5, -7) < SMOOTHED(-3, -6)) << 2) + ((SMOOTHED(-6, -4) < SMOOTHED(12, 14)) << 1) + ((SMOOTHED(12, -11) < SMOOTHED(-8, -16)) << 0) ;
			desc[35] = ((SMOOTHED(-21, 15) < SMOOTHED(-12, 6)) << 7) + ((SMOOTHED(-2, -1) < SMOOTHED(-8, 16)) << 6) + ((SMOOTHED(6, -1) < SMOOTHED(-8, -2)) << 5) + ((SMOOTHED(1, -1) < SMOOTHED(-9, 8)) << 4) + ((SMOOTHED(3, -4) < SMOOTHED(-2, -2)) << 3) + ((SMOOTHED(-7, 0) < SMOOTHED(4, -8)) << 2) + ((SMOOTHED(11, -11) < SMOOTHED(-12, 2)) << 1) + ((SMOOTHED(2, 3) < SMOOTHED(11, 7)) << 0) ;
			desc[36] = ((SMOOTHED(-7, -4) < SMOOTHED(-9, -6)) << 7) + ((SMOOTHED(3, -7) < SMOOTHED(-5, 0)) << 6) + ((SMOOTHED(3, -7) < SMOOTHED(-10, -5)) << 5) + ((SMOOTHED(-3, -1) < SMOOTHED(8, -10)) << 4) + ((SMOOTHED(0, 8) < SMOOTHED(5, 1)) << 3) + ((SMOOTHED(9, 0) < SMOOTHED(1, 16)) << 2) + ((SMOOTHED(8, 4) < SMOOTHED(-11, -3)) << 1) + ((SMOOTHED(-15, 9) < SMOOTHED(8, 17)) << 0) ;
			desc[37] = ((SMOOTHED(0, 2) < SMOOTHED(-9, 17)) << 7) + ((SMOOTHED(-6, -11) < SMOOTHED(-10, -3)) << 6) + ((SMOOTHED(1, 1) < SMOOTHED(15, -8)) << 5) + ((SMOOTHED(-12, -13) < SMOOTHED(-2, 4)) << 4) + ((SMOOTHED(-6, 4) < SMOOTHED(-6, -10)) << 3) + ((SMOOTHED(5, -7) < SMOOTHED(7, -5)) << 2) + ((SMOOTHED(10, 6) < SMOOTHED(8, 9)) << 1) + ((SMOOTHED(-5, 7) < SMOOTHED(-18, -3)) << 0) ;
			desc[38] = ((SMOOTHED(-6, 3) < SMOOTHED(5, 4)) << 7) + ((SMOOTHED(-10, -13) < SMOOTHED(-5, -3)) << 6) + ((SMOOTHED(-11, 2) < SMOOTHED(-16, 0)) << 5) + ((SMOOTHED(7, -21) < SMOOTHED(-5, -13)) << 4) + ((SMOOTHED(-14, -14) < SMOOTHED(-4, -4)) << 3) + ((SMOOTHED(4, 9) < SMOOTHED(7, -3)) << 2) + ((SMOOTHED(4, 11) < SMOOTHED(10, -4)) << 1) + ((SMOOTHED(6, 17) < SMOOTHED(9, 17)) << 0) ;
			desc[39] = ((SMOOTHED(-10, 8) < SMOOTHED(0, -11)) << 7) + ((SMOOTHED(-6, -16) < SMOOTHED(-6, 8)) << 6) + ((SMOOTHED(-13, 5) < SMOOTHED(10, -5)) << 5) + ((SMOOTHED(3, 2) < SMOOTHED(12, 16)) << 4) + ((SMOOTHED(13, -8) < SMOOTHED(0, -6)) << 3) + ((SMOOTHED(10, 0) < SMOOTHED(4, -11)) << 2) + ((SMOOTHED(8, 5) < SMOOTHED(10, -2)) << 1) + ((SMOOTHED(11, -7) < SMOOTHED(-13, 3)) << 0) ;
			desc[40] = ((SMOOTHED(2, 4) < SMOOTHED(-7, -3)) << 7) + ((SMOOTHED(-14, -2) < SMOOTHED(-11, 16)) << 6) + ((SMOOTHED(11, -6) < SMOOTHED(7, 6)) << 5) + ((SMOOTHED(-3, 15) < SMOOTHED(8, -10)) << 4) + ((SMOOTHED(-3, 8) < SMOOTHED(12, -12)) << 3) + ((SMOOTHED(-13, 6) < SMOOTHED(-14, 7)) << 2) + ((SMOOTHED(-11, -5) < SMOOTHED(-8, -6)) << 1) + ((SMOOTHED(7, -6) < SMOOTHED(6, 3)) << 0) ;
			desc[41] = ((SMOOTHED(-4, 10) < SMOOTHED(5, 1)) << 7) + ((SMOOTHED(9, 16) < SMOOTHED(10, 13)) << 6) + ((SMOOTHED(-17, 10) < SMOOTHED(2, 8)) << 5) + ((SMOOTHED(-5, 1) < SMOOTHED(4, -4)) << 4) + ((SMOOTHED(-14, 8) < SMOOTHED(-5, 2)) << 3) + ((SMOOTHED(4, -9) < SMOOTHED(-6, -3)) << 2) + ((SMOOTHED(3, -7) < SMOOTHED(-10, 0)) << 1) + ((SMOOTHED(-2, -8) < SMOOTHED(-10, 4)) << 0) ;
			desc[42] = ((SMOOTHED(-8, 5) < SMOOTHED(-9, 24)) << 7) + ((SMOOTHED(2, -8) < SMOOTHED(8, -9)) << 6) + ((SMOOTHED(-4, 17) < SMOOTHED(-5, 2)) << 5) + ((SMOOTHED(14, 0) < SMOOTHED(-9, 9)) << 4) + ((SMOOTHED(11, 15) < SMOOTHED(-6, 5)) << 3) + ((SMOOTHED(-8, 1) < SMOOTHED(-3, 4)) << 2) + ((SMOOTHED(9, -21) < SMOOTHED(10, 2)) << 1) + ((SMOOTHED(2, -1) < SMOOTHED(4, 11)) << 0) ;
			desc[43] = ((SMOOTHED(24, 3) < SMOOTHED(2, -2)) << 7) + ((SMOOTHED(-8, 17) < SMOOTHED(-14, -10)) << 6) + ((SMOOTHED(6, 5) < SMOOTHED(-13, 7)) << 5) + ((SMOOTHED(11, 10) < SMOOTHED(0, -1)) << 4) + ((SMOOTHED(4, 6) < SMOOTHED(-10, 6)) << 3) + ((SMOOTHED(-12, -2) < SMOOTHED(5, 6)) << 2) + ((SMOOTHED(3, -1) < SMOOTHED(8, -15)) << 1) + ((SMOOTHED(1, -4) < SMOOTHED(-7, 11)) << 0) ;
			desc[44] = ((SMOOTHED(1, 11) < SMOOTHED(5, 0)) << 7) + ((SMOOTHED(6, -12) < SMOOTHED(10, 1)) << 6) + ((SMOOTHED(-3, -2) < SMOOTHED(-1, 4)) << 5) + ((SMOOTHED(-2, -11) < SMOOTHED(-1, 12)) << 4) + ((SMOOTHED(7, -8) < SMOOTHED(-20, -18)) << 3) + ((SMOOTHED(2, 0) < SMOOTHED(-9, 2)) << 2) + ((SMOOTHED(-13, -1) < SMOOTHED(-16, 2)) << 1) + ((SMOOTHED(3, -1) < SMOOTHED(-5, -17)) << 0) ;
			desc[45] = ((SMOOTHED(15, 8) < SMOOTHED(3, -14)) << 7) + ((SMOOTHED(-13, -12) < SMOOTHED(6, 15)) << 6) + ((SMOOTHED(2, -8) < SMOOTHED(2, 6)) << 5) + ((SMOOTHED(6, 22) < SMOOTHED(-3, -23)) << 4) + ((SMOOTHED(-2, -7) < SMOOTHED(-6, 0)) << 3) + ((SMOOTHED(13, -10) < SMOOTHED(-6, 6)) << 2) + ((SMOOTHED(6, 7) < SMOOTHED(-10, 12)) << 1) + ((SMOOTHED(-6, 7) < SMOOTHED(-2, 11)) << 0) ;
			desc[46] = ((SMOOTHED(0, -22) < SMOOTHED(-2, -17)) << 7) + ((SMOOTHED(-4, -1) < SMOOTHED(-11, -14)) << 6) + ((SMOOTHED(-2, -8) < SMOOTHED(7, 12)) << 5) + ((SMOOTHED(12, -5) < SMOOTHED(7, -13)) << 4) + ((SMOOTHED(2, -2) < SMOOTHED(-7, 6)) << 3) + ((SMOOTHED(0, 8) < SMOOTHED(-3, 23)) << 2) + ((SMOOTHED(6, 12) < SMOOTHED(13, -11)) << 1) + ((SMOOTHED(-21, -10) < SMOOTHED(10, 8)) << 0) ;
			desc[47] = ((SMOOTHED(-3, 0) < SMOOTHED(7, 15)) << 7) + ((SMOOTHED(7, -6) < SMOOTHED(-5, -12)) << 6) + ((SMOOTHED(-21, -10) < SMOOTHED(12, -11)) << 5) + ((SMOOTHED(-5, -11) < SMOOTHED(8, -11)) << 4) + ((SMOOTHED(5, 0) < SMOOTHED(-11, -1)) << 3) + ((SMOOTHED(8, -9) < SMOOTHED(7, -1)) << 2) + ((SMOOTHED(11, -23) < SMOOTHED(21, -5)) << 1) + ((SMOOTHED(0, -5) < SMOOTHED(-8, 6)) << 0) ;
			desc[48] = ((SMOOTHED(-6, 8) < SMOOTHED(8, 12)) << 7) + ((SMOOTHED(-7, 5) < SMOOTHED(3, -2)) << 6) + ((SMOOTHED(-5, -20) < SMOOTHED(-12, 9)) << 5) + ((SMOOTHED(-6, 12) < SMOOTHED(-11, 3)) << 4) + ((SMOOTHED(4, 5) < SMOOTHED(13, 11)) << 3) + ((SMOOTHED(2, 12) < SMOOTHED(13, -12)) << 2) + ((SMOOTHED(-4, -13) < SMOOTHED(4, 7)) << 1) + ((SMOOTHED(0, 15) < SMOOTHED(-3, -16)) << 0) ;
			desc[49] = ((SMOOTHED(-3, 2) < SMOOTHED(-2, 14)) << 7) + ((SMOOTHED(4, -14) < SMOOTHED(16, -11)) << 6) + ((SMOOTHED(-13, 3) < SMOOTHED(23, 10)) << 5) + ((SMOOTHED(9, -19) < SMOOTHED(2, 5)) << 4) + ((SMOOTHED(5, 3) < SMOOTHED(14, -7)) << 3) + ((SMOOTHED(19, -13) < SMOOTHED(-11, 15)) << 2) + ((SMOOTHED(14, 0) < SMOOTHED(-2, -5)) << 1) + ((SMOOTHED(11, -4) < SMOOTHED(0, -6)) << 0) ;
			desc[50] = ((SMOOTHED(-2, 5) < SMOOTHED(-13, -8)) << 7) + ((SMOOTHED(-11, -15) < SMOOTHED(-7, -17)) << 6) + ((SMOOTHED(1, 3) < SMOOTHED(-10, -8)) << 5) + ((SMOOTHED(-13, -10) < SMOOTHED(7, -12)) << 4) + ((SMOOTHED(0, -13) < SMOOTHED(23, -6)) << 3) + ((SMOOTHED(2, -17) < SMOOTHED(-7, -3)) << 2) + ((SMOOTHED(1, 3) < SMOOTHED(4, -10)) << 1) + ((SMOOTHED(13, 4) < SMOOTHED(14, -6)) << 0) ;
			desc[51] = ((SMOOTHED(-19, -2) < SMOOTHED(-1, 5)) << 7) + ((SMOOTHED(9, -8) < SMOOTHED(10, -5)) << 6) + ((SMOOTHED(7, -1) < SMOOTHED(5, 7)) << 5) + ((SMOOTHED(9, -10) < SMOOTHED(19, 0)) << 4) + ((SMOOTHED(7, 5) < SMOOTHED(-4, -7)) << 3) + ((SMOOTHED(-11, 1) < SMOOTHED(-1, -11)) << 2) + ((SMOOTHED(2, -1) < SMOOTHED(-4, 11)) << 1) + ((SMOOTHED(-1, 7) < SMOOTHED(2, -2)) << 0) ;
			desc[52] = ((SMOOTHED(1, -20) < SMOOTHED(-9, -6)) << 7) + ((SMOOTHED(-4, -18) < SMOOTHED(8, -18)) << 6) + ((SMOOTHED(-16, -2) < SMOOTHED(7, -6)) << 5) + ((SMOOTHED(-3, -6) < SMOOTHED(-1, -4)) << 4) + ((SMOOTHED(0, -16) < SMOOTHED(24, -5)) << 3) + ((SMOOTHED(-4, -2) < SMOOTHED(-1, 9)) << 2) + ((SMOOTHED(-8, 2) < SMOOTHED(-6, 15)) << 1) + ((SMOOTHED(11, 4) < SMOOTHED(0, -3)) << 0) ;
			desc[53] = ((SMOOTHED(7, 6) < SMOOTHED(2, -10)) << 7) + ((SMOOTHED(-7, -9) < SMOOTHED(12, -6)) << 6) + ((SMOOTHED(24, 15) < SMOOTHED(-8, -1)) << 5) + ((SMOOTHED(15, -9) < SMOOTHED(-3, -15)) << 4) + ((SMOOTHED(17, -5) < SMOOTHED(11, -10)) << 3) + ((SMOOTHED(-2, 13) < SMOOTHED(-15, 4)) << 2) + ((SMOOTHED(-2, -1) < SMOOTHED(4, -23)) << 1) + ((SMOOTHED(-16, 3) < SMOOTHED(-7, -14)) << 0) ;
			desc[54] = ((SMOOTHED(-3, -5) < SMOOTHED(-10, -9)) << 7) + ((SMOOTHED(-5, 3) < SMOOTHED(-2, -1)) << 6) + ((SMOOTHED(-1, 4) < SMOOTHED(1, 8)) << 5) + ((SMOOTHED(12, 9) < SMOOTHED(9, -14)) << 4) + ((SMOOTHED(-9, 17) < SMOOTHED(-3, 0)) << 3) + ((SMOOTHED(5, 4) < SMOOTHED(13, -6)) << 2) + ((SMOOTHED(-1, -8) < SMOOTHED(19, 10)) << 1) + ((SMOOTHED(8, -5) < SMOOTHED(-15, 2)) << 0) ;
			desc[55] = ((SMOOTHED(-12, -9) < SMOOTHED(-4, -5)) << 7) + ((SMOOTHED(12, 0) < SMOOTHED(24, 4)) << 6) + ((SMOOTHED(8, -2) < SMOOTHED(14, 4)) << 5) + ((SMOOTHED(8, -4) < SMOOTHED(-7, 16)) << 4) + ((SMOOTHED(5, -1) < SMOOTHED(-8, -4)) << 3) + ((SMOOTHED(-2, 18) < SMOOTHED(-5, 17)) << 2) + ((SMOOTHED(8, -2) < SMOOTHED(-9, -2)) << 1) + ((SMOOTHED(3, -7) < SMOOTHED(1, -6)) << 0) ;
			desc[56] = ((SMOOTHED(-5, -22) < SMOOTHED(-5, -2)) << 7) + ((SMOOTHED(-8, -10) < SMOOTHED(14, 1)) << 6) + ((SMOOTHED(-3, -13) < SMOOTHED(3, 9)) << 5) + ((SMOOTHED(-4, -1) < SMOOTHED(-1, 0)) << 4) + ((SMOOTHED(-7, -21) < SMOOTHED(12, -19)) << 3) + ((SMOOTHED(-8, 8) < SMOOTHED(24, 8)) << 2) + ((SMOOTHED(12, -6) < SMOOTHED(-2, 3)) << 1) + ((SMOOTHED(-5, -11) < SMOOTHED(-22, -4)) << 0) ;
			desc[57] = ((SMOOTHED(-3, 5) < SMOOTHED(-4, 4)) << 7) + ((SMOOTHED(-16, 24) < SMOOTHED(7, -9)) << 6) + ((SMOOTHED(-10, 23) < SMOOTHED(-9, 18)) << 5) + ((SMOOTHED(1, 12) < SMOOTHED(17, 21)) << 4) + ((SMOOTHED(24, -6) < SMOOTHED(-3, -11)) << 3) + ((SMOOTHED(-7, 17) < SMOOTHED(1, -6)) << 2) + ((SMOOTHED(4, 4) < SMOOTHED(2, -7)) << 1) + ((SMOOTHED(14, 6) < SMOOTHED(-12, 3)) << 0) ;
			desc[58] = ((SMOOTHED(-6, 0) < SMOOTHED(-16, 13)) << 7) + ((SMOOTHED(-10, 5) < SMOOTHED(7, 12)) << 6) + ((SMOOTHED(5, 2) < SMOOTHED(6, -3)) << 5) + ((SMOOTHED(7, 0) < SMOOTHED(-23, 1)) << 4) + ((SMOOTHED(15, -5) < SMOOTHED(1, 14)) << 3) + ((SMOOTHED(-3, -1) < SMOOTHED(6, 6)) << 2) + ((SMOOTHED(6, -9) < SMOOTHED(-9, 12)) << 1) + ((SMOOTHED(4, -2) < SMOOTHED(-4, 7)) << 0) ;
			desc[59] = ((SMOOTHED(-4, -5) < SMOOTHED(4, 4)) << 7) + ((SMOOTHED(-13, 0) < SMOOTHED(6, -10)) << 6) + ((SMOOTHED(2, -12) < SMOOTHED(-6, -3)) << 5) + ((SMOOTHED(16, 0) < SMOOTHED(-3, 3)) << 4) + ((SMOOTHED(5, -14) < SMOOTHED(6, 11)) << 3) + ((SMOOTHED(5, 11) < SMOOTHED(0, -13)) << 2) + ((SMOOTHED(7, 5) < SMOOTHED(-1, -5)) << 1) + ((SMOOTHED(12, 4) < SMOOTHED(6, 10)) << 0) ;
			desc[60] = ((SMOOTHED(-10, 4) < SMOOTHED(-1, -11)) << 7) + ((SMOOTHED(4, 10) < SMOOTHED(-14, 5)) << 6) + ((SMOOTHED(11, -14) < SMOOTHED(-13, 0)) << 5) + ((SMOOTHED(2, 8) < SMOOTHED(12, 24)) << 4) + ((SMOOTHED(-1, 3) < SMOOTHED(-1, 2)) << 3) + ((SMOOTHED(9, -14) < SMOOTHED(-23, 3)) << 2) + ((SMOOTHED(-8, -6) < SMOOTHED(0, 9)) << 1) + ((SMOOTHED(-15, 14) < SMOOTHED(10, -10)) << 0) ;
			desc[61] = ((SMOOTHED(-10, -6) < SMOOTHED(-7, -5)) << 7) + ((SMOOTHED(11, 5) < SMOOTHED(-3, -15)) << 6) + ((SMOOTHED(1, 0) < SMOOTHED(1, 8)) << 5) + ((SMOOTHED(-11, -6) < SMOOTHED(-4, -18)) << 4) + ((SMOOTHED(9, 0) < SMOOTHED(22, -4)) << 3) + ((SMOOTHED(-5, -1) < SMOOTHED(-9, 4)) << 2) + ((SMOOTHED(-20, 2) < SMOOTHED(1, 6)) << 1) + ((SMOOTHED(1, 2) < SMOOTHED(-9, -12)) << 0) ;
			desc[62] = ((SMOOTHED(5, 15) < SMOOTHED(4, -6)) << 7) + ((SMOOTHED(19, 4) < SMOOTHED(4, 11)) << 6) + ((SMOOTHED(17, -4) < SMOOTHED(-8, -1)) << 5) + ((SMOOTHED(-8, -12) < SMOOTHED(7, -3)) << 4) + ((SMOOTHED(11, 9) < SMOOTHED(8, 1)) << 3) + ((SMOOTHED(9, 22) < SMOOTHED(-15, 15)) << 2) + ((SMOOTHED(-7, -7) < SMOOTHED(1, -23)) << 1) + ((SMOOTHED(-5, 13) < SMOOTHED(-8, 2)) << 0) ;
			desc[63] = ((SMOOTHED(3, -5) < SMOOTHED(11, -11)) << 7) + ((SMOOTHED(3, -18) < SMOOTHED(14, -5)) << 6) + ((SMOOTHED(-20, 7) < SMOOTHED(-10, -23)) << 5) + ((SMOOTHED(-2, -5) < SMOOTHED(6, 0)) << 4) + ((SMOOTHED(-17, -13) < SMOOTHED(-3, 2)) << 3) + ((SMOOTHED(-6, -1) < SMOOTHED(14, -2)) << 2) + ((SMOOTHED(-12, -16) < SMOOTHED(15, 6)) << 1) + ((SMOOTHED(-12, -2) < SMOOTHED(3, -19)) << 0) ;
#undef SMOOTHED
		}
    }
}

namespace cv
{

GriefDescriptorExtractor::GriefDescriptorExtractor(int bytes) :
    bytes_(bytes), test_fn_(NULL)
{
    switch (bytes)
    {
        case 16:
            test_fn_ = pixelTests16;
            break;
        case 32:
            test_fn_ = pixelTests32;
            break;
        case 64:
            test_fn_ = pixelTests64;
            break;
        default:
            CV_Error(CV_StsBadArg, "bytes must be 16, 32, or 64");
    }
}

int GriefDescriptorExtractor::descriptorSize() const
{
    return bytes_;
}

int GriefDescriptorExtractor::descriptorType() const
{
    return CV_8UC1;
}

void GriefDescriptorExtractor::read( const FileNode& fn)
{
    int dSize = fn["descriptorSize"];
    switch (dSize)
    {
        case 16:
            test_fn_ = pixelTests16;
            break;
        case 32:
            test_fn_ = pixelTests32;
            break;
        case 64:
            test_fn_ = pixelTests64;
            break;
        default:
            CV_Error(CV_StsBadArg, "descriptorSize must be 16, 32, or 64");
    }
    bytes_ = dSize;
}

void GriefDescriptorExtractor::write( FileStorage& fs) const
{
    fs << "descriptorSize" << bytes_;
}

void GriefDescriptorExtractor::computeImpl(const Mat& image, std::vector<KeyPoint>& keypoints, Mat& descriptors) const
{
    // Construct integral image for fast smoothing (box filter)
    Mat sum;

    Mat grayImage = image;
    if( image.type() != CV_8U ) cvtColor( image, grayImage, CV_BGR2GRAY );

    ///TODO allow the user to pass in a precomputed integral image
    //if(image.type() == CV_32S)
    //  sum = image;
    //else

    integral( grayImage, sum, CV_32S);

    //Remove keypoints very close to the border
    KeyPointsFilter::runByImageBorder(keypoints, image.size(), PATCH_SIZE/2 + KERNEL_SIZE/2);

    descriptors = Mat::zeros((int)keypoints.size(), bytes_, CV_8U);
    test_fn_(sum, keypoints, descriptors);
}

} // namespace cv

