FROM ubuntu

RUN apt update &&\
    apt install -y clang\
    make

# for debug
# RUN apt install -y vim

RUN mkdir /ft_containers
COPY ./docker_time /ft_containers/docker_time

WORKDIR /ft_containers

CMD ./docker_time/run_make.sh
