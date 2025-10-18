#ifndef VIDEO_BUF_H
#define VIDEO_BUF_H

#include <vector>
#include <optional>
#include <string>
#include <chrono>

namespace Buffer 
{
    struct VideoFrame
    {
        std::vector<std::uint8_t> img; 
        std::size_t w; 
        std::size_t h; 
        std::size_t pts; // presentation timestamp
    };

    struct AudioFrame
    {

    };

    struct Video 
    {
        static std::optional<Video> create_from(const std::string file_path);

        std::string vid_name; 
        // MP4s (our target type for now) support either
        std::optional<std::vector<VideoFrame>> video_buffer = std::nullopt;
        std::optional<std::vector<AudioFrame>> audio_buffer = std::nullopt;
        double length_seconds;
        double video_width; 
        double video_height; 

        // note: frame is MOVED
        void add_vframe(VideoFrame&& frame);
    };
};

#endif // VIDEO_BUF_H