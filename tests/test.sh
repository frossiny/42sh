# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 15:04:01 by lubenard          #+#    #+#              #
#    Updated: 2019/11/08 17:35:53 by lubenard         ###   ########.fr        #
=======
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 15:04:01 by lubenard          #+#    #+#              #
#    Updated: 2019/11/08 17:31:22 by frossiny         ###   ########.fr        #
>>>>>>> e724c38d80f6dab5e9e1ff6e20931269f5a0f3bc
#                                                                              #
# **************************************************************************** #

make test > log_test
output=$(cat log_test)

if [[ $output == *"[ERROR]"* ]]; then
	echo "TEST FAILED"
	cat log_test
	rm log_test
	return 1
fi
echo "DONE ! All tests passed !"
rm log_test
<<<<<<< HEAD
=======
return 0

##!/bin/zsh
#
#PATH_42sh=../../42sh
#
#RED='\e[0;31m'
#GREEN='\e[0;32m'
#BLACK='\e[0;0m'
#
#chmod 755 tests_file/*
#rm diff_* 2>&-
#
#init()
##{
#	touch test1 test2 test3
#}
#
#cd 42sh_env
#init
#cd ../bash_env
#init
#cd ..
#
#for file in tests_file/*
#do
#	file=$(echo $file | sed -e 's:tests_file/::g')
#	cd 42sh_env
#	$PATH_42sh < ../tests_file/$file >"../42sh_result/result_$file" 2>"../42sh_result/result_$file"
#	cd ../bash_env
#	bash < ../tests_file/$file >"../bash_result/result_$file" 2>"../bash_result/result_$file"
#	cd ..
#	diff bash_result/result_$file 42sh_result/result_$file 1>/dev/null 2>/dev/null
#	if [ $? = 0 ]; then
#		echo "${GREEN}$file${BLACK}"
#	else
#		echo "${RED}$file${BLACK}"
#		echo "diff placed in : diff_$file"
#		diff bash_result/result_$file 42sh_result/result_$file > diff_$file;
#	fi
#done
>>>>>>> e724c38d80f6dab5e9e1ff6e20931269f5a0f3bc
