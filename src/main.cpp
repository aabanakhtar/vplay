//
// Created by aabanakhtar on 9/29/25.
//
#include <iostream>
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}

int main(int argc, char* argv[])
{
    std::string filename = "vid.mp4";
    AVFormatContext* video_fmt_ctx = avformat_alloc_context();
    if (video_fmt_ctx == nullptr)
    {
        std::cerr << "Could not allocate context!" << std::endl;
    }

    if (avformat_open_input(&video_fmt_ctx, filename.c_str(), nullptr, nullptr) != 0) 
    {
        std::cerr << "Could not open the file!" << std::endl;
    }

    std::cout << "Video format: " << video_fmt_ctx->iformat->name << ", Duration: " << video_fmt_ctx->duration << ", and cool!\n";
    
    avformat_free_context(video_fmt_ctx);
    return 0;
}