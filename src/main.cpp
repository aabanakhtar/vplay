//
// Created by aabanakhtar on 9/29/25.
//
#include <iostream>
#include <SDL3/SDL.h>

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

    std::cout << "Video format: " << video_fmt_ctx->iformat->name << 
        ", Duration: " << double(video_fmt_ctx->duration) / AV_TIME_BASE << ", and cool!\n";
    
        // load the streams into context
    avformat_find_stream_info(video_fmt_ctx, nullptr);

    for (std::size_t i = 0; i < video_fmt_ctx->nb_streams; ++i)
    {
        auto& selected_stream = video_fmt_ctx->streams[i]; 
        // describes the codec
        AVCodecParameters* codec_params = selected_stream->codecpar; 

        if (codec_params->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            std::cout << "Resolution: " << codec_params->width << "x" << codec_params->height << "\n";
        } 
        else if (codec_params->codec_type == AVMEDIA_TYPE_AUDIO) 
        {
            std::cout << "channels: " << codec_params->channels << ", sample rate: " << codec_params->sample_rate << ".\n";
        }

        // create a  context for encode/decode ops
        AVCodec* codec = avcodec_find_decoder(codec_params->codec_id); 
        AVCodecContext* coding_ctx = avcodec_alloc_context3(codec); // allocate a context
        avcodec_parameters_to_context(coding_ctx, codec_params); // supply some codec params
        avcodec_open2(coding_ctx, codec, nullptr); // init the context

        AVPacket* packet = av_packet_alloc(); 
        AVFrame* frame = av_frame_alloc(); 

        while (av_read_frame(video_fmt_ctx, packet) >= 0)
        {
            avcodec_send_packet(coding_ctx, packet); 
            avcodec_receive_frame(coding_ctx, frame); 

        }

        av_packet_free(&packet); 
        av_frame_free(&frame);

        avcodec_close(coding_ctx);
        avcodec_free_context(&coding_ctx);
    }
    
    avformat_free_context(video_fmt_ctx);
    return 0;
}