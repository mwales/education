#!/bin/bash

current_dir=`pwd`
tool_dir=`dirname $0`

is_dc_image_installed=`docker image ls | cut -d ' ' -f 1 | grep decompyle6_img  | wc -l`
echo "is installed = $is_dc_image_installed"
if [[ $is_dc_image_installed -lt 1 ]]; then
	echo "running first time, building docker image"
	docker build -t decompyle6_img $tool_dir
fi

docker run --rm -it -v "$current_dir":/opt decompyle6_img uncompyle6 "$@"

