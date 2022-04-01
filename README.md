# Youtube Subtitle Searcher

YouTube Subtitle Searcher is a application to search subtitles from YouTube videos for a specified term and generate link to the times in which the term appears in the video. Subtitle files are required to be in VTT format with the title:

    <video name>-<youtube video id>

Subtitles with this format can be downloaded using [youtube-dl](https://github.com/ytdl-org/youtube-dl). This application can execute the required command to download the subtitles. This command is: 

    youtube-dl --sub-lang en --write-auto-sub --sub-format vtt --skip-download --output %(title)s-%(id)s.%(ext)s "<link to video>"

## Demo

![demo](./demo/demo.gif)

## Getting Started

This shows how to get a local copy of the project running for development.

### Prerequisites

- [youtube-dl](https://github.com/ytdl-org/youtube-dl)

### Installing

Download [youtube-dl](https://github.com/ytdl-org/youtube-dl) and place it in the directory with ytsubsearcher.exe.