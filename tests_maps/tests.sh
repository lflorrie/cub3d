if [[ $1 -ge 1 ]]
then
echo "VALID:"
.././mlx-test test_valid_1.cub
.././mlx-test test_valid_2.cub
.././mlx-test test_valid_3.cub
.././mlx-test test_valid_4.cub
.././mlx-test test_valid_5.cub
.././mlx-test test_valid_6.cub
.././mlx-test test_valid_7.cub
.././mlx-test test_valid_8.cub
echo "END_VALID"
fi
echo "NOT_VALID:"
echo "1"
.././mlx-test test_not_valid_1.cub
.././mlx-test test_not_valid_2.cub
.././mlx-test test_not_valid_3.cub
.././mlx-test test_not_valid_4.cub
.././mlx-test test_not_valid_5.cub
echo "6"
.././mlx-test test_not_valid_6.cub
.././mlx-test test_not_valid_7.cub
.././mlx-test test_not_valid_8.cub
.././mlx-test test_not_valid_9.cub
.././mlx-test test_not_valid_10.cub
.././mlx-test test_not_valid_11.cub
.././mlx-test test_not_valid_12.cub
.././mlx-test test_not_valid_13.cub
.././mlx-test test_not_valid_14.cub
.././mlx-test test_not_valid_15.cub
.././mlx-test test_not_valid_16.cub
echo "11"
echo "END_NOT_VALID"