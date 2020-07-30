#!/bin/bash


unset options;

function add-opt {
	options="${options}$1"
}

function reset-cache {
	case "$options" in
		*r*)
			rm -rf ./* \
			&& cmake -DCMAKE_BUILD_TYPE="$1" .. \
			|| return 1;;
	esac
}

function run-cmake {
	cmake --build . || return 1
}

function process-arg {
	mkdir -p "$1" \
	&& cd "$1" \
	&& reset-cache "$2" \
	&& run-cmake \
	|| return 1
}

if [[ "$1" = '-r' || "$1" = '--rm-cache' ]]; then
	add-opt r
	shift 1
fi

unset error
while [[ -n "$1" ]]; do
	case "$1" in
		default)
			profile=default;
			profile_val='';;
		debug)
			profile=debug;
			profile_val=Debug;;
		release)
			profile=release;
			profile_val=Release;;
		release-debug)
			profile=release-dbginfo;
			profile_val=RelWithDebInfo;;
		release-size)
			profile=release-minsize;
			profile_val=MinSizeRel;;
		*)  error='';;
	esac
	(process-arg "$profile" "$profile_val") || error=''
	shift
done
[[ -v error ]] && exit 1 || exit 0
