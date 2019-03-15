#!/usr/bin/env bash
if [ "$(ls -A ./libft 2> /dev/null)" == "" ]; then
	git submodule update --init
else
	git submodule update --recursive --remote
fi