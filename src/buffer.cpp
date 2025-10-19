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

    std::optional<std::vector<Buffer::VideoFrame>> create_video_from_stream(size_t stream_idx, AVFormatContext* ctx, AVCodecParameters* codecpar)
    {
        AVCodec* cdc = avcodec_find_decoder(codecpar->codec_id); 
        // create a decoding context
        AVCodecContext* decode_ctx = avcodec_alloc_context3(cdc); 
        // pass in some parameters and open it up
        avcodec_parameters_to_context(decode_ctx, codecpar); 
        
        // try to open
        if (avcodec_open2(decode_ctx, cdc, nullptr) < 0) 
        {
            std::cerr << "Couldn't open codec. \n"; 
            return std::nullopt;
        }

        std::vector<Buffer::VideoFrame> buf; 
        AVPacket* pkt = av_packet_alloc(); 
        AVFrame* frame = av_frame_alloc(); 

        // process frame till EOF
        while (av_read_frame(ctx, pkt) >= 0) 
        {
            // ensure target
            if (pkt->stream_index == stream_idx)
            {
                // send it to the decoder
                if (avcodec_send_packet(decode_ctx, pkt) < 0) 
                {
                    std::cerr << "Unable to handle decoding packets!\n";
                    break;
                }

                // recieve it on the other end
                while (avcodec_receive_frame(decode_ctx, frame) == 0) 
                {
                    // do processing here
                    Buffer::VideoFrame vframe; 
                    vframe.h = frame->height; 
                    vframe.w = frame->width; 
                    buf.push_back(vframe);
                }

            }

            // cleans up internal stuff related to this packet
            av_packet_unref(pkt);
        }

        // clean up
        av_packet_free(&pkt); 
        av_frame_free(&frame);
        avcodec_close(decode_ctx); 
        avcodec_free_context(&decode_ctx);
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
            result.video_buffer = create_video_from_stream(i, vid_ctx, codecpar);
            found_video_stream = true;
        }
    }

    if (!found_audio_stream || !found_video_stream) 
    {
        std::cerr << "Could not find certain streams!" << std::endl;
    }

    avformat_free_context(vid_ctx);
    return result;
}
