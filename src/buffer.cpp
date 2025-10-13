#include "buffer.h"

void Buffer::Video::add_vframe(VideoFrame&& frame)
{
    if (video_buffer) 
    {
        video_buffer.value().emplace_back(std::move(frame));
    }
}