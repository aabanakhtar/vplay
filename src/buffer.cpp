#include "buffer.h"
#include "util.h"
#include <iostream>

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}

void Buffer::Video::add_vframe(VideoFrame&& frame)
{
    if (video_buffer) 
    {
        video_buffer.value().emplace_back(std::move(frame));
    }
}

namespace {
    std::optional<std::vector<Buffer::VideoFrame>> create_video_from_stream(AVFormatContext* ctx, AVCodecParameters* codecpar)
    {
        return std::nullopt;
    }
}

std::optional<Buffer::Video> Buffer::Video::create_from(const std::string file_path)
{
    // represents a context for all video operations
    Video result; 
    AVFormatContext* vid_ctx = avformat_alloc_context();
    RETURN_IF_NULL_OPT(vid_ctx, std::nullopt);

    // open 
    if (avformat_open_input(&vid_ctx, file_path.c_str(), nullptr, nullptr) != 0) 
    {
        return std::nullopt; 
    }

    result.length_seconds = vid_ctx->duration / AV_TIME_BASE; 
    result.vid_name = file_path;  
    
    // load the streams 
    bool found_video_stream = false, found_audio_stream = false; 
    for (std::size_t i = 0; i != vid_ctx->nb_streams; ++i) 
    {
        auto& stream_sel = vid_ctx->streams[i]; 
        // describes codec
        AVCodecParameters* codecpar = stream_sel->codecpar; 
        if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            result.video_width = codecpar->width; 
            result.video_height = codecpar->height; 
            result.video_buffer = create_video_from_stream(vid_ctx, codecpar);
            found_video_stream;
        }

    }

    if (!found_audio_stream || !found_video_stream) 
    {
        std::cerr << "Could not find certain streams!" << std::endl;
    }

    avformat_free_context(vid_ctx);
    return result;
}
