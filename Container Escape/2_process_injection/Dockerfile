FROM ubuntu:22.04

SHELL ["/bin/bash", "-c"]

RUN apt-get update -y

RUN apt-get install -y vim build-essential net-tools netcat

COPY infect.c /infect.c

RUN gcc -o infect infect.c
