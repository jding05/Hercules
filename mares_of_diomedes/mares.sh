# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mares.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sding <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/14 20:35:35 by sding             #+#    #+#              #
#    Updated: 2018/04/14 21:47:10 by sding            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

./manger &
pkill -4 podargos
pkill -5 lampon
pkill -10 xanthos
pkill -11 deinos
pkill -4 yes

kill -s KILL $(top -l 1 | grep manger | awk '{print $1}')
rm -rf *crap*poo*

gcc -o jeff_the_best creative_manger.c

./jeff_the_best &

sleep 3

pkill jeff_the best



echo "killed the manger"
