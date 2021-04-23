#! bin/bash

if [[ $1 -ge 1 ]]
then
echo "VALID:"
.././cub3D test_valid_1.cub
.././cub3D test_valid_2.cub
.././cub3D test_valid_3.cub
.././cub3D test_valid_4.cub
.././cub3D test_valid_5.cub
.././cub3D test_valid_6.cub
.././cub3D test_valid_7.cub
.././cub3D test_valid_8.cub
echo "END_VALID"
fi
echo "NOT_VALID:"
.././cub3D test_not_valid_1.cub
.././cub3D test_not_valid_2.cub
.././cub3D test_not_valid_3.cub
.././cub3D test_not_valid_4.cub
.././cub3D test_not_valid_5.cub
.././cub3D test_not_valid_6.cub
.././cub3D test_not_valid_7.cub
.././cub3D test_not_valid_8.cub
.././cub3D test_not_valid_9.cub
.././cub3D test_not_valid_10.cub
.././cub3D test_not_valid_11.cub
.././cub3D test_not_valid_12.cub
.././cub3D test_not_valid_13.cub
.././cub3D test_not_valid_14.cub
.././cub3D test_not_valid_15.cub
.././cub3D test_not_valid_16.cub
echo "END_NOT_VALID"