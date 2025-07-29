#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // === 加载图像 ===
    cv::Mat src = cv::imread("3.png");    //使用imread，把图片存入nmupy数组，也就是矩阵
    cv::Mat templ = cv::imread("1.png");

    if (src.empty() || templ.empty()) {                      //。empty()函数判断矩阵是否为空，是cv::Mat类的成员函数
        std::cerr << "读取图片失败！请检查文件路径是否正确。" << std::endl;         //cerr是标准错误输出流，类似于cout,用于错误输出
        std::cerr << "src 是否加载成功？" << (src.empty() ? "否" : "是") << std::endl;
        std::cerr << "templ 是否加载成功？" << (templ.empty() ? "否" : "是") << std::endl;
        return -1;
    }

    std::cout << "源图尺寸: " << src.cols << "x" << src.rows << std::endl;         //输出源图的尺寸
    std::cout << "模板尺寸: " << templ.cols << "x" << templ.rows << std::endl;

    // === 模板匹配 ===
    cv::Mat result;        //定义一个结果矩阵
    cv::matchTemplate(src, templ, result, cv::TM_CCOEFF_NORMED);   //使用matchTemplate函数进行模板匹配，结果存入result矩阵
    // TM_CCOEFF_NORMED方法计算归一化的相关系数，返回值范围[-1, 1]，值越大表示匹配度越高，
    //cv::TM_CCOEFF_NORMED是运算的方法，还有其他方法如cv::TM_SQDIFF、cv::TM_CCORR等，


    // === 查找最大匹配值及其位置 ===
    double minVal, maxVal;         //定义最小值和最大值
    cv::Point minLoc, maxLoc;       //这个是为了后面可以输出匹配像素的位置
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);    //提取result的数据 

    std::cout << "匹配值范围：min = " << minVal << ", max = " << maxVal << std::endl;

    // === 判断是否匹配成功 ===
    if (maxVal > 0.8) {
        std::cout << "✅ 匹配成功！最大匹配度：" << maxVal
                  << "，位置：" << maxLoc << std::endl;

        // 在原图中绘制匹配框
    } else {
        std::cout << "❌ 匹配度太低，未找到匹配区域。" << std::endl;
    }

    return 0;
}
