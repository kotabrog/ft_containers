FROM ubuntu

RUN apt update &&\
    apt install -y clang\
    make

# for debug
# RUN apt install -y vim

RUN mkdir /ft_containers
COPY ./docker /ft_containers/docker

WORKDIR /ft_containers

CMD ./docker/run_make.sh
