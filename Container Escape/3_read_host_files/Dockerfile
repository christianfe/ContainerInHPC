FROM ubuntu:22.04

SHELL ["/bin/bash", "-c"]

RUN apt-get update -y
RUN apt-get install -y vim build-essential net-tools netcat ssh

COPY shocker.c /shocker.c
RUN gcc -o shocker shocker.c
