docker image build -t clang_make_time -f ./docker_time/Dockerfile .
LOGNAME=`date +%Y%m%d%H%M%S`
mkdir -p ./make_log
docker run --rm -v ${PWD}:/ft_containers -e LOGNAME=${1} -d clang_make_time