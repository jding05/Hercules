#!/bin/bash

# $1 -> first argument
if [ $1 == "--help" ]; then
	echo "Usage: sh bird.sh [DIR NAME]"
	exit
fi

mkdir $1
mkdir $1/SRCS
mkdir $1/INCLUDES

echo "sding" > $1/author

cp -R c.gitignore $1/.gitignore


echo "Do you want to include libft? (y/n)?"
read answer
if [ "$answer" == Y ] || [ "$answer" == y ] || [ "$answer" == YES ] || [ "$answer" == yes ]
then
		git clone https://github.com/jding05/libft.git libft;
		rm -rf libft/.git;
		mkdir $1/libft;
		mv libft $1/;
		cp -R Makefile_include_libft/Makefile $1/Makefile;
		echo "\nalready clone libft from jding05 github.";
		echo "you can start work on your project";
else
	cp -R Makefile $1/Makefile;
	echo "\nyou can start work on your project!";
fi
