# CLI Video Editor Roadmap

## Phase 0: Prerequisites

* Install FFmpeg development libraries
* Set up C++ build environment (CMake recommended)
* Familiarize with FFmpeg CLI usage
* Brush up on C++17/20 features, smart pointers, STL

## Phase 1: Learn FFmpeg API Basics

* Open video files (`avformat_open_input`, `avformat_find_stream_info`)
* Find video/audio streams (`av_find_best_stream`)
* Decode frames (`avcodec_send_packet`, `avcodec_receive_frame`)
* Encode frames for output (`avcodec_send_frame`, `avcodec_receive_packet`)
* Scale video frames with `libswscale`
* Resample audio with `libswresample`
* Start with reading a video file and printing frame info

## Phase 2: CLI Skeleton & Project Structure

* File structure:

  ```
  src/
    main.cpp
    cli/
      cli_parser.cpp, .h
    core/
      project.cpp, .h
    ffmpeg_wrappers/
      video_utils.cpp, .h
      audio_utils.cpp, .h
    utils/
      logger.cpp, .h
  ```
* Implement CLI parser using `cxxopts` or `CLI11`

  * Commands: `new`, `add`, `trim`, `overlay`, `export`, `list`, `preview`
* Implement Project object with:

  * Tracks: video/audio
  * Operations queue
  * Metadata storage

## Phase 3: In-Memory Operations

* Implement Operation class/struct:

  * Types: TRIM, CONCAT, OVERLAY_AUDIO, FILTER, RESIZE
* Add operations queue in Project object
* Commands add operations to queue (non-destructive)
* Implement `list` command to show queued operations

## Phase 4: Basic Export

* Iterate through operations and apply via FFmpeg API
* Handle trims, concatenation, and audio overlay
* Generate output file in chosen container and codec
* Show progress (ASCII progress bar optional)

## Phase 5: Terminal Preview (Optional)

* Decode frames using FFmpeg API
* Resize frame to terminal dimensions
* Convert pixels → ASCII/Unicode + optional ANSI colors
* Print frames with sleep based on FPS
* Simulate queued edits (trim, crop, filter) in preview

## Phase 6: Advanced Features

* Filters: grayscale, invert, brightness/contrast
* Batch operations on multiple files
* Undo/Redo stack for operations
* Save/load project state (serialize to JSON)
* Multi-threading for faster decoding/encoding

## Phase 7: Polish & Showcase

* Write README with installation and usage examples
* Add `examples/` folder with sample projects
* Record demo GIF/video showing CLI edits, preview, and export
* Push to GitHub as a capstone-level project

## Learning Path for FFmpeg

* Start with FFmpeg command-line to understand operations
* Learn `libavformat` + `libavcodec` for decoding frames
* Learn `libswscale` for resizing, `libswresample` for audio
* Combine learned APIs into in-memory project system

**Key Idea:**

* CLI editor acts like a mini NLE: edits stored in memory → preview → export. FFmpeg handles decoding/encoding; C++ manages project structure, operations, and CLI UX.
