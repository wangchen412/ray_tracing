#include <fstream>

template <typename Func>
void render(Func f, int image_width, int image_height) {
  auto file = std::ofstream("image.ppm");
  file << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (int j = 0; j < image_height; ++j) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; ++i) write_color(file, f(i, j));
  }
  std::clog << "\rDone!                    " << std::endl;
  file.close();
}