FROM ubuntu

RUN apt update &&\
    apt install -y clang \
    make

# for debug
RUN apt install -y vim

COPY . /ft_containers

WORKDIR /ft_containers

CMD ./docker/run_make.sh