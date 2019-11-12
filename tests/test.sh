# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 15:04:01 by lubenard          #+#    #+#              #
#    Updated: 2019/11/12 17:58:08 by frossiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

make tests 2>&1 > log_test
output=$(cat log_test | grep 'Total failed tests:' | cut -f4 -d" ")

if [[ $output > 0 ]]; then
	echo $output "TEST(S) FAILED"
	cat log_test
	rm log_test
	exit 1
fi
echo "DONE ! All tests passed !"
rm log_test
exit 0
