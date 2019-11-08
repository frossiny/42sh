# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/03 15:04:01 by lubenard          #+#    #+#              #
#    Updated: 2019/11/08 17:35:53 by lubenard         ###   ########.fr        #
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
