git clone https://github.com/42Paris/minilibx-linux.git mlx_linux
cd mlx_linux
./configure
cd ..
mv Makefile Makefile_m && mv Makefile_l Makefile
mv my_cub_utils.h my_cub_utils_m.h && mv my_cub_utils_l.h my_cub_utils.h
make
./cub3D tests_maps/test_valid_3.cub