docker image build -t clang_make -f ./docker/Dockerfile .
LOGNAME=`date +%Y%m%d%H%M%S`
mkdir -p ./make_log
docker run --rm -v ${PWD}:/ft_containers -e LOGNAME=${1} -d clang_make