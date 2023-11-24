FROM ubuntu:22.04

SHELL ["/bin/bash", "-c"]

RUN apt-get update -y

RUN apt-get install -y ssh gcc vim

COPY shocker.c /shocker.c
COPY shocker_write.c /shocker_write.c

RUN gcc -o read shocker.c
RUN gcc -o write shocker_write.c
