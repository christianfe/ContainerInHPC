FROM gcc:latest
RUN mkdir -p /var/log/linpack
COPY linpack.c /usr/src/linpack/linpack.c
WORKDIR /usr/src/linpack
RUN gcc -o linpack -O3 -march=native -lm linpack.c
ENTRYPOINT ["./linpack"]