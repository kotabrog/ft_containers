docker image build -t clang_make -f docker/Dockerfile .
docker run --rm -v ${PWD}:/ft_containers -d clang_make