# Raytracer

![Example generated image](/example.jpg)

I got bored one weekend and wanted to try some different techniques for raytracing than those I
previously used in [Fantasi][f]. In this project, rays scatter off of surfaces they hit
stochastically, whereas in Fantasi rays followed a deterministic path, computing lighting using
some approximations.

## Building

Currently this only supports Linux (and maybe macOS) based systems. You'll need a version of g++
that supports C++17, as well as the boost libraries. Generally you should be good to go if you run:

    sudo apt-get install build-essentials libboost-all-dev

Then just run `make release` and it should output a binary to `./build/release/apps/raytracer`.

## Acknowledgements

This project was largely inspired by the excellent book [Ray Tracing in One Weekend][rt] by Peter
Shirley. It's well-written and easy to follow along. I made many of my own modifications along the
way, making use of techniques from [Scratchapixel][s] and the book
[Physically Based Rendering: From Theory to Implementation][p] by Matt Pharr et. al.

[f]: https://github.com/thecodeboss/Fantasi
[rt]: http://in1weekend.blogspot.com/2016/01/ray-tracing-in-one-weekend.html
[p]: http://www.pbr-book.org/
[s]: https://www.scratchapixel.com/

## License

Code in this repository is released under the MIT License - see the LICENSE file.
